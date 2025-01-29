#include "lua_physics.h"

int L_cpSpace_NewSpace(lua_State *l) {
    cpSpace * o = cpSpaceNew();
    cpSpaceSetUserData(o, LUA_REFNIL);
    class_newuserdata(l, cpSpace, o);
    return 1;
}
class_index_and_newindex(cpSpace)
class_gc(cpSpace, *, ReleaseSpace)

class_getterf_and_setterf(cpSpace, *, number, Iterations, cpSpaceGetIterations, cpSpaceSetIterations)
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
    class_method_reg(cpSpace, NewSpace),
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
    class_method_reg(cpSpace, AddBodyAndShapes),
    class_method_reg(cpSpace, RemoveShape),
    class_method_reg(cpSpace, RemoveBody),
    class_method_reg(cpSpace, RemoveConstraint),
    class_method_reg(cpSpace, ContainsShape),
    class_method_reg(cpSpace, ContainsBody),
    class_method_reg(cpSpace, ContainsConstraint),
    class_method_reg(cpSpace, PointQuery),
    class_method_reg(cpSpace, PointQueryNearest),
    class_method_reg(cpSpace, SegmentQuery),
    class_method_reg(cpSpace, SegmentQueryFirst),
    class_method_reg(cpSpace, Step)
)