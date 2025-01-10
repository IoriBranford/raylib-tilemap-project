#include <engine/lua.h>
#include <engine/tasks.h>
#include <util/lua_class.h>

int GetLua(lua_State *l, const char *luaFile);
void Task_ResumeLuaThread(Task *t);
void ReleaseLuaTask(Task *task);

class_gc(Task, ReleaseLuaTask)

int L_Task_run(lua_State *l) {
    if (lua_isstring(l, 1)) {
        const char *luaFile = lua_tostring(l, 1);
        int error = GetLua(l, luaFile);
        if (error)
            return 0;
        lua_replace(l, 1);
    }
    if (!lua_isfunction(l, 1) && !lua_iscfunction(l, 1))
        return luaL_typerror(l, 1, "function or valid script path");
    
    int priority = luaL_checkinteger(l, 2);
    lua_remove(l, 2);

    int nArgs = lua_gettop(l) - 1;

    lua_State *thread = lua_newthread(l);
    int threadRef = luaL_ref(l, LUA_REGISTRYINDEX);
    lua_xmove(l, thread, lua_gettop(l));

    int result = lua_resume(thread, nArgs);
    int nResults = 1;
    if (result == LUA_OK || result == LUA_YIELD) {
        Task *task = NewTask(Task_ResumeLuaThread, threadRef, priority);
        if (result == LUA_OK)
            EndTask(task);
        class_newuserdata(l, Task, task);
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        lua_pushnil(l);
        lua_xmove(thread, l, 1);
        nResults = 2;
        luaL_unref(l, LUA_REGISTRYINDEX, threadRef);
    }
    return nResults;
}

int PushTaskResults(lua_State *l, Task *task) {
    int threadRef = task->idata;
    lua_rawgeti(l, LUA_REGISTRYINDEX, threadRef);
    lua_State *thread = lua_tothread(l, -1);
    int nResults = lua_gettop(thread);
    for (int i = 1; i <= nResults; ++i)
        lua_pushvalue(thread, i);
    lua_xmove(thread, l, nResults);
    return nResults;
}

int L_Task_results(lua_State *l) {
    Task **ud = luaL_checkudata(l, 1, "Task");
    return PushTaskResults(l, *ud);
}

int L_Task_end(lua_State *l) {
    Task **ud = luaL_checkudata(l, 1, "Task");
    EndTask(*ud);
    return PushTaskResults(l, *ud);
}

int L_Task___getdone(lua_State *l) {
    Task **ud = luaL_checkudata(l, 1, "Task");
    lua_pushboolean(l, IsTaskDone(*ud));
    return 1;
}

int L_Task_sleep(lua_State *l) {
    Task **ud = luaL_checkudata(l, 1, "Task");
    int sleep = luaL_checknumber(l, 2);
    SleepTask(*ud, sleep);
    return 0;
}

class_index_and_newindex(Task);
class_getter_and_setter(Task, integer, priority);
class_getter(Task, integer, sleeping);

int luaopen_task(lua_State *l) {
    luaL_Reg task_r[] = {
        class_method_reg(Task, run),
        {0}
    };
    luaL_register(l, "task", task_r);
    lua_pop(l, 1);

    luaL_newmetatable(l, "Task");
    luaL_Reg Task_r[] = {
        class_method_reg(Task, __index),
        class_method_reg(Task, __newindex),
        class_method_reg(Task, __gc),
        class_getter_reg(Task, priority),
        class_setter_reg(Task, priority),
        class_getter_reg(Task, done),
        class_getter_reg(Task, sleeping),
        class_method_reg(Task, results),
        class_method_reg(Task, sleep),
        class_method_reg(Task, end),
        {0}
    };
    luaL_register(l, NULL, Task_r);
    lua_pop(l, 1);

    return 0;
}