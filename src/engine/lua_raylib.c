#include <engine/lua.h>
#include <util/lua_class.h>
#include <raylib.h>

l_func_0_1(GetFrameTime, number)

int L_ColorFromHSV(lua_State *l) {
    lua_Number hue = luaL_checknumber(l, 1);
    lua_Number sat = luaL_checknumber(l, 2);
    lua_Number val = luaL_checknumber(l, 3);
    Color c = ColorFromHSV(hue, sat, val);
    lua_pushnumber(l, c.r);
    lua_pushnumber(l, c.g);
    lua_pushnumber(l, c.b);
    lua_pushnumber(l, 255);
    return 4;
}

int luaopen_raylib(lua_State *l) {
    lua_getglobal(l, "_G");
    luaL_Reg raylibFunctions[] = {
        l_func_reg(GetFrameTime),
        l_func_reg(ColorFromHSV),
        {0}
    };
    luaL_register(l, NULL, raylibFunctions);
    lua_pop(l, 1);
    return 0;
}