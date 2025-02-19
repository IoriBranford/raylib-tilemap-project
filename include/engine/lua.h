#ifndef F368B866_5240_4102_BE90_898768165E85
#define F368B866_5240_4102_BE90_898768165E85

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <raylib.h>
#include <stdint.h>
#include "lfunc.h"
#include "lclass.h"

#if LUA_VERSION_RELEASE_NUM >= 504
#define LUA54
static void luaL_register(lua_State *l, const char *name, luaL_Reg *reg) {
    if (name) {
        lua_getglobal(l, "package"); // [ package ]
        lua_pushstring(l, "loaded"); // [ package, "loaded" ]
        lua_gettable(l, -2); // [ package, loaded ]
        lua_pushstring(l, name); // [ package, loaded, name ]
        lua_gettable(l, -2);
        if (lua_isnil(l, -1)) { // [ package, loaded, nil ]
            luaL_newlib(l, reg); // [ package, loaded, nil, newlib ]
            lua_pushstring(l, name); // [ package, loaded, nil, newlib, name ]
            lua_replace(l, -3); // [ package, loaded, name, newlib ]
            lua_pushvalue(l, -1); // [ package, loaded, name, newlib, newlib ]
            lua_setglobal(l, name); // [ package, loaded, name, newlib ]
            lua_copy(l, -1, -4); // [ newlib, loaded, name, newlib ]
            lua_settable(l, -3); // [ newlib, loaded ]
        } else if (lua_istable(l, -1)) { // [ package, loaded, lib ]
            luaL_setfuncs(l, reg, 0);
            lua_replace(l, -1); // [ lib, loaded ]
        }
        lua_pop(l, 1); // [ lib ]
    } else {
        luaL_setfuncs(l, reg, 0);
    }
}
#define luaL_typerror luaL_typeerror
#define lua_objlen lua_rawlen
static inline int lua_cpcall(lua_State *l, lua_CFunction f, void *ud) {
    lua_pushcfunction(l, f);
    lua_pushlightuserdata(l, ud);
    return lua_pcall(l, 1, 0, 0);
}
#endif

typedef struct Task Task;

void InitLua();
void CloseLua();
void UpdateLua();

int RunLua(const char *luaFile, int priority, const char *argf, ...);
Task* GetLuaTask(int ref);

int LuaResultBool(int taskRef, int i);
lua_Number LuaResultNumber(int taskRef, int i);
const char* LuaResultString(int taskRef, int i);
void* LuaResultUserdata(int taskRef, int i, const char *udType);

int LuaResultFieldBool(int taskRef, int ti, const char *k);
lua_Number LuaResultFieldNumber(int taskRef, int ti, const char *k);
const char* LuaResultFieldString(int taskRef, int ti, const char *k);
void* LuaResultFieldUserdata(int taskRef, int ti, const char *k, const char *udType);

void UnrefLuaTask(int ref);

uint32_t L_toColorInt(lua_State *l, int i);
Color L_toColor(lua_State *l, int i);

#define L_tableToArgs(l, t, ...) { \
    static const char *FIELDS[] = {__VA_ARGS__}; \
    static const size_t NFIELDS = sizeof(FIELDS)/sizeof(FIELDS[0]); \
    for (int i = 1; i < NFIELDS; ++i) \
        lua_getfield(l, t, FIELDS[i]); \
    lua_getfield(l, t, FIELDS[0]); \
    lua_replace(l, t); \
}

#endif /* F368B866_5240_4102_BE90_898768165E85 */
