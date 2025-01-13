#include <engine/lua.h>
#include <util/lua_class.h>
#include <raylib.h>

int L_color_FromHSV(lua_State *l) {
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

int L_time___getFrameTime(lua_State *l) {
    lua_pushnumber(l, GetFrameTime());
    return 1;
}

int L_time___index(lua_State *l) { /* [t, k] */
    lua_pushstring(l, "__get"); /* [t, k, "__get"] */
    lua_insert(l, 2); /*[ t, "__get", k ]*/
    lua_concat(l, 2); /*[ t, "__getk" ]*/
    const char *name = lua_tostring(l, -1);
    lua_rawget(l, 1); /*[ t, __getk ]*/
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {
        lua_pcall(l, 0, 1, 0);   /* [ t, v ] */
        return 1;
    } else {
        fprintf(stderr, "time has no field %s\n", name);
    }
    return 0;
}

int luaopen_raylib(lua_State *l) {
    luaL_Reg colorFunctions[] = {
        class_method_reg(color, FromHSV),
        {0}
    };
    luaL_register(l, "color", colorFunctions);
    lua_pop(l, 1);
    luaL_Reg timeFunctions[] = {
        class_method_reg(time, __index),
        class_getter_reg(time, FrameTime),
        {0}
    };
    luaL_register(l, "time", timeFunctions);
    lua_pushvalue(l, -1);
    lua_setmetatable(l, -1);
    lua_pop(l, 1);
    return 0;
}