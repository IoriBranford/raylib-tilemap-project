#include <stdarg.h>
#include <string.h>
#include <engine/lua.h>

void L_doc(lua_State *l) {
    lua_getglobal(l, "doc");
}

void L_doc_funcs(lua_State *l) {
    lua_getfield(l, -1, "functions");
    if (lua_isnil(l, -1)) {
        lua_pop(l, 1);
        lua_newtable(l);
        lua_pushvalue(l, -1);
        lua_setfield(l, -3, "functions");
    }
}

void L_doc_funcs_entry(lua_State *l, const char *name) {
    lua_getfield(l, -1, name);
    if (lua_isnil(l, -1)) {
        lua_pop(l, 1);
        lua_newtable(l);
        lua_pushboolean(l, 1);
        lua_setfield(l, -3, name);
        lua_pushvalue(l, -1);
        lua_rawseti(l, -3, lua_objlen(l, -3) + 1);

        lua_pushstring(l, "");
        lua_setfield(l, -2, "description");
        lua_newtable(l);
        lua_setfield(l, -2, "variants");
    }
}

void L_doc_types(lua_State *l) {
    lua_getfield(l, -1, "types");
    if (lua_isnil(l, -1)) {
        lua_pop(l, 1);
        lua_newtable(l);
        lua_pushvalue(l, -1);
        lua_setfield(l, -3, "types");
    }
}

void L_doc_types_entry(lua_State *l, const char *name) {
    lua_getfield(l, -1, name);
    if (lua_isnil(l, -1)) {
        lua_pop(l, 1);
        lua_newtable(l);
        lua_pushboolean(l, 1);
        lua_setfield(l, -3, name);
        lua_pushvalue(l, -1);
        lua_rawseti(l, -3, lua_objlen(l, -3) + 1);

        lua_pushstring(l, "");
        lua_setfield(l, -2, "description");
        lua_newtable(l);
        lua_setfield(l, -2, "constructors");
        lua_newtable(l);
        lua_setfield(l, -2, "functions");
        lua_newtable(l);
        lua_setfield(l, -2, "supertypes");
    }
}

void L_docfuncs_reg(lua_State *l, luaL_Reg *reg) {
    L_doc(l);
    L_doc_funcs(l);
    for (; reg->name; ++reg) {
        L_doc_func(l, reg->name);
        lua_pop(l, 1);
    }
    lua_pop(l, 2);
}

void L_docclassfuncs_reg(lua_State *l, const char *cls, luaL_Reg *reg) {
    L_doc(l);
    L_doc_types(l);
    L_doc_types_entry(l, cls);
    L_doc_funcs(l);
    for (; reg->name; ++reg) {
        if (strncmp(reg->name, "__", 2)) {
            L_doc_funcs_entry(l, reg->name);
            lua_pop(l, 1);
        }
    }
    lua_pop(l, 4);
}

int L_doc_load(lua_State *l) {
    lua_getglobal(l, "require");
    lua_pushstring(l, "api");
    if (lua_pcall(l, 1, 1, 0) != LUA_OK || !lua_istable(l, -1)) {
        lua_newtable(l);
    }
    lua_pushvalue(l, -1);
    lua_setglobal(l, "doc");
    return 1;
}

int L_doc_save(lua_State *l) {
    lua_getglobal(l, "require");
    lua_pushstring(l, "pl.file");
    lua_pcall(l, 1, 1, 0);

    lua_getglobal(l, "require");
    lua_pushstring(l, "pl.pretty");
    lua_pcall(l, 1, 1, 0);

    lua_pushstring(l, "return ");
    lua_getfield(l, -2, "write");
    L_doc(l);
    lua_pcall(l, 1, 1, 0);
    lua_concat(l, 2);

    lua_getfield(l, -3, "write");
    lua_pushstring(l, "lua/api.lua");
    lua_pushvalue(l, -3);
    lua_pcall(l, 2, 1, 0);

    return 1;
}