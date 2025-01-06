#include <engine/tasks.h>
#include <engine/lua.h>
#include <util/lua_class.h>
#include <stdlib.h>
#include <assert.h>

static lua_State *lua;

void Task_ResumeLuaThread(Task *t) {
    int ref = t->idata;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
    lua_State *thread = lua_tothread(lua, -1);
    lua_pop(lua, 1);

    int nArgs = lua_gettop(thread);
    
    int result = lua_resume(thread, nArgs);
    if (result == LUA_OK) {
        EndTask(t);
    } else if (result == LUA_YIELD) {
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        EndTask(t);
    }
}

int GetLua(lua_State *l, const char *luaFile) {
    lua_getglobal(l, luaFile);
    if (!lua_isfunction(l, -1)) {
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

int RunLua(const char *luaFile, int priority) {
    int error = GetLua(lua, luaFile);
    if (error)
        return LUA_REFNIL;

    lua_State *thread = lua_newthread(lua);
    int threadRef = luaL_ref(lua, LUA_REGISTRYINDEX);
    lua_xmove(lua, thread, 1);

    int taskRef = LUA_REFNIL;
    int result = lua_resume(thread, 0);
    if (result == LUA_OK) {
        luaL_unref(lua, LUA_REGISTRYINDEX, threadRef);
    } else if (result == LUA_YIELD) {
        class_newuserdata(lua, Task, NewTask(Task_ResumeLuaThread, threadRef, priority));
        taskRef = luaL_ref(lua, LUA_REGISTRYINDEX);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        luaL_unref(lua, LUA_REGISTRYINDEX, threadRef);
    }
    return taskRef;
}

Task* GetLuaTask(int taskRef) {
    if (taskRef == LUA_REFNIL)
        return NULL;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, taskRef);
    Task **ud = luaL_testudata(lua, 1, "Task");
    return ud ? *ud : NULL;
}

void ReleaseLuaTask(int taskRef) {
    if (taskRef == LUA_REFNIL)
        return;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, taskRef);
    if (luaL_testudata(lua, 1, "Task"))
        luaL_unref(lua, LUA_REGISTRYINDEX, taskRef);
}

void CloseLua() {
    if (lua)
        lua_close(lua);
    lua = NULL;
}

int luaopen_task(lua_State *l);

void InitLua() {
    if (lua)
        CloseLua();
    lua = luaL_newstate();
    luaL_openlibs(lua);
    lua_cpcall(lua, luaopen_task, NULL);
}