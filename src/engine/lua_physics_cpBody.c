#include "lua_physics.h"

int L_cpBody_NewBody(lua_State *l) {
    cpBody *body = cpBodyNew(luaL_optnumber(l, 1, 1), luaL_optnumber(l, 2, HUGE_VAL));
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpBody, body);
    return 1;
}

int L_cpBody_NewKinematicBody(lua_State *l) {
    cpBody *body = cpBodyNewKinematic();
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpBody, body);
    return 1;
}

int L_cpBody_NewStaticBody(lua_State *l) {
    cpBody *body = cpBodyNewStatic();
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpBody, body);
    return 1;
}

class_index_and_newindex(cpBody)
class_gc(cpBody, *, ReleaseOrphanedBody)
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
    class_method_reg(cpBody, NewBody),
    class_method_reg(cpBody, NewKinematicBody),
    class_method_reg(cpBody, NewStaticBody),
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