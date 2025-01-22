#ifndef C9B2A184_9A49_4803_890A_1608AF458EA2
#define C9B2A184_9A49_4803_890A_1608AF458EA2

#include <lua.h>

void L_docfuncs_reg(lua_State *l, luaL_Reg *reg);
void L_docclassfuncs_reg(lua_State *l, const char *cls, luaL_Reg *reg);
int L_doc_load(lua_State *l);
int L_doc_save(lua_State *l);

#endif /* C9B2A184_9A49_4803_890A_1608AF458EA2 */
