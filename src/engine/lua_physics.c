#include <engine/lua.h>
#include <engine/physics.h>

#define cp_setter_userdata(cls) \
int L_##cls##_setUserData(lua_State *l) { \
    cls *o = *(cls**)luaL_checkudata(l, 1, #cls); \
    int ref = (int)cls##GetUserData(o); \
    if (ref != LUA_REFNIL) \
        luaL_unref(l, LUA_REGISTRYINDEX, ref); \
    if (lua_isnoneornil(l, 2)) \
        ref = LUA_REFNIL; \
    else \
        ref = luaL_ref(l, LUA_REGISTRYINDEX); \
    cls##SetUserData(o, (cpDataPointer)ref); \
    return 0; \
}

#define cp_getter_userdata(cls) \
int L_##cls##_getUserData(lua_State *l) { \
    cls *o = *(cls**)luaL_checkudata(l, 1, #cls); \
    int ref = (int)cls##GetUserData(o); \
    if (ref != LUA_REFNIL) { \
        lua_rawgeti(l, LUA_REGISTRYINDEX, ref); \
        return 1; \
    } \
    return 0; \
}

#define cp_getter_and_setter_userdata(cls) \
    cp_getter_userdata(cls) \
    cp_setter_userdata(cls)

void L_PointQuery_iter(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient, lua_State *l) {
    lua_pushvalue(l, -1);
    class_newuserdata(l, cpShape, shape);
    lua_pushnumber(l, point.x);
    lua_pushnumber(l, point.y);
    lua_pushnumber(l, distance);
    lua_pushnumber(l, gradient.x);
    lua_pushnumber(l, gradient.y);
    if (lua_pcall(l, 6, 0, 0) != LUA_OK) lua_error(l);
}

void L_SegmentQuery_iter(cpShape *shape, cpFloat t, cpVect n, lua_State *l) {
    lua_pushvalue(l, -1);
    class_newuserdata(l, cpShape, shape);
    lua_pushnumber(l, t);
    lua_pushnumber(l, n.x);
    lua_pushnumber(l, n.y);
    if (lua_pcall(l, 4, 0, 0) != LUA_OK) lua_error(l);
}

class_ctor_0(cpSpace, *, cpSpaceNew, )
class_index_and_newindex(cpSpace)
class_gc(cpSpace, *, ReleaseSpace)

class_getterf_and_setterf(cpSpace, *, integer, Iterations, cpSpaceGetIterations, cpSpaceSetIterations)
class_getterf_and_setterf_vec2(cpSpace, *, cpVect, Gravity, cpSpaceGetGravity, cpSpaceSetGravity)
class_getterf_and_setterf(cpSpace, *, number, Damping, cpSpaceGetDamping, cpSpaceSetDamping)
class_getterf_and_setterf(cpSpace, *, number, IdleSpeedThreshold, cpSpaceGetIdleSpeedThreshold, cpSpaceSetIdleSpeedThreshold)
class_getterf_and_setterf(cpSpace, *, number, SleepTimeThreshold, cpSpaceGetSleepTimeThreshold, cpSpaceSetSleepTimeThreshold)
class_getterf_and_setterf(cpSpace, *, number, CollisionSlop, cpSpaceGetCollisionSlop, cpSpaceSetCollisionSlop)
class_getterf_and_setterf(cpSpace, *, number, CollisionBias, cpSpaceGetCollisionBias, cpSpaceSetCollisionBias)
class_getterf_and_setterf(cpSpace, *, number, CollisionPersistence, cpSpaceGetCollisionPersistence, cpSpaceSetCollisionPersistence)
cp_getter_and_setter_userdata(cpSpace)
class_getterf_ud(cpSpace, *, cpBody, *, StaticBody, cpSpaceGetStaticBody)
class_getterf(cpSpace, *, number, TimeStep, cpSpaceGetCurrentTimeStep)
class_getterf(cpSpace, *, boolean, Locked, cpSpaceIsLocked)

// TODO Collision handlers?

class_func_ud_ud(cpSpace, *, AddShape, cpSpaceAddShape, cpShape, *, cpShape, *)
class_func_ud_ud(cpSpace, *, AddBody, cpSpaceAddBody, cpBody, *, cpBody, *)
class_func_ud_ud(cpSpace, *, AddConstraint, cpSpaceAddConstraint, cpConstraint, *, cpConstraint, *)

