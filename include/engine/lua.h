#ifndef F368B866_5240_4102_BE90_898768165E85
#define F368B866_5240_4102_BE90_898768165E85

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct Task Task;

void InitLua();
void CloseLua();

int RunLua(const char *luaFile, int priority);
Task* GetLuaTask(int ref);
void ReleaseLuaTask(int ref);

#endif /* F368B866_5240_4102_BE90_898768165E85 */
