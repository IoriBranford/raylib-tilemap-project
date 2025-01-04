#include <engine/tasks.h>
#include <raylib.h>
#include <lua.h>
#include <luacode.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static lua_State *lua;

extern "C" void Task_ResumeLuaThread(Task *t) {
    int ref = (int)t->data;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
    lua_State *thread = lua_tothread(lua, -1);
    int nArgs = lua_gettop(thread);
    int result = lua_resume(thread, NULL, nArgs);
    if (result == LUA_OK) {
        lua_unref(lua, ref);
        EndTask(t);
    } else if (result == LUA_YIELD) {
        if (lua_isnumber(thread, 1))
            t->priority = lua_tonumber(thread, 1);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        lua_unref(lua, ref);
        EndTask(t);
    }
    lua_pop(thread, lua_gettop(thread));
    lua_pop(lua, lua_gettop(lua));
}

int GetLua(lua_State *l, const char *luaFile) {
    if (lua_getglobal(l, luaFile) != LUA_TFUNCTION) {
        lua_pop(l, 1);
        if (!FileExists(luaFile)) {
            printf("LUA: file not found %s", luaFile);
            return LUA_ERRERR;
        }

        int sourceSize = GetFileLength(luaFile);
        char *source = LoadFileText(luaFile);
        size_t bytecodeSize = 0;
        char* bytecode = luau_compile(source, sourceSize, NULL, &bytecodeSize);
        int error = luau_load(l, luaFile, bytecode, bytecodeSize, 0);
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
    lua_State *thread = lua_newthread(lua); // lua[ *args, thread ]
    int error = GetLua(thread, luaFile); // thread[ code ]
    if (error) {
        lua_pop(lua, lua_gettop(lua));
        return NULL;
    }

    int ref = lua_ref(lua, -1);
    lua_pop(lua, 1); // lua[ *args ]
    lua_xmove(lua, thread, lua_gettop(lua));  // lua[], thread[ *args ]
    return NewTask(Task_ResumeLuaThread, (void*)ref, priority);
}

extern "C" int RunLua(const char *luaFile) {
    lua_State *thread = lua_newthread(lua); // lua[ *args, thread ]
    int error = GetLua(thread, luaFile); // thread[ code ]
    if (error) {
        lua_pop(lua, lua_gettop(lua));
        return error;
    }

    int ref = lua_ref(lua, -1);
    lua_pop(lua, 1); // lua[ *args ]
    int nArgs = lua_gettop(lua);
    lua_xmove(lua, thread, lua_gettop(lua));  // lua[], thread[ *args ]
    int result = lua_resume(thread, NULL, nArgs);
    if (result == LUA_OK) {
        lua_unref(lua, ref);
    } else if (result == LUA_YIELD) { // thread[ priority? ]
        int priority = luaL_optinteger(thread, 1, 0);
        NewTask(Task_ResumeLuaThread, (void*)ref, priority);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        lua_unref(lua, ref);
    }
    lua_pop(thread, lua_gettop(thread));
    lua_pop(lua, lua_gettop(lua));
    return result;
}

extern "C" void CloseLua() {
    if (lua)
        lua_close(lua);
    lua = NULL;
}

extern "C" void InitLua() {
    if (lua)
        CloseLua();
    lua = luaL_newstate();
    luaL_openlibs(lua);
}