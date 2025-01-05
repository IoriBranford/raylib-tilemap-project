#include <tmx.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <util/lua_class.h>

void L_put_property_in_table(tmx_property *property, void *userdata) {
    lua_State *l = userdata;
    lua_pushstring(l, property->name);
    if (property->type == PT_INT)
        lua_pushinteger(l, property->value.integer);
    else if (property->type == PT_FLOAT)
        lua_pushnumber(l, property->value.decimal);
    else if (property->type == PT_BOOL)
        lua_pushboolean(l, property->value.boolean);
    else if (property->type == PT_STRING)
        lua_pushstring(l, property->value.string);
    else if (property->type == PT_COLOR)
        lua_pushinteger(l, property->value.color);
    else if (property->type == PT_FILE)
        lua_pushstring(l, property->value.string);
    else if (property->type == PT_OBJECT)
        lua_pushinteger(l, property->value.object_id);
    else
        lua_pushnil(l);
    lua_settable(l, -3);
}

#define tmx_class_properties_getter(cls) \
int L_##cls##_get_properties(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    lua_newtable(l); \
    tmx_property_foreach((*o)->properties, L_put_property_in_table, l); \
    return 1; \
}

int L_tmx_load(lua_State *l) {
    const char *file = luaL_checkstring(l, 1);
    tmx_map *map = tmx_load(file);
    if (map) {
        tmx_map** ud = lua_newuserdata(l, sizeof(tmx_map*));
        *ud = map;
        luaL_setmetatable(l, "tmx_map");
        return 1;
    }
    
    lua_pushboolean(l, 0);
    lua_pushstring(l, tmx_strerr());
    return 2;
}

int L_tmx_map_gc(lua_State *l) {
    tmx_map **map = luaL_checkudata(l, 1, "tmx_map");
    if (*map) {
        tmx_map_free(*map);
        *map = NULL;
    }
    return 0;
}

int L_tmx_map_index(lua_State *l) {
    tmx_map **map = luaL_checkudata(l, 1, "tmx_map"); // [ map, k ]
    lua_pushstring(l, "get_"); // [ map, k, "get_" ]
    lua_pushvalue(l, 2); // [ map, k, "get_", k ]
    lua_concat(l, 2);  // [ map, k, "get_k" ]
    const char *name = lua_tostring(l, -1);
    lua_pop(l, 1);  // [ map, k ]
    luaL_getmetafield(l, 1, name);
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) { // [ map, k, v, set_k ]
        lua_pushvalue(l, 1);  // [ map, k, get_k, map ]
        lua_call(l, 1, 1);  // [ map, k ]
    } else {
        lua_pushnil(l);
    }

    return 1;
}

int L_tmx_map_newindex(lua_State *l) { // [ map, k, v ]
    tmx_map **map = luaL_checkudata(l, 1, "tmx_map");
    lua_pushstring(l, "set_"); // [ map, k, v, "set_" ]
    lua_pushvalue(l, 2); // [ map, k, v, "set_", k ]
    lua_concat(l, 2); // [ map, k, v, "set_k" ]
    const char *name = lua_tostring(l, -1);
    lua_pop(l, 1);  // [ map, k, v ]
    luaL_getmetafield(l, 1, name);
    if (lua_iscfunction(l, -1) || lua_isfunction(l, -1)) { // [ map, k, v, set_k ]
        lua_pushvalue(l, 1);  // [ map, k, v, set_k, map ]
        lua_pushvalue(l, 3);  // [ map, k, v, set_k, map, v ]
        lua_call(l, 3, 0);  // [ map, k, v ]
    } else {
    }

    return 0;
}

class_getter(tmx_map, string, class_type);
class_getter(tmx_map, number, width);
class_getter(tmx_map, number, height);
class_getter(tmx_map, number, tile_width);
class_getter(tmx_map, number, tile_height);
tmx_class_properties_getter(tmx_map)

void luaopen_tmx(lua_State *l) {
    lua_newtable(l);
    lua_pushstring(l, "load");
    lua_pushcfunction(l, L_tmx_load);
    lua_settable(l, -3);
    lua_setglobal(l, "tmx");

    luaL_newmetatable(l, "tmx_map");
    
    lua_pushstring(l, "__index");
    lua_pushcfunction(l, L_tmx_map_index);
    lua_settable(l, -3);
    
    lua_pushstring(l, "__newindex");
    lua_pushcfunction(l, L_tmx_map_newindex);
    lua_settable(l, -3);

    lua_pushstring(l, "__gc");
    lua_pushcfunction(l, L_tmx_map_gc);
    lua_settable(l, -3);

    class_init_getter(tmx_map, class_type);
    class_init_getter(tmx_map, width);
    class_init_getter(tmx_map, height);
    class_init_getter(tmx_map, tile_width);
    class_init_getter(tmx_map, tile_height);
    class_init_getter(tmx_map, properties);

    lua_pop(l, 1);
}