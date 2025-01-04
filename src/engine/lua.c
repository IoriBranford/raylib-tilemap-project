#include <engine/tasks.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <assert.h>

static lua_State *lua;

void Task_ResumeLuaThread(Task *t) {
    int ref = t->data;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
    lua_State *thread = lua_tothread(lua, -1);
    int nResults = 0;
    int result = lua_resume(thread, NULL, 0, &nResults);
    if (result == LUA_OK) {
        luaL_unref(lua, LUA_REGISTRYINDEX, ref);
        EndTask(t);
    } else if (result == LUA_YIELD) {
        t->priority = luaL_optinteger(thread, 1, 0);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(lua, -1));
    }
    lua_pop(thread, lua_gettop(thread));
    lua_pop(lua, lua_gettop(lua));
}

int RunLua(const char *luaFile) {
    if (lua_getglobal(lua, luaFile) != LUA_TFUNCTION) {
        lua_pop(lua, 1);
        int error = luaL_loadfile(lua, luaFile);
        if (error) {
            fprintf(stderr, "LUA: %s\n", lua_tostring(lua, -1));
            lua_pop(lua, 1);
            return error;
        }
        lua_pushvalue(lua, -1);
        lua_setglobal(lua, luaFile);
    }

    lua_State *thread = lua_newthread(lua);
    lua_pushvalue(lua, 1);
    lua_xmove(lua, thread, 1);
    int nResults = 0;
    int result = lua_resume(thread, NULL, 0, &nResults);
    if (result == LUA_OK) {
    } else if (result == LUA_YIELD) {
        int priority = luaL_optinteger(thread, 1, 0);
        int ref = luaL_ref(lua, LUA_REGISTRYINDEX);
        NewTask(Task_ResumeLuaThread, ref, priority);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
    }
    lua_pop(thread, lua_gettop(thread));
    lua_pop(lua, lua_gettop(lua));
    return result;
}

void CloseLua() {
    if (lua)
        lua_close(lua);
    lua = NULL;
}

void InitLua() {
    if (lua)
        CloseLua();
    lua = luaL_newstate();
    luaL_openlibs(lua);
}