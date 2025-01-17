#ifndef CD425245_A2F7_4AB2_ADAB_E5F9A1924686
#define CD425245_A2F7_4AB2_ADAB_E5F9A1924686

#define class_func_0_0(cls, p, name, f) \
int L_##cls##_##name(lua_State *l) { cls p *o = luaL_checkudata(l, 1, #cls); f(*o); return 0; }
#define class_func_1_0(cls, p, name, f, at) \
int L_##cls##_##name(lua_State *l) { cls p *o = luaL_checkudata(l, 1, #cls); f(*o, luaL_check##at(l, 2)); return 0; }
#define class_func_2_0(cls, p, name, f, at, at2) \
int L_##cls##_##name(lua_State *l) { cls p *o = luaL_checkudata(l, 1, #cls); f(*o, luaL_check##at(l, 2), luaL_check##at2(l, 3)); return 0; }

#define class_func_0_1(cls, p, name, f, rt) \
int L_##cls##_##name(lua_State *l) { cls p *o = luaL_checkudata(l, 1, #cls); lua_push##rt(f(*o)); return 1; }
#define class_func_1_1(cls, p, name, f, at, rt) \
int L_##cls##_##name(lua_State *l) { cls p *o = luaL_checkudata(l, 1, #cls); lua_push##rt(f(*o, luaL_check##at(l, 2))); return 1; }

#define class_index(cls) \
int L_##cls##___index(lua_State *l) { \
    luaL_checkudata(l, 1, #cls);  /* [ map, k ] */ \
    /* find named value */\
    lua_getmetatable(l, 1); /* [ map, k, Map ] */\
    lua_pushvalue(l, 2);  /* [ map, k, Map, k ] */\
    lua_gettable(l, -2); /* [ map, k, Map, v ] */\
    if (!lua_isnil(l, -1)) \
        return 1; \
    lua_pop(l, 2); /* [ map, k ] */\
    /* find getter */\
    lua_pushstring(l, "__get");  /* [ map, k, "__get" ] */\
    lua_pushvalue(l, 2);  /* [ map, k, "__get", k ] */\
    lua_concat(l, 2);   /* [ map, k, "__getk" ] */\
    const char *name = lua_tostring(l, -1);\
    lua_pop(l, 1);   /* [ map, k ] */\
    luaL_getmetafield(l, 1, name);\
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {  /* [ map, k, __getk ] */\
        lua_pushvalue(l, 1);   /* [ map, k, __getk, map ] */\
        if (lua_pcall(l, 1, 1, 0) != LUA_OK) lua_error(l); /* [ map, k, v ] */\
        return 1;\
    } \
    return 0; \
}

#define class_ctor_1(cls, p, f, successful, at) int L_##f(lua_State *l) { \
    cls p o = f(lua_to##at(l, 1)); \
    if (successful(o)) { \
        cls p*od = lua_newuserdata(l, sizeof(cls p)); \
        *od = o; \
        luaL_setmetatable(l, #cls); \
        return 1; \
    } \
    return 0; \
}

#define class_newindex(cls) \
int L_##cls##___newindex(lua_State *l) {  /* [ map, k, v ] */\
    luaL_checkudata(l, 1, #cls);\
    lua_pushstring(l, "__set");  /* [ map, k, v, "__set" ] */\
    lua_pushvalue(l, 2);  /* [ map, k, v, "__set", k ] */\
    lua_concat(l, 2);  /* [ map, k, v, "__setk" ] */\
    const char *name = lua_tostring(l, -1);\
    lua_pop(l, 1);   /* [ map, k, v ] */\
    luaL_getmetafield(l, 1, name);\
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {  /* [ map, k, v, __setk ] */\
        lua_pushvalue(l, 1);   /* [ map, k, v, __setk, map ] */\
        lua_pushvalue(l, 3);   /* [ map, k, v, __setk, map, v ] */\
        if (lua_pcall(l, 2, 0, 0) != LUA_OK) lua_error(l); /* [ map, k, v ] */\
    }\
    return 0;\
}

#define class_index_and_newindex(cls) \
    class_index(cls) \
    class_newindex(cls)

#define class_gc(cls, p, free) \
int L_##cls##___gc(lua_State *l) { \
    cls p*o = luaL_testudata(l, 1, #cls); \
    if (o) { free(*o); } \
    return 0; \
}

#define class_getterf(cls, p, fieldtype, field, getField) \
int L_##cls##___get##field(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (o) lua_push##fieldtype(l, getField(*o)); \
    return 1; \
}

