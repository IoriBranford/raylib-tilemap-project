#include "lua_physics.h"

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

int luaopen_physics(lua_State *l) {
    lua_cpcall(l, luaopen_cpSpace, NULL);
    lua_cpcall(l, luaopen_cpBody, NULL);
    lua_cpcall(l, luaopen_cpShape, NULL);
    lua_cpcall(l, luaopen_cpArbiter, NULL);

    return 0;
}