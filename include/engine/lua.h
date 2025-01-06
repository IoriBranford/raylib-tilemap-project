#ifndef F368B866_5240_4102_BE90_898768165E85
#define F368B866_5240_4102_BE90_898768165E85

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void InitLua();
void CloseLua();

int RunLua(const char *luaFile, int priority);

#endif /* F368B866_5240_4102_BE90_898768165E85 */
