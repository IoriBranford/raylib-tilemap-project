#ifndef CD425245_A2F7_4AB2_ADAB_E5F9A1924686
#define CD425245_A2F7_4AB2_ADAB_E5F9A1924686

#include "lua_doc.h"

#define lclass_func_0_0(cls, p, name, f) \
int L_##cls##_##name(lua_State *l) { cls p *o = (cls p*)luaL_checkudata(l, 1, #cls); f(*o); return 0; }
#define lclass_func_1_0(cls, p, name, f, at) \
int L_##cls##_##name(lua_State *l) { cls p *o = (cls p*)luaL_checkudata(l, 1, #cls); f(*o, luaL_check##at(l, 2)); return 0; }
#define lclass_func_2_0(cls, p, name, f, at, at2) \
int L_##cls##_##name(lua_State *l) { cls p *o = (cls p*)luaL_checkudata(l, 1, #cls); f(*o, luaL_check##at(l, 2), luaL_check##at2(l, 3)); return 0; }

#define lclass_func_0_1(cls, p, name, f, rt) \
int L_##cls##_##name(lua_State *l) { cls p *o = (cls p*)luaL_checkudata(l, 1, #cls); lua_push##rt(l, f(*o)); return 1; }
#define lclass_func_1_1(cls, p, name, f, at, rt) \
int L_##cls##_##name(lua_State *l) { cls p *o = (cls p*)luaL_checkudata(l, 1, #cls); lua_push##rt(l, f(*o, luaL_check##at(l, 2))); return 1; }

#define lclass_func_0_2ud(cls, p, name, f, rcls, rp, rcls2, rp2) \
int L_##cls##_##name(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    rcls rp*r1 = (rcls rp*) lua_newuserdata(l, sizeof(rcls rp)); \
    luaL_setmetatable(l, #rcls); \
    rcls2 rp2*r2 = (rcls2 rp2*) lua_newuserdata(l, sizeof(rcls2 rp2)); \
    luaL_setmetatable(l, #rcls2); \
    f(*o, r1, r2); \
    return 2; \
}

#define lclass_func_1_ud(cls, p, name, f, at, rcls, rp, isValid) \
int L_##cls##_##name(lua_State *l) { \
    cls p*o = luaL_checkudata(l, 1, #cls); \
    rcls rp ro = f(*o, luaL_check##at(l, 2)); \
    if (isValid(ro)) { \
        rcls rp*rod = lua_newuserdata(l, sizeof(rcls rp)); \
        *rod = ro; \
        luaL_setmetatable(l, #rcls); \
        return 1; \
    } \
    return 0; \
}

#define lclass_func_ud_0(cls, p, name, f, acls, ap)\
int L_##cls##_##name(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    acls ap*a = (acls ap*)(luaL_checkudata(l, 2, #acls)); \
    f(*o, *a); \
    return 0; \
}

#define lclass_func_ud_1(cls, p, name, f, acls, ap, rt)\
int L_##cls##_##name(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    acls ap*a = (acls ap*)(luaL_checkudata(l, 2, #acls)); \
    lua_push##rt(l, f(*o, *a)); \
    return 1; \
}

#define lclass_func_ud_ud(cls, p, name, f, acls, ap, rcls, rp, rvalid) \
int L_##cls##_##name(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    acls ap*a = (acls ap*)luaL_checkudata(l, 2, #acls); \
    rcls rp rv = f(*o, *a); \
    if (!rvalid(rv)) return 0; \
    rcls rp*r = (rcls rp*)lua_newuserdata(l, sizeof(rcls rp)); \
    *r = rv; \
    luaL_setmetatable(l, #rcls); \
    return 1; \
}

#define lclass_index(cls) \
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
    lua_pushstring(l, "get");  /* [ map, k, "get" ] */\
    lua_pushvalue(l, 2);  /* [ map, k, "get", k ] */\
    lua_concat(l, 2);   /* [ map, k, "getk" ] */\
    const char *name = lua_tostring(l, -1);\
    lua_pop(l, 1);   /* [ map, k ] */\
    luaL_getmetafield(l, 1, name);\
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {  /* [ map, k, getk ] */\
        lua_pushvalue(l, 1);   /* [ map, k, getk, map ] */\
        if (lua_pcall(l, 1, 1, 0) != LUA_OK) lua_error(l); /* [ map, k, v ] */\
        return 1;\
    } \
    return 0; \
}

#define lclass_ctor_0(cls, p, f, successful) int L_##f(lua_State *l) { \
    cls p o = f(); \
    if (successful(o)) { \
        cls p*od = (cls p*)lua_newuserdata(l, sizeof(cls p)); \
        *od = o; \
        luaL_setmetatable(l, #cls); \
        return 1; \
    } \
    return 0; \
}

