#include <engine/tasks.h>
#include <raylib.h>
#include <lua.h>
#include <luacode.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static lua_State *lua;

void EndLuaTask(Task *t) {
    int ref = (int)t->data;
    lua_unref(lua, ref);
    EndTask(t);
}

int Lua_EndTask(lua_State *l) {
    assert(lua_istable(l, -1)); // lua: self
    lua_pushstring(l, "__task"); // lua: self, "__task"
    lua_gettable(l, -2); // lua: self, task
    assert(lua_islightuserdata(l, -1));
    Task *t = (Task*)lua_touserdata(l, -1);
    lua_pop(l, 2);
    assert(t);
    EndLuaTask(t);
    return 0;
}

extern "C" void Task_LuaFunction(Task *t) {
    int ref = (int)t->data;
    lua_getref(lua, ref);
    assert(lua_istable(lua, -1)); // lua: self

    lua_pushstring(lua, "__call"); // lua: self, "__call"
    lua_gettable(lua, -2);
    assert(lua_isfunction(lua, -1)); // lua: self, function

    lua_pushvalue(lua, -2); // lua: self, function, self
    int result = lua_pcall(lua, 1, 0, 0); // lua: self
    if (result != LUA_OK) { // lua: self, error
        printf(lua_tostring(lua, -1));
        printf("\n");
        lua_pop(lua, 1); // lua: self
        EndLuaTask(t);
    }
    lua_pop(lua, 1); // lua:
}

extern "C" void Task_LuaClass(Task *t) {
    int ref = (int)t->data;
    lua_getref(lua, ref);
    assert(lua_istable(lua, -1)); // lua: self

    lua_pushstring(lua, "update"); // lua: self, "update"
    lua_gettable(lua, -2);
    if (lua_isfunction(lua, -1)) { // lua: self, update
        lua_pushvalue(lua, -2); // lua: self, update, self
        int result = lua_pcall(lua, 1, 0, 0); // lua: self
        if (result != LUA_OK) { // lua: self, error
            printf(lua_tostring(lua, -1));
            printf("\n");
            lua_pop(lua, 1); // lua: self
            EndLuaTask(t);
        }
    }
    lua_pop(lua, 1); // lua:
}

Task* NewLuaClassTask(int priority) {
    lua_newtable(lua); // lua: class, self
    lua_pushvalue(lua, -2); // lua: class, self, class
    lua_setmetatable(lua, -2); // lua: class, self

    int ref = lua_ref(lua, -1);

    Task *task = NewTask(Task_LuaClass, (void*)ref, priority);
    lua_pushstring(lua, "__task");// lua: class, self, "__task"
    lua_pushlightuserdata(lua, task); // lua: class, self, "__task", task
    lua_settable(lua, -3);  // lua: class, self
    
    lua_pushstring(lua, "start");// lua: class, self, "start"
    lua_gettable(lua, -2);  // lua: class, self, start
    if (lua_isfunction(lua, -1)) {
        lua_pushvalue(lua, -2); // lua: class, self, start, self
        int result = lua_pcall(lua, 1, 0, 0); // lua: class, self
        if (result != LUA_OK) { // lua: class, self, error
            printf(lua_tostring(lua, -1));
            printf("\n");
            lua_pop(lua, 1); // lua: class, self
        }
    } else {
        lua_pop(lua, 1); // lua: class, self
    }
    lua_pop(lua, 2); // lua:
    return task;
}

Task* NewLuaFunctionTask(int priority) { // lua: function
    lua_newtable(lua); // lua: function, self

    lua_pushstring(lua, "__call");// lua: function, self, "__call"
    lua_pushvalue(lua, -3); // lua: function, self, "__call", function
    lua_settable(lua, -3);  // lua: function, self

    int ref = lua_ref(lua, -1);

    Task *task = NewTask(Task_LuaFunction, (void*)ref, priority);
    lua_pushstring(lua, "__task");// lua: function, self, "__task"
    lua_pushlightuserdata(lua, task); // lua: function, self, "__task", task
    lua_settable(lua, -3);  // lua: function, self
    lua_pop(lua, 2); // lua:
    return task;
}

int RequireLuaModule(lua_State *l) {
    luaL_checkstring(l, 1); // lua: modulePath
    lua_getglobal(l, "require"); // lua: modulePath, require
    lua_pushvalue(l, -2); // lua: modulePath, require, modulePath
    lua_call(l, 1, 1); // lua: modulePath, ?

    if (lua_istable(l, -1)) { // lua: modulePath, class
        lua_pushstring(l, "__index"); // lua: modulePath, class, "__index"
        lua_pushvalue(l, -2); // lua: modulePath, class, "__index", class
        lua_settable(l, -3); // lua: modulePath, class

        lua_pushstring(l, "update"); // lua: modulePath, class, "update"
        lua_gettable(l, -2); // lua: modulePath, class, update
        if (!lua_isfunction(l, -1)) {
            printf("Warning: no update function in %s\n", lua_tostring(l, 1));
        }
        lua_pop(l, 1); // lua: modulePath, class
    }

    return 1;
}

Task* NewLuaTask(const char *luaFile, int priority) {
    lua_getglobal(lua, luaFile);
    if (lua_isfunction(lua, -1)) {
        lua_call(lua, 0, 1);
    } else {
        lua_pop(lua, 1);
        if (!FileExists(luaFile)) {
            printf("LUA: file not found %s", luaFile);
            return NULL;
        }

        int sourceSize = GetFileLength(luaFile);
        char *source = LoadFileText(luaFile);
        size_t bytecodeSize = 0;
        char* bytecode = luau_compile(source, sourceSize, NULL, &bytecodeSize);
        int errored = luau_load(lua, luaFile, bytecode, bytecodeSize, 0);
        if (errored) {
            printf("LUA: load error %s", lua_tostring(lua, -1));
        } else {
            lua_setglobal(lua, luaFile);
            lua_call(lua, 0, 1);
        }
        free(bytecode);
        UnloadFileText(source);
    }

    if (lua_isfunction(lua, -1)) { // lua: function
        return NewLuaFunctionTask(priority);
    }
    if (lua_istable(lua, -1)) { // lua: class
        return NewLuaClassTask(priority);
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