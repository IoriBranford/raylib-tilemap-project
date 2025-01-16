#ifndef AF748BAB_8CD4_4319_906B_B206A59C10F9
#define AF748BAB_8CD4_4319_906B_B206A59C10F9

#define l_func_0_0(f) int L_##f(lua_State *l) { f(); return 0; }
#define l_func_1_0(f, at) int L_##f(lua_State *l) { f(luaL_check##at(l, 1)); return 0; }
#define l_func_2_0(f, at, at2) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2)); return 0; }
#define l_func_0_1(f, rt) int L_##f(lua_State *l) { lua_push##rt(l, f()); return 1; }
#define l_func_1_1(f, at, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(luaL_check##at(l, 1))); return 1; }
#define l_func_2_1(f, at, at2, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(luaL_check##at(l, 1), luaL_check##at2(l, 2))); return 1; }
#define l_func_4_0(f, at, at2, at3, at4) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3), luaL_check##at4(l, 4)); return 0; }

#define l_func_0_vec2(f, vt) int L_##f(lua_State *l) { vt v = f(); lua_pushnumber(l, v.x); lua_pushnumber(l, v.y); return 2; }

#define l_func_3_Color(f, at1, at2, at3) \
int L_##f(lua_State *l) { \
    Color c = f(luaL_check##at1(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3)); \
    lua_pushnumber(l, c.r); \
    lua_pushnumber(l, c.g); \
    lua_pushnumber(l, c.b); \
    lua_pushnumber(l, c.a); \
    return 4; \
}

#define l_func_1_ud(f, at, ud) int L_##f(lua_State *l) { \
    ud *o = f(lua_to##at(l, 1)); \
    if (o) { \
        ud** od = lua_newuserdata(l, sizeof(ud*)); \
        *od = o; \
        luaL_setmetatable(l, #ud); \
        return 1; \
    } \
    return 0; \
}

#define l_func_reg(f) {.name = #f, .func = L_##f}

#define l_global_enum(l, e) { lua_pushinteger(l, e); lua_setglobal(l, #e); }

#endif /* AF748BAB_8CD4_4319_906B_B206A59C10F9 */
