#include <engine/tasks.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <assert.h>

static lua_State *lua;

void EndLuaTask(Task *t) {
    intptr_t ref = t->data;
    luaL_unref(lua, LUA_REGISTRYINDEX, ref);
    EndTask(t);
}

int Lua_EndTask(lua_State *l) {
    assert(lua_istable(l, -1)); // lua: self
    lua_pushstring(l, "__task"); // lua: self, "__task"
    lua_gettable(l, -2); // lua: self, task
    assert(lua_islightuserdata(l, -1));
    Task *t = lua_touserdata(l, -1);
    lua_pop(l, 2);
    assert(t);
    EndLuaTask(t);
    return 0;
}

void Task_LuaFunction(Task *t) {
    intptr_t ref = t->data;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
    assert(lua_istable(lua, -1)); // lua: self

    lua_pushstring(lua, "__call"); // lua: self, "__call"
    lua_gettable(lua, -2);
    assert(lua_isfunction(lua, -1)); // lua: self, function

    lua_pushvalue(lua, -2); // lua: self, function, self
    int result = lua_pcall(lua, 1, 0, 0); // lua: self
    if (result != LUA_OK) { // lua: self, error
        printf(luaL_tolstring(lua, -1, NULL));
        printf("\n");
        lua_pop(lua, 1); // lua: self
        EndLuaTask(t);
    }
    lua_pop(lua, 1); // lua:
}

void Task_LuaClass(Task *t) {
    intptr_t ref = t->data;
    lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
    assert(lua_istable(lua, -1)); // lua: self

    lua_pushstring(lua, "update"); // lua: self, "update"
    lua_gettable(lua, -2);
    if (lua_isfunction(lua, -1)) { // lua: self, update
        lua_pushvalue(lua, -2); // lua: self, update, self
        int result = lua_pcall(lua, 1, 0, 0); // lua: self
        if (result != LUA_OK) { // lua: self, error
            printf(luaL_tolstring(lua, -1, NULL));
            printf("\n");
            lua_pop(lua, 1); // lua: self
            EndLuaTask(t);
        }
    }
    lua_pop(lua, 1); // lua:
}

Task* NewLuaTask(const char *luaModule, int priority) {
    int result;

    lua_getglobal(lua, "require"); // lua: require
    lua_pushstring(lua, luaModule); // lua: require, module
    result = lua_pcall(lua, 1, 1, 0);
    if (result != LUA_OK) { // lua: error
        printf(luaL_tolstring(lua, -1, NULL));
        printf("\n");
        lua_pop(lua, 1);
        return NULL;
    }

    if (lua_isfunction(lua, -1)) { // lua: function
        lua_newtable(lua); // lua: function, self

        lua_pushstring(lua, "__call");// lua: function, self, "__call"
        lua_pushvalue(lua, -3); // lua: function, self, "__call", function
        lua_settable(lua, -3);  // lua: function, self

        intptr_t ref = luaL_ref(lua, LUA_REGISTRYINDEX); // lua: function
        lua_pop(lua, 1); // lua:

        Task *task = NewTask(Task_LuaFunction, (void*)ref, priority);
        lua_rawgeti(lua, LUA_REGISTRYINDEX, ref); // lua: self
        lua_pushstring(lua, "__task");// lua: self, "__task"
        lua_pushlightuserdata(lua, task); // lua: self, "__task", task
        lua_settable(lua, -3);  // lua: self
        lua_pop(lua, 1); // lua:
        return task;
    }

    if (lua_istable(lua, -1)) { // lua: class
        lua_pushstring(lua, "__index"); // lua: class, "__index"
        lua_pushvalue(lua, -2); // lua: class, "__index", class
        lua_settable(lua, -3); // lua: class

        lua_newtable(lua); // lua: class, self
        lua_pushvalue(lua, -2); // lua: class, self, class
        lua_setmetatable(lua, -2); // lua: class, self

        intptr_t ref = luaL_ref(lua, LUA_REGISTRYINDEX); // lua: class

        Task *task = NewTask(Task_LuaClass, (void*)ref, priority);
        
        lua_pushstring(lua, "start");// lua: class, "start"
        lua_gettable(lua, -2);  // lua: class, start
        if (lua_isfunction(lua, -1)) {
            lua_rawgeti(lua, LUA_REGISTRYINDEX, ref); // lua: class, start, self
            result = lua_pcall(lua, 1, 0, 0); // lua: class
            if (result != LUA_OK) { // lua: class, error
                printf(luaL_tolstring(lua, -1, NULL));
                printf("\n");
                lua_pop(lua, 1); // lua: class
            }
        } else {
            lua_pop(lua, 1); // lua: class
        }
        lua_pop(lua, 1); // lua:
        return task;
    }

    printf("Can't start a task from a %s\n", lua_typename(lua, lua_type(lua, -1)));
    return NULL;
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