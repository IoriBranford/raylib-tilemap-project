#include <engine/lua.h>
#include <util/lua_class.h>
#include <game/physics.h>

int L_physics_body(lua_State *l) {
    cpFloat mass = luaL_optnumber(l, 1, 1);
    cpFloat moment = luaL_optnumber(l, 2, HUGE_VAL);
    cpBody *body = NewBody(0, 0, 0);
    cpBodySetMass(body, mass);
    cpBodySetMoment(body, moment);
    class_newuserdata(l, cpBody, body);
    return 1;
}

int L_physics_kinematicbody(lua_State *l) {
    class_newuserdata(l, cpBody, cpBodyNewKinematic());
    return 1;
}

int L_physics_staticbody(lua_State *l) {
    class_newuserdata(l, cpBody, cpBodyNewStatic());
    return 1;
}

int L_physics_circleshape(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpFloat radius = luaL_optnumber(l, 2, 1);
    cpVect offset = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpShape *shape = AddBodyCircle(body, radius, offset.x, offset.y);
    class_newuserdata(l, cpShape, shape);
    return 1;
}

int L_physics_segmentshape(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpVect a = cpv(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    cpVect b = cpv(luaL_checknumber(l, 4), luaL_checknumber(l, 5));
    cpFloat radius = luaL_optnumber(l, 6, 0);
    class_newuserdata(l, cpShape, cpSegmentShapeNew(body, a, b, radius));
    return 1;
}

int L_physics_polyshape(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;

    int argType = lua_type(l, 2);

    int nVertArgs = 0;
    if (argType == LUA_TTABLE) {
        nVertArgs = lua_objlen(l, 2);
    } else if (argType == LUA_TNUMBER) {
        nVertArgs = lua_gettop(l) - 1;
    }

    if (nVertArgs % 2 != 0)
        luaL_error(l, "physics.polyshape expected even number of point components { x1, y1, x2, y2, ... }");
    else if (nVertArgs == 0)
        luaL_error(l, "physics.polyshape expected point components { x1, y1, x2, y2, ... }");
    
    int nVerts = nVertArgs / 2;
    cpVect *verts = calloc(sizeof(cpVect), nVerts);
    cpVect *vert = verts;
    if (argType == LUA_TTABLE) {
        for (int i = 2; i <= nVertArgs; i += 2) {
            lua_rawgeti(l, 2, i-1);
            lua_rawgeti(l, 2, i);
            vert->x = luaL_checknumber(l, -2);
            vert->y = luaL_checknumber(l, -1);
            lua_pop(l, 2);
            ++vert;
        }
    } else if (argType == LUA_TNUMBER) {
        int nArgs = nVertArgs + 1;
        for (int i = 2; i <= nVertArgs; i += 2) {
            vert->x = luaL_checknumber(l, i);
            vert->y = luaL_checknumber(l, i+1);
            ++vert;
        }
    }

    class_newuserdata(l, cpShape, cpPolyShapeNew(body, nVerts, verts, cpTransformIdentity, 0));

    free(verts);
    return 1;
}

#define cp_getter(cls, fieldtype, field) \
int L_##cls##___get##field(lua_State *l) { \
    cls **ud = luaL_checkudata(l, 1, #cls); \
    lua_push##fieldtype(l, cls##Get##field(*ud)); \
    return 1; \
}

#define cp_setter(cls, fieldtype, field) \
int L_##cls##___set##field(lua_State *l) { \
    cls **ud = luaL_checkudata(l, 1, #cls); \
    if (!*ud) return 0; \
    if (!lua_is##fieldtype(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), #fieldtype, #cls, #field); \
    cls##Set##field(*ud, lua_to##fieldtype(l, 2)); \
    return 0; \
}

#define cp_getter_and_setter(cls, fieldtype, field) \
    cp_getter(cls, fieldtype, field) \
    cp_setter(cls, fieldtype, field)

#define cp_getter_vect(cls, field) \
int L_##cls##_get##field(lua_State *l) { \
    cls **ud = luaL_checkudata(l, 1, #cls); \
    cpVect v = cls##Get##field(*ud); \
    lua_pushnumber(l, v.x); \
    lua_pushnumber(l, v.y); \
    return 2; \
}

#define cp_setter_vect(cls, field) \
int L_##cls##_set##field(lua_State *l) { \
    cls **ud = luaL_checkudata(l, 1, #cls); \
    cpVect v = { luaL_checknumber(l, 2), luaL_checknumber(l, 3) }; \
    cls##Set##field(*ud, v); \
    return 0; \
}

#define cp_getter_and_setter_vect(cls, field) \
    cp_getter_vect(cls, field) \
    cp_setter_vect(cls, field)

class_index_and_newindex(cpBody)
cp_getter_and_setter(cpBody, number, Angle)
cp_getter_and_setter(cpBody, number, AngularVelocity)
cp_getter_and_setter(cpBody, number, Torque)
cp_getter_and_setter(cpBody, number, Mass)
cp_getter_and_setter(cpBody, number, Moment)
cp_getter_and_setter_vect(cpBody, Position)
cp_getter_and_setter_vect(cpBody, CenterOfGravity)
cp_getter_and_setter_vect(cpBody, Velocity)
cp_getter_and_setter_vect(cpBody, Force)

int L_cpBody_NewCircleShape(lua_State *l) {
    cpBody **body = luaL_checkudata(l, 1, "cpBody");
    lua_Number radius = luaL_optnumber(l, 2, 0.5);
    cpVect offset = {
        luaL_optnumber(l, 3, 0),
        luaL_optnumber(l, 4, 0),
    };
    cpShape *shape = cpCircleShapeNew(*body, radius, offset);
    cpSpace *space = cpBodyGetSpace(*body);
    if (space)
        cpSpaceAddShape(space, shape);
    class_newuserdata(l, cpShape, shape);
    return 1;
}

int L_cpBody_UpdateSprite(lua_State *l) {
    cpBody **body = luaL_checkudata(l, 1, "cpBody");
    Sprite **sprite = luaL_checkudata(l, 2, "Sprite");
    UpdateSpriteFromBody(*body, *sprite);
    return 0;
}

void L_cpBody_EachArbiter_iter(cpBody *body, cpArbiter *arbiter, lua_State *l) {
    lua_pushvalue(l, 2);
    lua_pushlightuserdata(l, arbiter); // TODO make userdata class for Arbiter
    if (lua_pcall(l, 1, 0, 0) != LUA_OK) lua_error(l);
}

int L_cpBody_EachArbiter(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    if (lua_isfunction(l, 2))
        cpBodyEachArbiter(body, (cpBodyArbiterIteratorFunc)L_cpBody_EachArbiter_iter, l);
    return 0;
}

class_gc(cpBody, *, ReleaseBody)

int L_cpBody_RemoveFromSpace(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpSpace *space = cpBodyGetSpace(body);
    if (space)
        cpSpaceRemoveBody(space, body);
    return 0;
}

class_index_and_newindex(cpShape)

class_gc(cpShape, *, ReleaseOrphanedShape)

int L_cpShape_RemoveFromSpace(lua_State *l) {
    cpShape **ud = luaL_checkudata(l, 1, "cpShape");
    cpSpace *space = cpShapeGetSpace(*ud);
    if (space)
        cpSpaceRemoveShape(space, *ud);
    return 0;
}

cp_getter_and_setter(cpShape, boolean, Sensor)

int luaopen_physics(lua_State *l) {
    luaL_Reg staticMethods[] = {
        class_method_reg(physics, body),
        class_method_reg(physics, kinematicbody),
        class_method_reg(physics, staticbody),
        class_method_reg(physics, circleshape),
        {0}
    };
    luaL_register(l, "physics", staticMethods);
    lua_pop(l, 1);

    luaL_newmetatable(l, "cpBody");
    luaL_Reg bodyMethods[] = {
        class_method_reg(cpBody, __index),
        class_method_reg(cpBody, __newindex),
        class_method_reg(cpBody, __gc),
        class_method_reg(cpBody, NewCircleShape),
        class_method_reg(cpBody, UpdateSprite),
        class_method_reg(cpBody, EachArbiter),
        class_method_reg(cpBody, RemoveFromSpace),
        class_getter_and_setter_reg(cpBody, Angle),
        class_getter_and_setter_reg(cpBody, AngularVelocity),
        class_getter_and_setter_reg(cpBody, Torque),
        class_getter_and_setter_reg(cpBody, Mass),
        class_getter_and_setter_reg(cpBody, Moment),
        class_getter_and_setter_multi_reg(cpBody, Position),
        class_getter_and_setter_multi_reg(cpBody, CenterOfGravity),
        class_getter_and_setter_multi_reg(cpBody, Velocity),
        class_getter_and_setter_multi_reg(cpBody, Force),
        {0}
    };
    luaL_register(l, NULL, bodyMethods);
    lua_pop(l, 1);

    luaL_newmetatable(l, "cpShape");
    luaL_Reg shapeMethods[] = {
        class_method_reg(cpShape, __index),
        class_method_reg(cpShape, __newindex),
        class_method_reg(cpShape, __gc),
        class_method_reg(cpShape, RemoveFromSpace),
        class_getter_and_setter_reg(cpShape, Sensor),
        {0}
    };
    luaL_register(l, NULL, shapeMethods);
    lua_pop(l, 1);

    return 0;
}