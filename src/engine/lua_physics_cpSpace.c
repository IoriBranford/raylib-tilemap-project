#include "lua_physics.h"

int L_cpSpace_NewSpace(lua_State *l) {
    cpSpace * o = cpSpaceNew();
    cpSpaceSetUserData(o, LUA_REFNIL);
    lclass_newuserdata(l, cpSpace, o);
    return 1;
}
lclass_index_and_newindex(cpSpace)
lclass_gc(cpSpace, *, ReleaseSpace)

lclass_getterf_and_setterf(cpSpace, *, number, Iterations, cpSpaceGetIterations, cpSpaceSetIterations)
lclass_getterf_and_setterf_vec2(cpSpace, *, cpVect, Gravity, cpSpaceGetGravity, cpSpaceSetGravity)
lclass_getterf_and_setterf(cpSpace, *, number, Damping, cpSpaceGetDamping, cpSpaceSetDamping)
lclass_getterf_and_setterf(cpSpace, *, number, IdleSpeedThreshold, cpSpaceGetIdleSpeedThreshold, cpSpaceSetIdleSpeedThreshold)
lclass_getterf_and_setterf(cpSpace, *, number, SleepTimeThreshold, cpSpaceGetSleepTimeThreshold, cpSpaceSetSleepTimeThreshold)
lclass_getterf_and_setterf(cpSpace, *, number, CollisionSlop, cpSpaceGetCollisionSlop, cpSpaceSetCollisionSlop)
lclass_getterf_and_setterf(cpSpace, *, number, CollisionBias, cpSpaceGetCollisionBias, cpSpaceSetCollisionBias)
lclass_getterf_and_setterf(cpSpace, *, number, CollisionPersistence, cpSpaceGetCollisionPersistence, cpSpaceSetCollisionPersistence)
cp_getter_and_setter_userdata(cpSpace)
lclass_getterf_ud(cpSpace, *, cpBody, *, StaticBody, cpSpaceGetStaticBody)
lclass_getterf(cpSpace, *, number, TimeStep, cpSpaceGetCurrentTimeStep)
lclass_getterf(cpSpace, *, boolean, Locked, cpSpaceIsLocked)

// TODO Collision handlers?

lclass_func_ud_ud(cpSpace, *, AddShape, cpSpaceAddShape, cpShape, *, cpShape, *)
lclass_func_ud_ud(cpSpace, *, AddBody, cpSpaceAddBody, cpBody, *, cpBody, *)
lclass_func_ud_ud(cpSpace, *, AddConstraint, cpSpaceAddConstraint, cpConstraint, *, cpConstraint, *)

void L_cpSpace_AddBodyAndShapes_iter(cpBody *body, cpShape *shape, cpSpace *space) {
    cpSpaceAddShape(space, shape);
}

int L_cpSpace_AddBodyAndShapes(lua_State *l) {
    cpSpace **space = (cpSpace **)luaL_checkudata(l, 1, "cpSpace");
    cpBody **body = (cpBody **)luaL_checkudata(l, 2, "cpBody");
    cpSpaceAddBody(*space, *body);
    cpBodyEachShape(*body, (cpBodyShapeIteratorFunc)L_cpSpace_AddBodyAndShapes_iter, *space);
    return 1;
}

lclass_func_ud_0(cpSpace, *, RemoveShape, cpSpaceRemoveShape, cpShape, *)
lclass_func_ud_0(cpSpace, *, RemoveBody, cpSpaceRemoveBody, cpBody, *)
lclass_func_ud_0(cpSpace, *, RemoveConstraint, cpSpaceRemoveConstraint, cpConstraint, *)

lclass_func_ud_1(cpSpace, *, ContainsShape, cpSpaceContainsShape, cpShape, *, boolean)
lclass_func_ud_1(cpSpace, *, ContainsBody, cpSpaceContainsBody, cpBody, *, boolean)
lclass_func_ud_1(cpSpace, *, ContainsConstraint, cpSpaceContainsConstraint, cpConstraint, *, boolean)

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
        lclass_newuserdata(l, cpShape, nearestShape);
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
        lclass_newuserdata(l, cpShape, nearestShape);
        lua_pushnumber(l, info.alpha);
        lua_pushnumber(l, info.point.x);
        lua_pushnumber(l, info.point.y);
        return 4;
    }
    return 0;
}

// TODO Iteration
// Indexing?

lclass_func_1_0(cpSpace, *, Step, cpSpaceStep, number)

lclass_luaopen(cpSpace,
    lclass_method_reg(cpSpace, NewSpace),
    lclass_method_reg(cpSpace, __index),
    lclass_method_reg(cpSpace, __newindex),
    lclass_method_reg(cpSpace, __gc),
    lclass_getter_and_setter_reg(cpSpace, Iterations),
    lclass_getter_and_setter_reg(cpSpace, Gravity),
    lclass_getter_and_setter_reg(cpSpace, Damping),
    lclass_getter_and_setter_reg(cpSpace, IdleSpeedThreshold),
    lclass_getter_and_setter_reg(cpSpace, SleepTimeThreshold),
    lclass_getter_and_setter_reg(cpSpace, CollisionSlop),
    lclass_getter_and_setter_reg(cpSpace, CollisionBias),
    lclass_getter_and_setter_reg(cpSpace, CollisionPersistence),
    lclass_getter_and_setter_reg(cpSpace, UserData),
    lclass_getter_reg(cpSpace, StaticBody),
    lclass_getter_reg(cpSpace, TimeStep),
    lclass_getter_reg(cpSpace, Locked),
    lclass_method_reg(cpSpace, AddShape),
    lclass_method_reg(cpSpace, AddBody),
    lclass_method_reg(cpSpace, AddConstraint),
    lclass_method_reg(cpSpace, AddBodyAndShapes),
    lclass_method_reg(cpSpace, RemoveShape),
    lclass_method_reg(cpSpace, RemoveBody),
    lclass_method_reg(cpSpace, RemoveConstraint),
    lclass_method_reg(cpSpace, ContainsShape),
    lclass_method_reg(cpSpace, ContainsBody),
    lclass_method_reg(cpSpace, ContainsConstraint),
    lclass_method_reg(cpSpace, PointQuery),
    lclass_method_reg(cpSpace, PointQueryNearest),
    lclass_method_reg(cpSpace, SegmentQuery),
    lclass_method_reg(cpSpace, SegmentQueryFirst),
    lclass_method_reg(cpSpace, Step)
)