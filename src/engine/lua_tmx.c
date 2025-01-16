#include <tmx.h>
#include <engine/assets.h>
#include <engine/lua.h>
#include <util/lua_class.h>

void L_put_property_in_table(tmx_property *property, void *userdata) {
    lua_State *l = userdata;
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
    lua_setfield(l, -2, property->name);
}

#define tmx_class_properties_getter(cls) \
int L_##cls##___getproperties(lua_State *l) { \
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

int L_tmx_map___gc(lua_State *l) {
    tmx_map **map = luaL_checkudata(l, 1, "tmx_map");
    if (*map) {
        UnloadMap(*map);
        *map = NULL;
    }
    return 0;
}

class_index_and_newindex(tmx_map);

int L_tmx_layer___getobjects(lua_State *l) {
    tmx_layer **ud = luaL_checkudata(l, 1, "tmx_layer");
    tmx_layer *layer = *ud;
    if (layer->type == L_OBJGR) {
        lua_newtable(l);
        tmx_object *o = layer->content.objgr->head;
        for (int i = 1; o; ++i, o = o->next) {
            lua_pushinteger(l, i);
            class_newuserdata(l, tmx_object, o);
            lua_settable(l, -3);
        }
        return 1;
    }
    return 0;
}

int L_tmx_map_find_object_by_id(lua_State *l) {
    tmx_map **map = luaL_checkudata(l, 1, "tmx_map");
    int id = luaL_checkinteger(l, 2);
    tmx_object *o = tmx_find_object_by_id(*map, id);
    if (o) {
        class_newuserdata(l, tmx_object, o);
        return 1;
    }
    return 0;
}

class_getter(tmx_map, string, class_type);
class_getter(tmx_map, number, width);
class_getter(tmx_map, number, height);
class_getter(tmx_map, number, tile_width);
class_getter(tmx_map, number, tile_height);
tmx_class_properties_getter(tmx_map);

class_getter(tmx_layer, string, class_type);
class_getter(tmx_layer, number, type);
tmx_class_properties_getter(tmx_layer);

class_getter(tmx_object, string, type);
class_getter(tmx_object, number, x);
class_getter(tmx_object, number, y);
class_getter(tmx_object, number, width);
class_getter(tmx_object, number, height);
tmx_class_properties_getter(tmx_object);

void luaopen_tmx(lua_State *l) {
    luaL_Reg tmx_r[] = {
        class_method_reg(tmx, load),
        {0}
    };
    luaL_register(l, "tmx", tmx_r);
    lua_pop(l, 1);

    luaL_newmetatable(l, "tmx_layer");
    luaL_Reg tmx_layer_r[] = {
        class_getter_reg(tmx_layer, class_type),
        class_getter_reg(tmx_layer, type),
        class_getter_reg(tmx_layer, objects),
        class_getter_reg(tmx_layer, properties),
        {0}
    };
    luaL_register(l, NULL, tmx_layer_r);
    lua_pop(l, 1);

    luaL_newmetatable(l, "tmx_object");
    luaL_Reg tmx_object_r[] = {
        class_getter_reg(tmx_object, type),
        class_getter_reg(tmx_object, x),
        class_getter_reg(tmx_object, y),
        class_getter_reg(tmx_object, width),
        class_getter_reg(tmx_object, height),
        class_getter_reg(tmx_object, properties),
        {0}
    };
    luaL_register(l, NULL, tmx_object_r);
    lua_pop(l, 1);

    luaL_newmetatable(l, "tmx_map");
    luaL_Reg tmx_map_r[] = {
        class_method_reg(tmx_map, __index),
        class_method_reg(tmx_map, __newindex),
        class_method_reg(tmx_map, __gc),
        class_method_reg(tmx_map, find_object_by_id),
        class_getter_reg(tmx_map, class_type),
        class_getter_reg(tmx_map, width),
        class_getter_reg(tmx_map, height),
        class_getter_reg(tmx_map, tile_width),
        class_getter_reg(tmx_map, tile_height),
        class_getter_reg(tmx_map, properties),
        {0}
    };
    luaL_register(l, NULL, tmx_map_r);
    lua_pop(l, 1);
}