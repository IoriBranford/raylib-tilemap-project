#include <stdarg.h>
#include <string.h>
#include <engine/lua.h>

void L_doc(lua_State *l) {
    lua_getglobal(l, "api");
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
    if (lua_isnumber(l, -1)) {
        lua_rawget(l, -2);
    } else {
        lua_pop(l, 1);
        int i = lua_objlen(l, -1) + 1;

        lua_newtable(l);
        lua_pushinteger(l, i);
        lua_setfield(l, -3, name);
        lua_pushvalue(l, -1);
        lua_rawseti(l, -3, i);

        lua_pushstring(l, name);
        lua_setfield(l, -2, "name");
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
    if (lua_isnumber(l, -1)) {
        lua_rawget(l, -2);
    } else {
        lua_pop(l, 1);
        int i = lua_objlen(l, -1) + 1;

        lua_newtable(l);
        lua_pushinteger(l, i);
        lua_setfield(l, -3, name);
        lua_pushvalue(l, -1);
        lua_rawseti(l, -3, i);

        lua_pushstring(l, name);
        lua_setfield(l, -2, "name");
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
    if (lua_isnil(l, -1)) return;
    L_doc_funcs(l);
    for (; reg->name; ++reg) {
        L_doc_funcs_entry(l, reg->name);
        lua_pop(l, 1);
    }
    lua_pop(l, 2);
}

void L_docclassfuncs_reg(lua_State *l, const char *cls, luaL_Reg *reg) {
    L_doc(l);
    if (lua_isnil(l, -1)) return;
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
    lua_setglobal(l, "api");
    return 1;
}

void L_doc_funcs_write(lua_State *l, FILE *file, const char *cls) {
    int nFuncs = lua_objlen(l, -1);
    for (int i = 1; i <= nFuncs; ++i) {
        lua_rawgeti(l, -1, i);

        lua_getfield(l, -1, "description");
        const char *s = lua_tostring(l, -1);
        fprintf(file, "--- %s\n", s);
        lua_pop(l, 1);

        lua_getfield(l, -1, "name");
        s = lua_tostring(l, -1);
        fprintf(file, "function %s%s%s(",
            cls ? cls : "",
            cls ? ":" : "",
            s);
        lua_pop(l, 1);

        // TODO args

        fprintf(file, ") end\n\n");
        lua_pop(l, 1);
    }
}

void L_doc_types_write(lua_State *l, FILE *file) {
    int nTypes = lua_objlen(l, -1);
    for (int i = 1; i <= nTypes; ++i) {
        lua_rawgeti(l, -1, i);
        luaL_checktype(l, -1, LUA_TTABLE);

        lua_getfield(l, -1, "description");
        fprintf(file, "--- %s\n", lua_tostring(l, -1));
        lua_pop(l, 1);

        lua_getfield(l, -1, "name");
        const char *name = lua_tostring(l, -1);
        fprintf(file, "---@class %s\n", name);
        fprintf(file, "local %s = {}\n\n", name);
        lua_pop(l, 1);

        lua_getfield(l, -1, "functions");
        L_doc_funcs_write(l, file, name);
        lua_pop(l, 1);

        lua_pop(l, 1);
    }
}

int L_doc_save(lua_State *l) {
    lua_getglobal(l, "require");
    lua_pushstring(l, "pl.pretty");
    if (lua_pcall(l, 1, 1, 0) != LUA_OK) lua_error(l);

    lua_pushstring(l, "return ");
    lua_getfield(l, -2, "write");
    L_doc(l);
    if (lua_pcall(l, 1, 1, 0) != LUA_OK) lua_error(l);
    lua_concat(l, 2);
    
    FILE *file = fopen("lua/api.lua", "w");
    fprintf(file, "%s", lua_tostring(l, -1));
    fclose(file);
    lua_pop(l, 1);

    file = fopen("lua/doc.lua", "w");
    fprintf(file, "---@meta\n\n");
    L_doc(l);
    L_doc_funcs(l);
    L_doc_funcs_write(l, file, NULL);
    lua_pop(l, 1);
    L_doc_types(l);
    L_doc_types_write(l, file);
    lua_pop(l, 1);
    fclose(file);

    return 0;
}