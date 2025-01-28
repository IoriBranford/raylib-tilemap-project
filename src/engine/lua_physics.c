#include <engine/lua.h>
#include <engine/physics.h>

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

class_index_and_newindex(cpBody)
class_getterf_and_setterf(cpBody, *, number, Angle, cpBodyGetAngle, cpBodySetAngle)
class_getterf_and_setterf(cpBody, *, number, AngularVelocity, cpBodyGetAngularVelocity, cpBodySetAngularVelocity)
class_getterf_and_setterf(cpBody, *, number, Torque, cpBodyGetTorque, cpBodySetTorque)
class_getterf_and_setterf(cpBody, *, number, Mass, cpBodyGetMass, cpBodySetMass)
class_getterf_and_setterf(cpBody, *, number, Moment, cpBodyGetMoment, cpBodySetMoment)
class_getterf_and_setterf_vec2(cpBody, *, cpVect, Position, cpBodyGetPosition, cpBodySetPosition)
class_getterf_and_setterf_vec2(cpBody, *, cpVect, CenterOfGravity, cpBodyGetCenterOfGravity, cpBodySetCenterOfGravity)
class_getterf_and_setterf_vec2(cpBody, *, cpVect, Velocity, cpBodyGetVelocity, cpBodySetVelocity)
class_getterf_and_setterf_vec2(cpBody, *, cpVect, Force, cpBodyGetForce, cpBodySetForce)

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
    class_newuserdata(l, cpArbiter, arbiter);
    if (lua_pcall(l, 1, 0, 0) != LUA_OK) lua_error(l);
}

int L_cpBody_EachArbiter(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    if (lua_isfunction(l, 2))
        cpBodyEachArbiter(body, (cpBodyArbiterIteratorFunc)L_cpBody_EachArbiter_iter, l);
    return 0;
}

class_gc(cpBody, *, ReleaseOrphanedBody)

int L_cpBody_RemoveFromSpace(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpSpace *space = cpBodyGetSpace(body);
    if (space)
        cpSpaceRemoveBody(space, body);
    return 0;
}

class_luaopen(cpBody,
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
    class_getter_and_setter_reg(cpBody, Position),
    class_getter_and_setter_reg(cpBody, CenterOfGravity),
    class_getter_and_setter_reg(cpBody, Velocity),
    class_getter_and_setter_reg(cpBody, Force)
)

class_index_and_newindex(cpShape)

class_gc(cpShape, *, ReleaseOrphanedShape)
class_getterf_and_setterf_ud(cpShape, *, cpBody, *, Body, cpShapeGetBody, cpShapeSetBody)
class_getterf_and_setterf(cpShape, *, number, Mass, cpShapeGetMass, cpShapeSetMass)
class_getterf_and_setterf(cpShape, *, number, Density, cpShapeGetDensity, cpShapeSetDensity)
class_getterf(cpShape, *, number, Moment, cpShapeGetMoment)
class_getterf(cpShape, *, number, Area, cpShapeGetArea)
class_getterf_vec2(cpShape, *, cpVect, CenterOfGravity, cpShapeGetCenterOfGravity)
class_getterf_and_setterf(cpShape, *, boolean, Sensor, cpShapeGetSensor, cpShapeSetSensor)
class_getterf_and_setterf(cpShape, *, number, Elasticity, cpShapeGetElasticity, cpShapeSetElasticity)
class_getterf_and_setterf(cpShape, *, number, Friction, cpShapeGetFriction, cpShapeSetFriction)
class_getterf_and_setterf_vec2(cpShape, *, cpVect, SurfaceVelocity, cpShapeGetSurfaceVelocity, cpShapeSetSurfaceVelocity)

int L_cpShape_getFilter(lua_State *l) {
    cpShape **shape = luaL_checkudata(l, 1, "cpShape");
    cpShapeFilter filter = cpShapeGetFilter(*shape);
    lua_pushinteger(l, filter.group);
    lua_pushinteger(l, filter.categories);
    lua_pushinteger(l, filter.mask);
    return 3;
}

int L_cpShape_setFilter(lua_State *l) {
    cpShape **shape = luaL_checkudata(l, 1, "cpShape");
    cpShapeFilter filter = cpShapeGetFilter(*shape);
    if (lua_isnumber(l, 2)) filter.group = floor(lua_tonumber(l, 2));
    if (lua_isnumber(l, 3)) filter.categories = floor(lua_tonumber(l, 3));
    if (lua_isnumber(l, 4)) filter.mask = floor(lua_tonumber(l, 4));
    cpShapeSetFilter(*shape, filter);
    return 0;
}

