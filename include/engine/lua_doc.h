#ifndef C9B2A184_9A49_4803_890A_1608AF458EA2
#define C9B2A184_9A49_4803_890A_1608AF458EA2

#include <lua.h>
#include <lauxlib.h>

typedef struct VarDoc {
    const char *name, *type, *desc, *dflt;
} VarDoc;

typedef struct FuncDoc {
    const char *name, *desc;
    int nArgs;
    const VarDoc *args;
    int nRets;
    const VarDoc *rets;
} FuncDoc;

typedef struct ClassDoc {
    const char *name, *desc;
    int nFields;
    const VarDoc *fields;
    int nCtors;
    const FuncDoc *ctors;
    int nMethods;
    const FuncDoc *methods;
} ClassDoc;

typedef struct ModuleDoc {
    const char *name, *desc;
    int nConstants;
    const VarDoc *constants;
    int nFuncs;
    const FuncDoc *funcs;
    int nClasses;
    const ClassDoc *classes;
} ModuleDoc;

int L_doc_var(lua_State *l, const VarDoc *var);
int L_doc_func(lua_State *l, const FuncDoc *func);
int L_doc_class(lua_State *l, const ClassDoc *cls);
int L_doc_module(lua_State *l, const ModuleDoc *module);

void L_docfuncs_reg(lua_State *l, luaL_Reg *reg);
void L_docclassfuncs_reg(lua_State *l, const char *cls, luaL_Reg *reg);
int L_doc_load(lua_State *l);
int L_doc_save(lua_State *l);

#endif /* C9B2A184_9A49_4803_890A_1608AF458EA2 */