#define lclass_ctor_1(cls, p, f, successful, at) int L_##f(lua_State *l) { \
    cls p o = f(lua_to##at(l, 1)); \
    if (successful(o)) { \
        cls p*od = (cls p*)lua_newuserdata(l, sizeof(cls p)); \
        *od = o; \
        luaL_setmetatable(l, #cls); \
        return 1; \
    } \
    return 0; \
}

#define lclass_ctor_2(cls, p, f, successful, at, at2) int L_##f(lua_State *l) { \
    cls p o = f(lua_to##at(l, 1), lua_to##at2(l, 2)); \
    if (successful(o)) { \
        cls p*od = (cls p*)lua_newuserdata(l, sizeof(cls p)); \
        *od = o; \
        luaL_setmetatable(l, #cls); \
        return 1; \
    } \
    return 0; \
}

#define lclass_newindex(cls) \
int L_##cls##___newindex(lua_State *l) {  /* [ map, k, v ] */\
    luaL_checkudata(l, 1, #cls);\
    lua_pushstring(l, "set");  /* [ map, k, v, "set" ] */\
    lua_pushvalue(l, 2);  /* [ map, k, v, "set", k ] */\
    lua_concat(l, 2);  /* [ map, k, v, "setk" ] */\
    const char *name = lua_tostring(l, -1);\
    lua_pop(l, 1);   /* [ map, k, v ] */\
    luaL_getmetafield(l, 1, name);\
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) {  /* [ map, k, v, setk ] */\
        lua_pushvalue(l, 1);   /* [ map, k, v, setk, map ] */\
        lua_pushvalue(l, 3);   /* [ map, k, v, setk, map, v ] */\
        if (lua_pcall(l, 2, 0, 0) != LUA_OK) lua_error(l); /* [ map, k, v ] */\
    }\
    return 0;\
}

#define lclass_index_and_newindex(cls) \
    lclass_index(cls) \
    lclass_newindex(cls)

#define lclass_gc(cls, p, free) \
int L_##cls##___gc(lua_State *l) { \
    cls p*o = (cls p*)luaL_testudata(l, 1, #cls); \
    if (o) { free(*o); } \
    return 0; \
}

#define lclass_getterf(cls, p, fieldtype, field, getField) \
int L_##cls##_get##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (o) lua_push##fieldtype(l, getField(*o)); \
    return 1; \
}

#define lclass_getter_ud(cls, p, rcls, rp, field) \
int L_##cls##_get##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    rcls rp*rod = lua_newuserdata(l, sizeof(rcls rp)); \
    *rod = (p*o).field; \
    luaL_setmetatable(l, #rcls); \
    return 1; \
}

#define lclass_getterf_ud(cls, p, rcls, rp, field, f) \
int L_##cls##_get##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    rcls rp*rod = lua_newuserdata(l, sizeof(rcls rp)); \
    *rod = f(*o); \
    luaL_setmetatable(l, #rcls); \
    return 1; \
}

#define lclass_getter(cls, p, fieldtype, field) \
int L_##cls##_get##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (o) lua_push##fieldtype(l, (p*o).field); \
    return 1; \
}

#define lclass_setterf(cls, p, fieldtype, field, setField) \
int L_##cls##_set##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (!lua_is##fieldtype(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), #fieldtype, #cls, #field); \
    setField(*o, lua_to##fieldtype(l, 2)); \
    return 0; \
}

#define lclass_setterf_ud(cls, p, acls, ap, field, f) \
int L_##cls##_set##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    acls ap*a = (acls ap*)luaL_checkudata(l, 2, #acls); \
    f(*o, *a); \
    return 0; \
}

#define lclass_setter(cls, p, fieldtype, field) \
int L_##cls##_set##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (!lua_is##fieldtype(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), #fieldtype, #cls, #field); \
    (p*o).field = lua_to##fieldtype(l, 2); \
    return 0; \
}

#define lclass_setter_clamped(cls, p, field, min, max) \
int L_##cls##_set##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (!lua_isnumber(l, 2)) \
        fprintf(stderr, "WARN: converted %s to %s when setting %s.%s\n", \
            luaL_typename(l, 2), "number", #cls, #field); \
    lua_Number n = lua_tonumber(l, 2); \
    if (n < min) n = min; else if (n > max) n = max; \
    (p*o).field = n; \
    return 0; \
}

#define lclass_getter_and_setter(cls, p, fieldtype, field) \
    lclass_getter(cls, p, fieldtype, field) \
    lclass_setter(cls, p, fieldtype, field)

