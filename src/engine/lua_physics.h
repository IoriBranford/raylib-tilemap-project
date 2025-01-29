#ifndef CCBBB07B_1EA8_4B8E_B008_3EC69165193F
#define CCBBB07B_1EA8_4B8E_B008_3EC69165193F

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

void L_PointQuery_iter(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient, lua_State *l);
void L_SegmentQuery_iter(cpShape *shape, cpFloat t, cpVect n, lua_State *l);

int luaopen_cpSpace(lua_State *l);
int luaopen_cpBody(lua_State *l);
int luaopen_cpShape(lua_State *l);
int luaopen_cpArbiter(lua_State *l);

#endif /* CCBBB07B_1EA8_4B8E_B008_3EC69165193F */