class_func_ud_0(cpSpace, *, RemoveShape, cpSpaceRemoveShape, cpShape, *)
class_func_ud_0(cpSpace, *, RemoveBody, cpSpaceRemoveBody, cpBody, *)
class_func_ud_0(cpSpace, *, RemoveConstraint, cpSpaceRemoveConstraint, cpConstraint, *)

class_func_ud_1(cpSpace, *, ContainsShape, cpSpaceContainsShape, cpShape, *, boolean)
class_func_ud_1(cpSpace, *, ContainsBody, cpSpaceContainsBody, cpBody, *, boolean)
class_func_ud_1(cpSpace, *, ContainsConstraint, cpSpaceContainsConstraint, cpConstraint, *, boolean)

// TODO Post-Step Callbacks?

int L_cpSpace_PointQuery(lua_State *l) {
    if (!lua_isfunction(l, 2))
        return 0;
    cpSpace *space = *(cpSpace**)luaL_checkudata(l, 1, "cpSpace");
    cpVect point = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpFloat maxDist = luaL_optnumber(l, 5, 0);
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 6, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 7, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 8, CP_ALL_CATEGORIES),
    };
    lua_pushvalue(l, 2);
    cpSpacePointQuery(space, point, maxDist, filter, (cpSpacePointQueryFunc)L_PointQuery_iter, l);
    return 0;
}

int L_cpSpace_PointQueryNearest(lua_State *l) {
    cpSpace *space = *(cpSpace**)luaL_checkudata(l, 1, "cpSpace");
    cpVect point = cpv(luaL_optnumber(l, 2, 0), luaL_optnumber(l, 3, 0));
    cpFloat maxDist = luaL_optnumber(l, 4, 0);
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 5, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 6, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 7, CP_ALL_CATEGORIES),
    };
    cpPointQueryInfo info;
    cpShape *nearestShape = cpSpacePointQueryNearest(space, point, maxDist, filter, &info);
    if (nearestShape) {
        class_newuserdata(l, cpShape, nearestShape);
        lua_pushnumber(l, info.point.x);
        lua_pushnumber(l, info.point.y);
        lua_pushnumber(l, info.distance);
        lua_pushnumber(l, info.gradient.x);
        lua_pushnumber(l, info.gradient.y);
        return 6;
    }
    return 0;
}

int L_cpSpace_SegmentQuery(lua_State *l) {
    if (!lua_isfunction(l, 2))
        return 0;
    cpSpace *space = *(cpSpace**)luaL_checkudata(l, 1, "cpSpace");
    cpVect start = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpVect end = cpv(luaL_optnumber(l, 5, 0), luaL_optnumber(l, 6, 0));
    cpFloat radius = luaL_optnumber(l, 7, 0);
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 8, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 9, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 10, CP_ALL_CATEGORIES),
    };
    lua_pushvalue(l, 2);
    cpSpaceSegmentQuery(space, start, end, radius, filter,
	    (cpSpaceSegmentQueryFunc)L_SegmentQuery_iter, l);
    return 0;
}

int L_cpSpace_SegmentQueryFirst(lua_State *l) {
    cpSpace *space = *(cpSpace**)luaL_checkudata(l, 1, "cpSpace");
    cpVect start = cpv(luaL_optnumber(l, 2, 0), luaL_optnumber(l, 3, 0));
    cpVect end = cpv(luaL_optnumber(l, 4, 0), luaL_optnumber(l, 5, 0));
    cpFloat radius = luaL_optnumber(l, 6, 0);
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 7, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 8, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 9, CP_ALL_CATEGORIES),
    };
    cpSegmentQueryInfo info;
    cpShape *nearestShape = cpSpaceSegmentQueryFirst(space, start, end, radius, filter, &info);
    if (nearestShape) {
        class_newuserdata(l, cpShape, nearestShape);
        lua_pushnumber(l, info.alpha);
        lua_pushnumber(l, info.point.x);
        lua_pushnumber(l, info.point.y);
        return 4;
    }
    return 0;
}

// TODO Iteration
// Indexing?

class_func_1_0(cpSpace, *, Step, cpSpaceStep, number)