#define lclass_getterf_and_setterf(cls, p, fieldtype, field, getf, setf) \
    lclass_getterf(cls, p, fieldtype, field, getf) \
    lclass_setterf(cls, p, fieldtype, field, setf)

#define lclass_getterf_and_setterf_ud(cls, p, cls2, p2, field, getf, setf) \
    lclass_getterf_ud(cls, p, cls2, p2, field, getf) \
    lclass_setterf_ud(cls, p, cls2, p2, field, setf)

#define lclass_getter_Vector2(cls, p, vector2) \
int L_##cls##_get##vector2(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    lua_pushnumber(l, (p*o).vector2.x); \
    lua_pushnumber(l, (p*o).vector2.y); \
    return 2; \
}

#define lclass_func_1_vec2(cls, p, fname, f, at, v2type) \
int L_##cls##_##fname(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    v2type v = f(*o, luaL_check##at(l, 2)); \
    lua_pushnumber(l, v.x); \
    lua_pushnumber(l, v.y); \
    return 2; \
}

#define lclass_getterf_vec2(cls, p, v2type, field, f) \
int L_##cls##_get##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    v2type v = f(*o); \
    lua_pushnumber(l, v.x); \
    lua_pushnumber(l, v.y); \
    return 2; \
}

#define lclass_setter_Vector2(cls, p, vector2) \
int L_##cls##_set##vector2(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    if (lua_isnumber(l, 2)) (p*o).vector2.x = lua_tonumber(l, 2); \
    if (lua_isnumber(l, 3)) (p*o).vector2.y = lua_tonumber(l, 3); \
    return 0; \
}

#define lclass_setterf_vec2(cls, p, v2type, field, f) \
int L_##cls##_set##field(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    int isnum[2] = {lua_isnumber(l, 2), lua_isnumber(l, 3)}; \
    if (!isnum[0] && !isnum[1]) \
        return 0; \
    if (isnum[0] && isnum[1]) { \
        f(*o, (v2type){lua_tonumber(l, 2), lua_tonumber(l, 3)}); \
        return 0; \
    } \
    lua_pushcfunction(l, L_##cls##_get##field); \
    lua_pushvalue(l, 1); \
    lua_pcall(l, 1, 2, 0); \
    if (isnum[0]) \
        f(*o, (v2type){lua_tonumber(l, 2), lua_tonumber(l, -1)}); \
    else \
        f(*o, (v2type){lua_tonumber(l, -2), lua_tonumber(l, 3)}); \
    return 0; \
}

#define lclass_getter_and_setter_Vector2(cls, p, vector2) \
    lclass_getter_Vector2(cls, p, vector2) \
    lclass_setter_Vector2(cls, p, vector2)

#define lclass_getterf_and_setterf_vec2(cls, p, v2type, field, getf, setf) \
    lclass_getterf_vec2(cls, p, v2type, field, getf) \
    lclass_setterf_vec2(cls, p, v2type, field, setf)

#define lclass_getter_Color(cls, p, color) \
int L_##cls##_get##color(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    lua_pushinteger(l, (uint32_t)ColorToInt((p*o).color)); \
    return 1; \
}

#define lclass_setter_Color(cls, p, color) \
int L_##cls##_set##color(lua_State *l) { \
    cls p*o = (cls p*)luaL_checkudata(l, 1, #cls); \
    if (!o) return 0; \
    (p*o).color = L_toColor(l, 2); \
    return 0; \
}

#define lclass_getter_and_setter_Color(cls, p, color) \
    lclass_getter_Color(cls, p, color) \
    lclass_setter_Color(cls, p, color)

#define lclass_method_reg(cls, f) { .name = #f, .func = L_##cls##_##f}
#define lclass_getter_reg(cls, field) lclass_method_reg(cls, get##field)
#define lclass_setter_reg(cls, field) lclass_method_reg(cls, set##field)
#define lclass_getter_and_setter_reg(cls, field) \
    lclass_getter_reg(cls, field),\
    lclass_setter_reg(cls, field)

#define lclass_luaopen(cls, ...) \
int luaopen_##cls(lua_State *l) { \
    luaL_newmetatable(l, #cls); \
    luaL_Reg r[] = { __VA_ARGS__, {0} }; \
    luaL_register(l, NULL, r); \
    lua_setglobal(l, #cls); \
    return 0; \
}

#define lclass_newuserdata(l, cls, o) { \
    cls **od = lua_newuserdata(l, sizeof(cls*)); \
    *od = o; \
    luaL_setmetatable(l, #cls); \
}

#endif /* CD425245_A2F7_4AB2_ADAB_E5F9A1924686 */
