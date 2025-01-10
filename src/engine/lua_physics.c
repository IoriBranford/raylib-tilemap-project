#include <engine/lua.h>
#include <util/lua_class.h>
#include <chipmunk.h>

int L_physics_body(lua_State *l) {
    cpFloat mass = luaL_optnumber(l, 1, 0);
    cpFloat moment = luaL_optnumber(l, 2, HUGE_VAL);
    class_newuserdata(l, cpBody, cpBodyNew(mass, moment));
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
    class_newuserdata(l, cpShape, cpCircleShapeNew(body, radius, offset));
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
    
    luaL_checktype(l, 2, LUA_TTABLE);
    int len = lua_objlen(l, 2);
    int nVerts = len/2;
    cpVect *verts = calloc(sizeof(cpVect), nVerts);
    cpVect *vert = verts;
    for (int i = 2; i <= len; i += 2) {
        lua_rawgeti(l, 2, i-1);
        lua_rawgeti(l, 2, i);
        vert->x = luaL_checknumber(l, -2);
        vert->y = luaL_checknumber(l, -1);
        lua_pop(l, 2);
        ++vert;
    }

    class_newuserdata(l, cpShape, cpPolyShapeNew(body, nVerts, verts, cpTransformIdentity, 0));

    free(verts);
    return 1;
}

#define cp_getter(cls, ctype, luatype, field) \
int L_##cls##___get##field(lua_State *l) { \
    cls **ud = luaL_checkudata(l, 1, #cls); \
    ctype v = cls##Get##field(*ud); \
    lua_push##luatype(l, v); \
    return 1; \
}

#define cp_setter(cls, ctype, luatype, field) \
int L_##cls##___set##field(lua_State *l) { \
    cls **ud = luaL_checkudata(l, 1, #cls); \
    ctype v = luaL_check##luatype(l, 2); \
    cls##Set##field(*ud, v); \
    return 0; \
}

#define cp_getter_and_setter(cls, ctype, luatype, field) \
    cp_getter(cls, ctype, luatype,field) \
    cp_setter(cls, ctype, luatype,field)

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
cp_getter_and_setter(cpBody, cpFloat, number, Angle)
cp_getter_and_setter(cpBody, cpFloat, number, AngularVelocity)
cp_getter_and_setter(cpBody, cpFloat, number, Torque)
cp_getter_and_setter(cpBody, cpFloat, number, Mass)
cp_getter_and_setter(cpBody, cpFloat, number, Moment)
cp_getter_and_setter_vect(cpBody, Position)
cp_getter_and_setter_vect(cpBody, CenterOfGravity)
cp_getter_and_setter_vect(cpBody, Velocity)
cp_getter_and_setter_vect(cpBody, Force)

void iter_removeShape(cpBody *body, cpShape *shape, void *space) {
    cpSpaceRemoveShape(space, shape);
}

void iter_freeShape(cpBody *body, cpShape *shape, void *_) {
    cpShapeFree(shape);
}

void iter_removeConstraint(cpBody *body, cpConstraint *constraint, void *space) {
    cpSpaceRemoveConstraint(space, constraint);
}

void iter_freeConstraint(cpBody *body, cpConstraint *constraint, void *_) {
    cpConstraintFree(constraint);
}

int L_cpBody___gc(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpSpace *space = cpBodyGetSpace(body);
    if (space) {
        cpBodyEachShape(body, iter_removeShape, space);
        cpBodyEachConstraint(body, iter_removeConstraint, space);
        cpSpaceRemoveBody(space, body);
    }
    cpBodyEachShape(body, iter_freeShape, space);
    cpBodyEachConstraint(body, iter_freeConstraint, space);
    cpBodyFree(body);
    *ud = NULL;
    return 0;
}

int L_cpBody_RemoveFromSpace(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpSpace *space = cpBodyGetSpace(body);
    if (space)
        cpSpaceRemoveBody(space, body);
    return 0;
}

class_index_and_newindex(cpShape)

int L_cpShape___gc(lua_State *l) {
    cpShape **ud = luaL_checkudata(l, 1, "cpShape");
    cpShape *shape = *ud;
    if (!cpShapeGetBody(shape) && !cpShapeGetSpace(shape))
        cpShapeFree(shape);
    return 0;
}

int L_cpShape_RemoveFromSpace(lua_State *l) {
    cpShape **ud = luaL_checkudata(l, 1, "cpShape");
    cpSpace *space = cpShapeGetSpace(*ud);
    if (space)
        cpSpaceRemoveShape(space, *ud);
    return 0;
}

cp_getter_and_setter(cpShape, cpBool, boolean, Sensor)

int luaopen_physics(lua_State *l) {
    luaL_Reg staticMethods[] = {
        class_method_reg(physics, body),
        {0}
    };
    luaL_register(l, "physics", staticMethods);
    lua_pop(l, 1);

    luaL_newmetatable(l, "cpBody");
    luaL_Reg bodyMethods[] = {
        class_method_reg(cpBody, __index),
        class_method_reg(cpBody, __newindex),
        class_method_reg(cpBody, __gc),
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