class_luaopen(cpSpace,
    class_method_reg(cpSpace, __index),
    class_method_reg(cpSpace, __newindex),
    class_method_reg(cpSpace, __gc),
    class_getter_and_setter_reg(cpSpace, Iterations),
    class_getter_and_setter_reg(cpSpace, Gravity),
    class_getter_and_setter_reg(cpSpace, Damping),
    class_getter_and_setter_reg(cpSpace, IdleSpeedThreshold),
    class_getter_and_setter_reg(cpSpace, SleepTimeThreshold),
    class_getter_and_setter_reg(cpSpace, CollisionSlop),
    class_getter_and_setter_reg(cpSpace, CollisionBias),
    class_getter_and_setter_reg(cpSpace, CollisionPersistence),
    class_getter_and_setter_reg(cpSpace, UserData),
    class_getter_reg(cpSpace, StaticBody),
    class_getter_reg(cpSpace, TimeStep),
    class_getter_reg(cpSpace, Locked),
    class_method_reg(cpSpace, AddShape),
    class_method_reg(cpSpace, AddBody),
    class_method_reg(cpSpace, AddConstraint),
    class_method_reg(cpSpace, RemoveShape),
    class_method_reg(cpSpace, RemoveBody),
    class_method_reg(cpSpace, RemoveConstraint),
    class_method_reg(cpSpace, ContainsShape),
    class_method_reg(cpSpace, ContainsBody),
    class_method_reg(cpSpace, ContainsConstraint),
    class_method_reg(cpSpace, PointQuery),
    class_method_reg(cpSpace, PointQueryNearest),
    class_method_reg(cpSpace, SegmentQuery),
    class_method_reg(cpSpace, SegmentQueryFirst)
)

int L_physics_body(lua_State *l) {
    cpFloat mass = luaL_optnumber(l, 1, 1);
    cpFloat moment = luaL_optnumber(l, 2, HUGE_VAL);
    cpBody *body = NewBody(0, 0, 0);
    cpBodySetMass(body, mass);
    cpBodySetMoment(body, moment);
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpBody, body);
    return 1;
}

int L_physics_kinematicbody(lua_State *l) {
    cpBody *body = cpBodyNewKinematic();
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpBody, body);
    return 1;
}

int L_physics_staticbody(lua_State *l) {
    cpBody *body = cpBodyNewStatic();
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpBody, body);
    return 1;
}

int L_physics_circleshape(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpFloat radius = luaL_optnumber(l, 2, 1);
    cpVect offset = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpShape *shape = AddBodyCircle(body, radius, offset.x, offset.y);
    cpShapeSetUserData(shape, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpShape, shape);
    return 1;
}

int L_physics_segmentshape(lua_State *l) {
    cpBody **ud = luaL_checkudata(l, 1, "cpBody");
    cpBody *body = *ud;
    cpVect a = cpv(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    cpVect b = cpv(luaL_checknumber(l, 4), luaL_checknumber(l, 5));
    cpFloat radius = luaL_optnumber(l, 6, 0);
    cpShape *shape = cpSegmentShapeNew(body, a, b, radius);
    cpShapeSetUserData(shape, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpShape, shape);
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

    cpShape *shape = cpPolyShapeNew(body, nVerts, verts, cpTransformIdentity, 0);
    cpShapeSetUserData(shape, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpShape, shape);

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
cp_getter_and_setter_userdata(cpBody)

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

int L_cpBody_PointQuery(lua_State *l) {
    if (!lua_isfunction(l, 2))
        return 0;
    cpBody *body = *(cpBody**)luaL_checkudata(l, 1, "cpBody");
    cpSpace *space = cpBodyGetSpace(body);
    if (!space)
        return 0;
    cpFloat maxDist = luaL_optnumber(l, 3, 0);
    cpVect offset = cpv(luaL_optnumber(l, 4, 0), luaL_optnumber(l, 5, 0));
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 6, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 7, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 8, CP_ALL_CATEGORIES),
    };
    cpVect point = cpvadd(cpBodyGetPosition(body), offset);
    lua_pushvalue(l, 2);
    cpSpacePointQuery(space, point, maxDist, filter, (cpSpacePointQueryFunc)L_PointQuery_iter, l);
    return 0;
}

