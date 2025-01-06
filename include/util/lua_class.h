#ifndef CD425245_A2F7_4AB2_ADAB_E5F9A1924686
#define CD425245_A2F7_4AB2_ADAB_E5F9A1924686

#define class_index(cls) \
int L_##cls##___index(lua_State *l) { \
    luaL_checkudata(l, 1, #cls);  /* [ map, k ] */ \
    lua_pushstring(l, "get_");  /* [ map, k, "get_" ] */\
    lua_pushvalue(l, 2);  /* [ map, k, "get_", k ] */\
    lua_concat(l, 2);   /* [ map, k, "get_k" ] */\
    const char *name = lua_tostring(l, -1);\
    lua_pop(l, 1);   /* [ map, k ] */\
    luaL_getmetafield(l, 1, name);\
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {  /* [ map, k, v, set_k ] */\
        lua_pushvalue(l, 1);   /* [ map, k, get_k, map ] */\
        lua_call(l, 1, 1);   /* [ map, k ] */\
    } else {\
        lua_pushnil(l);\
    }\
    return 1;\
}

#define class_newindex(cls) \
int L_##cls##___newindex(lua_State *l) {  /* [ map, k, v ] */\
    luaL_checkudata(l, 1, #cls);\
    lua_pushstring(l, "set_");  /* [ map, k, v, "set_" ] */\
    lua_pushvalue(l, 2);  /* [ map, k, v, "set_", k ] */\
    lua_concat(l, 2);  /* [ map, k, v, "set_k" ] */\
    const char *name = lua_tostring(l, -1);\
    lua_pop(l, 1);   /* [ map, k, v ] */\
    luaL_getmetafield(l, 1, name);\
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {  /* [ map, k, v, set_k ] */\
        lua_pushvalue(l, 1);   /* [ map, k, v, set_k, map ] */\
        lua_pushvalue(l, 3);   /* [ map, k, v, set_k, map, v ] */\
        lua_call(l, 3, 0);   /* [ map, k, v ] */\
    }\
    return 0;\
}

#define class_index_and_newindex(cls) \
    class_index(cls) \
    class_newindex(cls)

#define class_getter(cls, fieldtype, field) \
int L_##cls##_get_##field(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    lua_push##fieldtype(l, (*o)->field); \
    return 1; \
}

#define class_setter(cls, fieldtype, field) \
int L_##cls##_set_##field(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    (*o)->field = lua_to##fieldtype(l, 2); \
    return 0; \
}

#define class_getter_and_setter(cls, fieldtype, field) \
    class_getter(cls, fieldtype, field) \
    class_setter(cls, fieldtype, field)

#define class_method_reg(cls, f) ((luaL_Reg){ .name = #f, .func = L_##cls##_##f})
#define class_getter_reg(cls, field) class_method_reg(cls, get_##field)
#define class_setter_reg(cls, field) class_method_reg(cls, set_##field)

#define class_newuserdata(l, cls, o) { \
    cls **od = lua_newuserdata(l, sizeof(cls*)); \
    *od = o; \
    luaL_setmetatable(l, #cls); \
}

#endif /* CD425245_A2F7_4AB2_ADAB_E5F9A1924686 */
