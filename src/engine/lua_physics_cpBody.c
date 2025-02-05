#include "lua_physics.h"

int L_cpBody_NewBody(lua_State *l) {
    cpBody *body = cpBodyNew(luaL_optnumber(l, 1, 1), luaL_optnumber(l, 2, HUGE_VAL));
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    lclass_newuserdata(l, cpBody, body);
    return 1;
}

int L_cpBody_NewKinematicBody(lua_State *l) {
    cpBody *body = cpBodyNewKinematic();
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    lclass_newuserdata(l, cpBody, body);
    return 1;
}

int L_cpBody_NewStaticBody(lua_State *l) {
    cpBody *body = cpBodyNewStatic();
    cpBodySetUserData(body, (cpDataPointer)LUA_REFNIL);
    lclass_newuserdata(l, cpBody, body);
    return 1;
}

lclass_index_and_newindex(cpBody)
lclass_gc(cpBody, *, ReleaseOrphanedBody)
lclass_getterf_and_setterf(cpBody, *, number, Angle, cpBodyGetAngle, cpBodySetAngle)
lclass_getterf_and_setterf(cpBody, *, number, AngularVelocity, cpBodyGetAngularVelocity, cpBodySetAngularVelocity)
lclass_getterf_and_setterf(cpBody, *, number, Torque, cpBodyGetTorque, cpBodySetTorque)
lclass_getterf_and_setterf(cpBody, *, number, Mass, cpBodyGetMass, cpBodySetMass)
lclass_getterf_and_setterf(cpBody, *, number, Moment, cpBodyGetMoment, cpBodySetMoment)
lclass_getterf_and_setterf_vec2(cpBody, *, cpVect, Position, cpBodyGetPosition, cpBodySetPosition)
lclass_getterf_and_setterf_vec2(cpBody, *, cpVect, CenterOfGravity, cpBodyGetCenterOfGravity, cpBodySetCenterOfGravity)
lclass_getterf_and_setterf_vec2(cpBody, *, cpVect, Velocity, cpBodyGetVelocity, cpBodySetVelocity)
lclass_getterf_and_setterf_vec2(cpBody, *, cpVect, Force, cpBodyGetForce, cpBodySetForce)
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
    lclass_newuserdata(l, cpShape, shape);
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
    lclass_newuserdata(l, cpArbiter, arbiter);
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
        lclass_newuserdata(l, cpShape, nearestShape);
        lua_pushnumber(l, info.alpha);
        lua_pushnumber(l, info.point.x);
        lua_pushnumber(l, info.point.y);
        return 4;
    }
    return 0;
}

lclass_luaopen(cpBody,
    lclass_method_reg(cpBody, NewBody),
    lclass_method_reg(cpBody, NewKinematicBody),
    lclass_method_reg(cpBody, NewStaticBody),
    lclass_method_reg(cpBody, __index),
    lclass_method_reg(cpBody, __newindex),
    lclass_method_reg(cpBody, __gc),
    lclass_method_reg(cpBody, NewCircleShape),
    lclass_method_reg(cpBody, UpdateSprite),
    lclass_method_reg(cpBody, EachArbiter),
    lclass_method_reg(cpBody, RemoveFromSpace),
    lclass_method_reg(cpBody, PointQuery),
    lclass_method_reg(cpBody, PointQueryNearest),
    lclass_method_reg(cpBody, SegmentQuery),
    lclass_method_reg(cpBody, SegmentQueryFirst),
    lclass_getter_and_setter_reg(cpBody, Angle),
    lclass_getter_and_setter_reg(cpBody, AngularVelocity),
    lclass_getter_and_setter_reg(cpBody, Torque),
    lclass_getter_and_setter_reg(cpBody, Mass),
    lclass_getter_and_setter_reg(cpBody, Moment),
    lclass_getter_and_setter_reg(cpBody, Position),
    lclass_getter_and_setter_reg(cpBody, CenterOfGravity),
    lclass_getter_and_setter_reg(cpBody, Velocity),
    lclass_getter_and_setter_reg(cpBody, Force),
    lclass_getter_and_setter_reg(cpBody, UserData)
)