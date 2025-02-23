#ifndef AF748BAB_8CD4_4319_906B_B206A59C10F9
#define AF748BAB_8CD4_4319_906B_B206A59C10F9

#include "lua_doc.h"

#define lfunc_0_0(f) int L_##f(lua_State *l) { f(); return 0; }
#define lfunc_1_0(f, at) int L_##f(lua_State *l) { f(luaL_check##at(l, 1)); return 0; }
#define lfunc_2_0(f, at, at2) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2)); return 0; }
#define lfunc_3_0(f, at, at2, at3) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3)); return 0; }
#define lfunc_4_0(f, at, at2, at3, at4) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3), luaL_check##at4(l, 4)); return 0; }

#define lfunc_0_1(f, rt) int L_##f(lua_State *l) { lua_push##rt(l, f()); return 1; }
#define lfunc_1_1(f, at, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(luaL_check##at(l, 1))); return 1; }
#define lfunc_2_1(f, at, at2, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(luaL_check##at(l, 1), luaL_check##at2(l, 2))); return 1; }

#define lfunc_0_vec2(f, vt) int L_##f(lua_State *l) { vt v = f(); lua_pushnumber(l, v.x); lua_pushnumber(l, v.y); return 2; }
#define lfunc_1_vec2(f, at, vt) int L_##f(lua_State *l) { vt v = f(luaL_check##at(l, 1)); lua_pushnumber(l, v.x); lua_pushnumber(l, v.y); return 2; }

#define lfunc_3_Color(f, at1, at2, at3) \
int L_##f(lua_State *l) { \
    Color c = f(luaL_check##at1(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3)); \
    lua_pushinteger(l, (uint32_t)ColorToInt(c)); \
    return 1; \
}

#define lfunc_1_ud(f, at, ud, isValid) int L_##f(lua_State *l) { \
    ud o = f(lua_to##at(l, 1)); \
    if (isValid(o)) { \
        ud* od = lua_newuserdata(l, sizeof(ud)); \
        *od = o; \
        luaL_setmetatable(l, #ud); \
        return 1; \
    } \
    return 0; \
}

#define lfunc_reg(f) {.name = #f, .func = L_##f}

#define l_global_funcs_luaopen(grp, ...) \
int luaopen_##grp(lua_State *l) { \
    lua_getglobal(l, "_G"); \
    luaL_Reg r[] = { __VA_ARGS__, {0} }; \
    luaL_register(l, NULL, r); \
    return 0; \
}

#define l_global_enum(l, e) { \
    lua_pushinteger(l, e); \
    lua_setglobal(l, #e); \
}

#endif /* AF748BAB_8CD4_4319_906B_B206A59C10F9 */
