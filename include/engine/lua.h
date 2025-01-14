#ifndef F368B866_5240_4102_BE90_898768165E85
#define F368B866_5240_4102_BE90_898768165E85

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct Task Task;

void InitLua();
void CloseLua();
void UpdateLua();

int RunLua(const char *luaFile, int priority, const char *argf, ...);
Task* GetLuaTask(int ref);

int LuaResultBool(int taskRef, int i);
lua_Integer LuaResultInt(int taskRef, int i);
lua_Number LuaResultNumber(int taskRef, int i);
const char* LuaResultString(int taskRef, int i);
void* LuaResultUserdata(int taskRef, int i, const char *udType);

int LuaResultFieldBool(int taskRef, int ti, const char *k);
lua_Integer LuaResultFieldInt(int taskRef, int ti, const char *k);
lua_Number LuaResultFieldNumber(int taskRef, int ti, const char *k);
const char* LuaResultFieldString(int taskRef, int ti, const char *k);
void* LuaResultFieldUserdata(int taskRef, int ti, const char *k, const char *udType);

void ReleaseLuaTaskRef(int ref);

#endif /* F368B866_5240_4102_BE90_898768165E85 */
