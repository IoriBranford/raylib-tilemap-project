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
    int nArgs = lua_gettop(thread);
    int nResults = 0;
    int result = lua_resume(thread, NULL, nArgs, &nResults);
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

int GetLua(lua_State *l, const char *luaFile) {
    if (lua_getglobal(l, luaFile) != LUA_TFUNCTION) {
        lua_pop(l, 1);
        int error = luaL_loadfile(l, luaFile);
        if (error) {
            fprintf(stderr, "LUA: %s\n", lua_tostring(l, -1));
            lua_pop(l, 1);
            return error;
        }
        lua_pushvalue(l, -1);
        lua_setglobal(l, luaFile);
    }
    return LUA_OK;
}

Task* NewLuaTask(const char *luaFile, int priority) {
    lua_State *thread = lua_newthread(lua);
    int error = GetLua(thread, luaFile);
    if (error) {
        lua_pop(lua, lua_gettop(lua));
        return NULL;
    }

    int ref = luaL_ref(lua, LUA_REGISTRYINDEX);
    lua_xmove(lua, thread, lua_gettop(lua));
    return NewTask(Task_ResumeLuaThread, ref, priority);
}

int RunLua(const char *luaFile) {
    lua_State *thread = lua_newthread(lua);
    int error = GetLua(thread, luaFile);
    if (error) {
        lua_pop(lua, lua_gettop(lua));
        return error;
    }

    int ref = luaL_ref(lua, LUA_REGISTRYINDEX);
    int nArgs = lua_gettop(lua);
    lua_xmove(lua, thread, nArgs);
    int nResults = 0;
    int result = lua_resume(thread, NULL, nArgs, &nResults);
    if (result == LUA_OK) {
        luaL_unref(lua, LUA_REGISTRYINDEX, ref);
    } else if (result == LUA_YIELD) {
        int priority = luaL_optinteger(thread, 1, 0);
        NewTask(Task_ResumeLuaThread, ref, priority);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        luaL_unref(lua, LUA_REGISTRYINDEX, ref);
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