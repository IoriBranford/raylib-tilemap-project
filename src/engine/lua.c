#include <engine/tasks.h>
#include <engine/lua.h>
#include <util/lua_class.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

int L_Task_run(lua_State *l);

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

int RunLua(const char *luaFile, int priority, const char *argf, ...) {
    lua_pushcfunction(lua, L_Task_run);
    lua_pushstring(lua, luaFile);
    lua_pushinteger(lua, priority);

    int argc = 2;
    if (argf) {
        va_list args;
        va_start(args, argf);
        while (*argf) {
            switch (*argf) {
            case 'i':
            case 'd': lua_pushinteger(lua, va_arg(args, lua_Integer));   ++argc; break;
            case 'f': lua_pushnumber(lua, va_arg(args, lua_Number));     ++argc; break;
            case 's': lua_pushstring(lua, va_arg(args, const char*));    ++argc; break;
            case 'b': lua_pushboolean(lua, va_arg(args, int));           ++argc; break;
            case 'l': lua_pushlightuserdata(lua, va_arg(args, void*));   ++argc; break;
            }
            ++argf;
        }
        va_end(args);
    }

    int result = lua_pcall(lua, argc, 1, 0);
    int taskRef = luaL_testudata(lua, -1, "Task") ?
        luaL_ref(lua, LUA_REGISTRYINDEX) : LUA_REFNIL;
    lua_pop(lua, lua_gettop(lua));
    return taskRef;
}

Task* GetLuaTask(int taskRef) {
    if (taskRef == LUA_REFNIL) return NULL;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, taskRef);
    Task **ud = luaL_testudata(lua, 1, "Task");
    lua_pop(lua, 1);
    return ud ? *ud : NULL;
}

lua_State* GetLuaThread(int taskRef) {
    Task *task = GetLuaTask(taskRef);
    if (!task) return NULL;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, task->idata);
    lua_State *thread = lua_isthread(lua, -1) ? lua_tothread(lua, -1) : NULL;
    lua_pop(lua, 1);
    return thread;
}

int LuaResultBool(int taskRef, int i) {
    lua_State *thread = GetLuaThread(taskRef);
    return lua_toboolean(thread, i);
}

lua_Integer LuaResultInt(int taskRef, int i) {
    lua_State *thread = GetLuaThread(taskRef);
    return lua_tointeger(thread, i);
}

lua_Number LuaResultNumber(int taskRef, int i) {
    lua_State *thread = GetLuaThread(taskRef);
    return lua_tonumber(thread, i);
}

const char* LuaResultString(int taskRef, int i) {
    lua_State *thread = GetLuaThread(taskRef);
    return lua_tostring(thread, i);
}

void* LuaResultUserdata(int taskRef, int i, const char *udType) {
    lua_State *thread = GetLuaThread(taskRef);
    if (udType)
        return luaL_testudata(thread, i, udType);
    return lua_touserdata(thread, i);
}

int LuaResultFieldBool(int taskRef, int ti, const char *k) {
    lua_State *thread = GetLuaThread(taskRef);
    lua_getfield(thread, ti, k);
    int v = lua_toboolean(thread, -1);
    lua_pop(thread, 1);
    return v;
}

lua_Integer LuaResultFieldInt(int taskRef, int ti, const char *k) {
    lua_State *thread = GetLuaThread(taskRef);
    lua_getfield(thread, ti, k);
    lua_Integer v = lua_tointeger(thread, -1);
    lua_pop(thread, 1);
    return v;
}

lua_Number LuaResultFieldNumber(int taskRef, int ti, const char *k) {
    lua_State *thread = GetLuaThread(taskRef);
    lua_getfield(thread, ti, k);
    lua_Number v = lua_tonumber(thread, -1);
    lua_pop(thread, 1);
    return v;
}

const char* LuaResultFieldString(int taskRef, int ti, const char *k) {
    lua_State *thread = GetLuaThread(taskRef);
    lua_getfield(thread, ti, k);
    const char *v = lua_tostring(thread, -1);
    lua_pop(thread, 1);
    return v;
}

void* LuaResultFieldUserdata(int taskRef, int ti, const char *k, const char *udType) {
    lua_State *thread = GetLuaThread(taskRef);
    lua_getfield(thread, ti, k);
    void *v = udType ? luaL_testudata(thread, -1, udType) : lua_touserdata(thread, -1);
    lua_pop(thread, 1);
    return v;
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