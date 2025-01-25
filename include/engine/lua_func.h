#ifndef AF748BAB_8CD4_4319_906B_B206A59C10F9
#define AF748BAB_8CD4_4319_906B_B206A59C10F9

#include "lua_doc.h"

#define l_func_0_0(f, fdesc) \
    int L_##f(lua_State *l) { f(); return 0; } \
    static const FuncDoc doc_##f = { .name = #f, .desc = fdesc, .nArgs = 0, .nRets = 0 };

#define l_func_1_0(f, fdesc, \
                    a1, a1type, a1desc, a1default) \
    int L_##f(lua_State *l) { f(luaL_check##a1type(l, 1)); return 0; } \
    static const VarDoc doc_##f##_args[] = { \
        { .name = #a1, .type = #a1type, .desc = a1desc, .dflt = a1default } \
    }; \
    static const FuncDoc doc_##f = { \
        .name = #f, .desc = fdesc, \
        .nArgs = sizeof(doc_##f##_args) / sizeof(doc_##f##_args[0]), .args = doc_##f##_args, \
        .nRets = 0 \
    };

#define l_func_2_0(f, at, at2) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2)); return 0; }
#define l_func_3_0(f, at, at2, at3) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3)); return 0; }
#define l_func_4_0(f, at, at2, at3, at4) int L_##f(lua_State *l) { f(luaL_check##at(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3), luaL_check##at4(l, 4)); return 0; }

#define l_func_0_1(f, rt) int L_##f(lua_State *l) { lua_push##rt(l, f()); return 1; }
#define l_func_1_1(f, at, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(luaL_check##at(l, 1))); return 1; }
#define l_func_2_1(f, at, at2, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(luaL_check##at(l, 1), luaL_check##at2(l, 2))); return 1; }

#define l_func_0_vec2(f, vt) int L_##f(lua_State *l) { vt v = f(); lua_pushnumber(l, v.x); lua_pushnumber(l, v.y); return 2; }
#define l_func_1_vec2(f, at, vt) int L_##f(lua_State *l) { vt v = f(luaL_check##at(l, 1)); lua_pushnumber(l, v.x); lua_pushnumber(l, v.y); return 2; }

#define l_func_3_Color(f, at1, at2, at3) \
int L_##f(lua_State *l) { \
    Color c = f(luaL_check##at1(l, 1), luaL_check##at2(l, 2), luaL_check##at3(l, 3)); \
    lua_pushinteger(l, (uint32_t)ColorToInt(c)); \
    return 1; \
}

#define l_func_1_ud(f, at, ud, isValid) int L_##f(lua_State *l) { \
    ud o = f(lua_to##at(l, 1)); \
    if (isValid(o)) { \
        ud* od = lua_newuserdata(l, sizeof(ud)); \
        *od = o; \
        luaL_setmetatable(l, #ud); \
        return 1; \
    } \
    return 0; \
}

#define l_func_reg(f) {.name = #f, .func = L_##f}

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

#define doc_module_constants(...) const VarDoc constants[] = {__VA_ARGS__};
#define doc_module_funcs(...) const FuncDoc funcs[] = {__VA_ARGS__};
#define doc_module_classes(...) const ClassDoc classes[] = {__VA_ARGS__};
#define doc_module(m, mdesc, ...) { \
    __VA_ARGS__ \
    const ModuleDoc m = { \
        .name = #m, .desc = mdesc, \
        .constants = constants, .nConstants = sizeof(constants)/sizeof(VarDoc), \
        .funcs = funcs, .nFuncs = sizeof(funcs)/sizeof(FuncDoc), \
        .classes = classes, .nClasses = sizeof(classes)/sizeof(ClassDoc), \
    }; \
    SaveModuleDoc(&m); \
}

#endif /* AF748BAB_8CD4_4319_906B_B206A59C10F9 */
