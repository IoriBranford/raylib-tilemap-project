#include <engine/lua_doc.h>

int L_doc_var(lua_State *l, const VarDoc *var) {
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

int L_doc_func(lua_State *l, const FuncDoc *func) {
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

int L_doc_class(lua_State *l, const ClassDoc *cls) {
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

int L_doc_module(lua_State *l, const ModuleDoc *module) {
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

void WriteFunction(FILE *file, const FuncDoc *func, const ClassDoc *cls) {
    fprintf(file, "--- %s\n", func->desc);
    for (int a = 0; a < func->nArgs; ++a) {
        const VarDoc *arg = &func->args[a];
        fprintf(file, "---@param %s %s %s\n", arg->name, arg->type, arg->desc);
    }
    for (int r = 0; r < func->nRets; ++r) {
        const VarDoc *ret = &func->rets[r];
        fprintf(file, "---@return %s %s %s\n", ret->type, ret->name, ret->desc);
    }
    if (cls)
        fprintf(file, "function %s:%s(", cls->name, func->name);
    else
        fprintf(file, "function %s(", func->name);
    if (func->nArgs)
        fprintf(file, "%s", func->args[0].name);
    for (int a = 1; a < func->nArgs; ++a) {
        const VarDoc *arg = &func->args[a];
        fprintf(file, ", %s", arg->name);
    }
    fprintf(file, ") end\n"
                    "\n");
}

void WriteClass(FILE *file, const ClassDoc *cls) {
    fprintf(file, "--- %s\n"
                    "---@class %s\n", cls->desc, cls->name);
    for (int a = 0; a < cls->nFields; ++a) {
        const VarDoc *field = &cls->fields[a];
        fprintf(file, "---@field %s %s %s\n", field->name, field->type, field->desc);
    }
    fprintf(file, "local %s = {}\n\n", cls->name);

    for (int f = 0; f < cls->nCtors; ++f) {
        WriteFunction(file, &cls->ctors[f], NULL);
    }

    for (int f = 0; f < cls->nMethods; ++f) {
        WriteFunction(file, &cls->methods[f], cls);
    }
}

int SaveModuleDoc(const ModuleDoc *module) {
    char s[128];
    sprintf(s, "lua/doc/%s.lua", module->name);

    FILE *file = fopen(s, "w");
    fprintf(file, "---@meta\n"
        "--- %s\n"
        "---@module '%s'\n"
        "\n",
        module->desc, module->name);

    for (int c = 0; c < module->nConstants; ++c) {
        const VarDoc constant = module->constants[c];
        fprintf(file, "--- %s\n"
                    "local %s\n"
                    "\n", constant.desc, constant.name);
    }

    for (int f = 0; f < module->nFuncs; ++f) {
        WriteFunction(file, &module->funcs[f], NULL);
    }

    for (int c = 0; c < module->nClasses; ++c) {
        WriteClass(file, &module->classes[c]);
    }

    fclose(file);

    return 0;
}