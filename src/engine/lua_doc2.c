#include <engine/lua_doc.h>

int L_doc_var(lua_State *l, VarDoc *var) {
    lua_newtable(l);
    if (var->name) {
        lua_pushstring(l, var->name);
        lua_setfield(l, -2, "name");
    }
    if (var->type) {
        lua_pushstring(l, var->type);
        lua_setfield(l, -2, "type");
    }
    if (var->desc) {
        lua_pushstring(l, var->desc);
        lua_setfield(l, -2, "description");
    }
    if (var->dflt) {
        lua_pushstring(l, var->dflt);
        lua_setfield(l, -2, "default");
    }
    return 1;
}

int L_doc_func(lua_State *l, FuncDoc *func) {
    lua_newtable(l);
    if (func->name) {
        lua_pushstring(l, func->name);
        lua_setfield(l, -2, "name");
    }
    if (func->desc) {
        lua_pushstring(l, func->desc);
        lua_setfield(l, -2, "description");
    }

    if (func->nArgs) {
        lua_newtable(l);
        for (int i = 1; i <= func->nArgs; ++i) {
            L_doc_var(l, &func->args[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "arguments");
    }

    if (func->nRets) {
        lua_newtable(l);
        for (int i = 1; i <= func->nRets; ++i) {
            L_doc_var(l, &func->rets[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "returns");
    }

    return 1;
}

int L_doc_class(lua_State *l, ClassDoc *cls) {
    lua_newtable(l);
    if (cls->name) {
        lua_pushstring(l, cls->name);
        lua_setfield(l, -2, "name");
    }
    if (cls->desc) {
        lua_pushstring(l, cls->desc);
        lua_setfield(l, -2, "description");
    }
    if (cls->nCtors) {
        lua_newtable(l);
        for (int i = 1; i <= cls->nCtors; ++i) {
            L_doc_func(l, &cls->ctors[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "constructors");
    }
    if (cls->nMethods) {
        lua_newtable(l);
        for (int i = 1; i <= cls->nMethods; ++i) {
            L_doc_func(l, &cls->methods[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "functions");
    }
    if (cls->nFields) {
        lua_newtable(l);
        for (int i = 1; i <= cls->nFields; ++i) {
            L_doc_var(l, &cls->fields[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "fields");
    }
    return 1;
}

int L_doc_module(lua_State *l, ModuleDoc *module) {
    lua_newtable(l);
    if (module->name) {
        lua_pushstring(l, module->name);
        lua_setfield(l, -2, "name");
    }
    if (module->desc) {
        lua_pushstring(l, module->desc);
        lua_setfield(l, -2, "description");
    }
    if (module->nConstants) {
        lua_newtable(l);
        for (int i = 1; i <= module->nConstants; ++i) {
            L_doc_var(l, &module->constants[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "constants");
    }
    
    if (module->nFuncs) {
        lua_newtable(l);
        for (int i = 1; i <= module->nFuncs; ++i) {
            L_doc_func(l, &module->funcs[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "functions");
    }
    
    if (module->nClasses) {
        lua_newtable(l);
        for (int i = 1; i <= module->nClasses; ++i) {
            L_doc_class(l, &module->classes[i]);
            lua_rawseti(l, -2, i);
        }
        lua_setfield(l, -2, "types");
    }
    return 1;
}