int L_cpBody_PointQueryNearest(lua_State *l) {
    cpBody *body = *(cpBody**)luaL_checkudata(l, 1, "cpBody");
    cpSpace *space = cpBodyGetSpace(body);
    if (!space)
        return 0;
    cpFloat maxDist = luaL_optnumber(l, 2, 0);
    cpVect offset = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 5, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 6, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 7, CP_ALL_CATEGORIES),
    };
    cpVect point = cpvadd(cpBodyGetPosition(body), offset);
    cpPointQueryInfo info;
    cpShape *nearestShape = cpSpacePointQueryNearest(space, point, maxDist, filter, &info);
    if (nearestShape) {
        class_newuserdata(l, cpShape, nearestShape);
        lua_pushnumber(l, info.point.x);
        lua_pushnumber(l, info.point.y);
        lua_pushnumber(l, info.distance);
        lua_pushnumber(l, info.gradient.x);
        lua_pushnumber(l, info.gradient.y);
        return 6;
    }
    return 0;
}

int L_cpBody_SegmentQuery(lua_State *l) {
    if (!lua_isfunction(l, 2))
        return 0;
    cpBody *body = *(cpBody**)luaL_checkudata(l, 1, "cpBody");
    cpSpace *space = cpBodyGetSpace(body);
    if (!space)
        return 0;
    cpVect startOffset = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpVect endOffset = cpv(luaL_optnumber(l, 5, 0), luaL_optnumber(l, 6, 0));
    cpFloat radius = luaL_optnumber(l, 7, 0);
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 8, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 9, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 10, CP_ALL_CATEGORIES),
    };
    cpVect pos = cpBodyGetPosition(body);
    cpVect start = cpvadd(pos, startOffset);
    cpVect end = cpvadd(pos, endOffset);
    lua_pushvalue(l, 2);
    cpSpaceSegmentQuery(space, start, end, radius, filter,
	    (cpSpaceSegmentQueryFunc)L_SegmentQuery_iter, l);
    return 0;
}

int L_cpBody_SegmentQueryFirst(lua_State *l) {
    cpBody *body = *(cpBody**)luaL_checkudata(l, 1, "cpBody");
    cpSpace *space = cpBodyGetSpace(body);
    if (!space)
        return 0;
    cpVect startOffset = cpv(luaL_optnumber(l, 2, 0), luaL_optnumber(l, 3, 0));
    cpVect endOffset = cpv(luaL_optnumber(l, 4, 0), luaL_optnumber(l, 5, 0));
    cpFloat radius = luaL_optnumber(l, 6, 0);
    cpShapeFilter filter = {
        .group = luaL_optinteger(l, 7, CP_NO_GROUP),
        .categories = luaL_optinteger(l, 8, CP_ALL_CATEGORIES),
        .mask = luaL_optinteger(l, 9, CP_ALL_CATEGORIES),
    };
    cpVect pos = cpBodyGetPosition(body);
    cpVect start = cpvadd(pos, startOffset);
    cpVect end = cpvadd(pos, endOffset);
    cpSegmentQueryInfo info;
    cpShape *nearestShape = cpSpaceSegmentQueryFirst(space, start, end, radius, filter, &info);
    if (nearestShape) {
        class_newuserdata(l, cpShape, nearestShape);
        lua_pushnumber(l, info.alpha);
        lua_pushnumber(l, info.point.x);
        lua_pushnumber(l, info.point.y);
        return 4;
    }
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
    class_method_reg(cpBody, PointQuery),
    class_method_reg(cpBody, PointQueryNearest),
    class_method_reg(cpBody, SegmentQuery),
    class_method_reg(cpBody, SegmentQueryFirst),
    class_getter_and_setter_reg(cpBody, Angle),
    class_getter_and_setter_reg(cpBody, AngularVelocity),
    class_getter_and_setter_reg(cpBody, Torque),
    class_getter_and_setter_reg(cpBody, Mass),
    class_getter_and_setter_reg(cpBody, Moment),
    class_getter_and_setter_reg(cpBody, Position),
    class_getter_and_setter_reg(cpBody, CenterOfGravity),
    class_getter_and_setter_reg(cpBody, Velocity),
    class_getter_and_setter_reg(cpBody, Force),
    class_getter_and_setter_reg(cpBody, UserData)
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
cp_getter_and_setter_userdata(cpShape)

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
    class_getter_and_setter_reg(cpShape, UserData),
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

    lua_cpcall(l, luaopen_cpSpace, NULL);
    lua_cpcall(l, luaopen_cpBody, NULL);
    lua_cpcall(l, luaopen_cpShape, NULL);
    lua_cpcall(l, luaopen_cpArbiter, NULL);

    return 0;
}