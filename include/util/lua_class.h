#ifndef CD425245_A2F7_4AB2_ADAB_E5F9A1924686
#define CD425245_A2F7_4AB2_ADAB_E5F9A1924686

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

#define class_init_getter(l, cls, field) { \
    lua_pushstring(l, "get_" #field); \
    lua_pushcfunction(l, L_##cls##_get_##field); \
    lua_settable(l, -3); \
}

#define class_init_setter(l, cls, field) { \
    lua_pushstring(l, "set_" #field); \
    lua_pushcfunction(l, L_##cls##_set_##field); \
    lua_settable(l, -3); \
}

#define class_init_getter_and_setter(cls, field) \
    class_init_getter(l, cls, field) \
    class_init_setter(l, cls, field)

#define class_newuserdata(l, cls, o) { \
    cls **od = lua_newuserdata(l, sizeof(cls*)); \
    *od = o; \
    luaL_setmetatable(l, #cls); \
}

#endif /* CD425245_A2F7_4AB2_ADAB_E5F9A1924686 */
