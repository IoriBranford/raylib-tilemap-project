#include <engine/lua.h>
#include <engine/tasks.h>

void Task_ResumeLuaThread(Task *t);
void ReleaseLuaTask(Task *task);

class_gc(Task, *, ReleaseLuaTask)

int L_RunTask(lua_State *l) {
    if (lua_isstring(l, 1)) {
        lua_getglobal(l, "require");
        lua_pushvalue(l, 1);
        if (lua_pcall(l, 1, 1, 0) != LUA_OK)
            lua_error(l);
        lua_replace(l, 1);
    }
    if (!lua_isfunction(l, 1) && !lua_iscfunction(l, 1))
        return luaL_typerror(l, 1, "function or valid require string");
    
    int priority = luaL_checkinteger(l, 2);
    lua_remove(l, 2);

    int nArgs = lua_gettop(l) - 1;

    lua_State *thread = lua_newthread(l);
    int threadRef = luaL_ref(l, LUA_REGISTRYINDEX);
    lua_xmove(l, thread, lua_gettop(l));

    int nResults;
    int result;
#ifdef LUA54
    result = lua_resume(thread, NULL, nArgs, &nResults);
#else
    result = lua_resume(thread, nArgs);
    nResults = lua_gettop(thread);
#endif
    if (result == LUA_OK || result == LUA_YIELD) {
        Task *task = NewTask(Task_ResumeLuaThread, NULL, priority);
        task->threadRef = threadRef;
        class_newuserdata(l, Task, task);
        if (result == LUA_OK) {
            EndTask(task);
            task->taskRef = LUA_REFNIL;
        } else {
            lua_pushvalue(l, -1);
            task->taskRef = luaL_ref(l, LUA_REGISTRYINDEX);
        }
        for (int i = 1; i <= nResults; ++i)
            lua_pushvalue(thread, i);
        lua_xmove(thread, l, nResults);
        return 1 + nResults;
    } else {
        fprintf(stderr, "LUA: %s\n", lua_tostring(thread, -1));
        lua_pushnil(l);
        lua_xmove(thread, l, 1);
        luaL_unref(l, LUA_REGISTRYINDEX, threadRef);
        return 2;
    }
}

int PushTaskResults(lua_State *l, Task *task) {
    int threadRef = task->threadRef;
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

class_getterf(Task, *, boolean, done, IsTaskDone)

class_func_1_0(Task, *, sleep, SleepTask, integer)

class_index_and_newindex(Task)
class_getter_and_setter(Task, *, number, priority)
class_getter(Task, *, number, sleeping)

class_luaopen(Task,
    class_method_reg(Task, __index),
    class_method_reg(Task, __newindex),
    class_method_reg(Task, __gc),
    class_getter_reg(Task, priority),
    class_setter_reg(Task, priority),
    class_getter_reg(Task, done),
    class_getter_reg(Task, sleeping),
    class_method_reg(Task, results),
    class_method_reg(Task, sleep),
    class_method_reg(Task, end)
)

int luaopen_task(lua_State *l) {
    lua_getglobal(l, "_G");
    luaL_Reg task_r[] = {
        l_func_reg(RunTask),
        {0}
    };
    luaL_register(l, NULL, task_r);
    lua_pop(l, 1);

    lua_cpcall(l, luaopen_Task, NULL);

    return 0;
}