#define class_getter(cls, p, fieldtype, field) \
int L_##cls##___get##field(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (o) lua_push##fieldtype(l, (p*o).field); \
    return 1; \
}

#define class_setterf(cls, p, fieldtype, field, setField) \
int L_##cls##___set##field(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (!lua_is##fieldtype(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), #fieldtype, #cls, #field); \
    setField(*o, lua_to##fieldtype(l, 2)); \
    return 0; \
}

#define class_setter(cls, p, fieldtype, field) \
int L_##cls##___set##field(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (!lua_is##fieldtype(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), #fieldtype, #cls, #field); \
    (p*o).field = lua_to##fieldtype(l, 2); \
    return 0; \
}

#define class_setter_clamped(cls, p, field, min, max) \
int L_##cls##___set##field(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (!lua_isnumber(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), "number", #cls, #field); \
    lua_Number n = lua_tonumber(l, 2); \
    if (n < min) n = min; else if (n > max) n = max; \
    (p*o).field = n; \
    return 0; \
}

#define class_getter_and_setter(cls, p, fieldtype, field) \
    class_getter(cls, p, fieldtype, field) \
    class_setter(cls, p, fieldtype, field)

#define class_getter_Vector2(cls, p, vector2) \
int L_##cls##_get##vector2(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    lua_pushnumber(l, (p*o).vector2.x); \
    lua_pushnumber(l, (p*o).vector2.y); \
    return 2; \
}

#define class_setter_Vector2(cls, p, vector2) \
int L_##cls##_set##vector2(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (lua_isnumber(l, 2)) (p*o).vector2.x = lua_tonumber(l, 2); \
    if (lua_isnumber(l, 3)) (p*o).vector2.y = lua_tonumber(l, 3); \
    return 0; \
}

#define class_getter_and_setter_Vector2(cls, p, vector2) \
    class_getter_Vector2(cls, p, vector2) \
    class_setter_Vector2(cls, p, vector2)

#define class_getter_Color(cls, p, color) \
int L_##cls##_get##color(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    lua_pushinteger(l, (p*o).color.r); \
    lua_pushinteger(l, (p*o).color.g); \
    lua_pushinteger(l, (p*o).color.b); \
    lua_pushinteger(l, (p*o).color.a); \
    return 4; \
}

#define class_setter_Color(cls, p, color) \
int L_##cls##_set##color(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (lua_isnumber(l, 2)) { \
        int c = lua_tointeger(l, 2); \
        (p*o).color.r = c < 0 ? 0 : c > 255 ? 255 : c; \
    }\
    if (lua_isnumber(l, 3)) { \
        int c = lua_tointeger(l, 3); \
        (p*o).color.g = c < 0 ? 0 : c > 255 ? 255 : c; \
    }\
    if (lua_isnumber(l, 4)) { \
        int c = lua_tointeger(l, 4); \
        (p*o).color.b = c < 0 ? 0 : c > 255 ? 255 : c; \
    }\
    if (lua_isnumber(l, 5)) { \
        int c = lua_tointeger(l, 5); \
        (p*o).color.a = c < 0 ? 0 : c > 255 ? 255 : c; \
    }\
    return 0; \
}

#define class_getter_and_setter_Color(cls, p, color) \
    class_getter_Color(cls, p, color) \
    class_setter_Color(cls, p, color)

#define class_method_reg(cls, f) { .name = #f, .func = L_##cls##_##f}
#define class_getter_reg(cls, field) class_method_reg(cls, __get##field)
#define class_setter_reg(cls, field) class_method_reg(cls, __set##field)
#define class_getter_and_setter_reg(cls, field) \
    class_getter_reg(cls, field),\
    class_setter_reg(cls, field)

#define class_newuserdata(l, cls, o) { \
    cls **od = lua_newuserdata(l, sizeof(cls*)); \
    *od = o; \
    luaL_setmetatable(l, #cls); \
}

#define class_getter_multi_reg(cls, field) class_method_reg(cls, get##field)
#define class_setter_multi_reg(cls, field) class_method_reg(cls, set##field)
#define class_getter_and_setter_multi_reg(cls, field) \
    class_getter_multi_reg(cls, field),\
    class_setter_multi_reg(cls, field)

#endif /* CD425245_A2F7_4AB2_ADAB_E5F9A1924686 */
