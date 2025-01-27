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
int SaveModuleDoc(const ModuleDoc *module);

#define doc_func(f, fdesc, na, ...)  \
    static const VarDoc doc_##f##_vars[] = {__VA_ARGS__ __VA_OPT__(,) {0}}; \
    static const FuncDoc doc_##f = { \
        .name = #f, .desc = fdesc, \
        .nArgs = na, .args = doc_##f##_vars, \
        .nRets = sizeof(doc_##f##_vars)/sizeof(VarDoc) - na - 1, .rets = doc_##f##_vars + na \
    };

#define doc_var(n, t, d, df) { .name = #n, .type = #t, .desc = d, .dflt = df }

#define doc_module_constants(...) const VarDoc constants[] = {__VA_ARGS__ __VA_OPT__(,) {0}};
#define doc_module_funcs(...) const FuncDoc funcs[] = {__VA_ARGS__ __VA_OPT__(,) {0}};
#define doc_module_classes(...) const ClassDoc classes[] = {__VA_ARGS__ __VA_OPT__(,) {0}};
#define doc_module(m, mdesc, ...) { \
    __VA_ARGS__ \
    const ModuleDoc m = { \
        .name = #m, .desc = mdesc, \
        .constants = constants, .nConstants = sizeof(constants)/sizeof(VarDoc) - 1, \
        .funcs = funcs, .nFuncs = sizeof(funcs)/sizeof(FuncDoc) - 1, \
        .classes = classes, .nClasses = sizeof(classes)/sizeof(ClassDoc) - 1, \
    }; \
    SaveModuleDoc(&m); \
}


#endif /* C9B2A184_9A49_4803_890A_1608AF458EA2 */