int L_cpShape_RemoveFromSpace(lua_State *l) {
    cpShape **ud = luaL_checkudata(l, 1, "cpShape");
    cpSpace *space = cpShapeGetSpace(*ud);
    if (space)
        cpSpaceRemoveShape(space, *ud);
    return 0;
}

class_luaopen(cpShape,
    class_method_reg(cpShape, __index),
    class_method_reg(cpShape, __newindex),
    class_method_reg(cpShape, __gc),
    class_getter_and_setter_reg(cpShape, Body),
    class_getter_and_setter_reg(cpShape, Mass),
    class_getter_and_setter_reg(cpShape, Density),
    class_getter_reg(cpShape, Moment),
    class_getter_reg(cpShape, Area),
    class_getter_reg(cpShape, CenterOfGravity),
    class_getter_and_setter_reg(cpShape, Sensor),
    class_getter_and_setter_reg(cpShape, Elasticity),
    class_getter_and_setter_reg(cpShape, Friction),
    class_getter_and_setter_reg(cpShape, SurfaceVelocity),
    class_getter_and_setter_reg(cpShape, Filter),
    class_method_reg(cpShape, RemoveFromSpace)
)

class_index_and_newindex(cpArbiter)
class_getterf_and_setterf(cpArbiter, *, number, Restitution, cpArbiterGetRestitution, cpArbiterSetRestitution)
class_getterf_and_setterf(cpArbiter, *, number, Friction, cpArbiterGetFriction, cpArbiterSetFriction)
class_getterf_and_setterf_vec2(cpArbiter, *, cpVect, SurfaceVelocity, cpArbiterGetSurfaceVelocity, cpArbiterSetSurfaceVelocity)

/// "This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback."
// class_getterf_vec2(cpArbiter, *, cpVect, TotalImpulse, cpArbiterTotalImpulse)
// class_getterf_vec2(cpArbiter, *, cpVect, KE, cpArbiterTotalKE)

class_func_0_2ud(cpArbiter, *, GetShapes, cpArbiterGetShapes, cpShape, *, cpShape, *)
class_func_0_2ud(cpArbiter, *, GetBodies, cpArbiterGetBodies, cpBody, *, cpBody, *)

// TODO? ContactPoints

class_getterf(cpArbiter, *, boolean, IsFirstContact, cpArbiterIsFirstContact)
class_getterf(cpArbiter, *, boolean, IsRemoval, cpArbiterIsRemoval)
class_getterf(cpArbiter, *, integer, NumContactPoints, cpArbiterGetCount)
class_getterf_vec2(cpArbiter, *, cpVect, Normal, cpArbiterGetNormal)
class_func_1_vec2(cpArbiter, *, GetPointA, cpArbiterGetPointA, integer, cpVect)
class_func_1_vec2(cpArbiter, *, GetPointB, cpArbiterGetPointB, integer, cpVect)
class_func_1_1(cpArbiter, *, GetDepth, cpArbiterGetDepth, integer, number)

class_luaopen(cpArbiter,
    class_method_reg(cpArbiter, __index),
    class_method_reg(cpArbiter, __newindex),
    class_getter_and_setter_reg(cpArbiter, Restitution),
    class_getter_and_setter_reg(cpArbiter, Friction),
    class_getter_and_setter_reg(cpArbiter, SurfaceVelocity),
    class_method_reg(cpArbiter, GetShapes),
    class_method_reg(cpArbiter, GetBodies),
    class_getter_reg(cpArbiter, IsFirstContact),
    class_getter_reg(cpArbiter, IsRemoval),
    class_getter_reg(cpArbiter, NumContactPoints),
    class_getter_reg(cpArbiter, Normal),
    class_method_reg(cpArbiter, GetPointA),
    class_method_reg(cpArbiter, GetPointB),
    class_method_reg(cpArbiter, GetDepth))

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

    lua_cpcall(l, luaopen_cpBody, NULL);
    lua_cpcall(l, luaopen_cpShape, NULL);
    lua_cpcall(l, luaopen_cpArbiter, NULL);

    return 0;
}