#include <tmx.h>
#include <engine/assets.h>
#include <engine/gfx2d.h>
#include <engine/physics.h>
#include <engine/lua.h>
#include <util/lua_class.h>

void L_push_property(lua_State *l, tmx_property *property) {
    if (!property)
        lua_pushnil(l);
    else if (property->type == PT_INT)
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
}

void L_put_property_in_table(tmx_property *property, void *userdata) {
    lua_State *l = userdata;
    L_push_property(l, property);
    lua_setfield(l, -2, property->name);
}

#define tmx_class_properties_getter(cls) \
int L_##cls##___getproperties(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    lua_newtable(l); \
    tmx_property_foreach((*o)->properties, L_put_property_in_table, l); \
    return 1; \
}
#define tmx_class_property_getter(cls) \
int L_##cls##_get_property(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    L_push_property(l, tmx_get_property((**o).properties, luaL_checkstring(l, 2))); \
    return 1; \
}

class_ctor_1(tmx_map, *, LoadMap, , string)
class_gc(tmx_map, *, UnloadMap)
class_index_and_newindex(tmx_map)
class_getter(tmx_map, *, string, class_type)
class_getter(tmx_map, *, number, width)
class_getter(tmx_map, *, number, height)
class_getter(tmx_map, *, number, tile_width)
class_getter(tmx_map, *, number, tile_height)
tmx_class_properties_getter(tmx_map)

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

class_index_and_newindex(tmx_layer)
class_getter(tmx_layer, *, string, class_type)
class_getter(tmx_layer, *, number, type)
tmx_class_properties_getter(tmx_layer)

int L_tmx_layer___getobjects(lua_State *l) {
    tmx_layer **ud = luaL_checkudata(l, 1, "tmx_layer");
    tmx_layer *layer = *ud;
    if (layer->type == L_OBJGR) {
        lua_newtable(l);
        tmx_object *o = layer->content.objgr->head;
        for (int i = 1; o; ++i, o = o->next) {
            class_newuserdata(l, tmx_object, o);
            lua_rawseti(l, -2, i);
        }
        return 1;
    }
    return 0;
}

class_index_and_newindex(tmx_object)
class_getter(tmx_object, *, string, type)
class_getter(tmx_object, *, number, x)
class_getter(tmx_object, *, number, y)
class_getter(tmx_object, *, number, width)
class_getter(tmx_object, *, number, height)
tmx_class_properties_getter(tmx_object)

int L_tmx_object_new_body(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    class_newuserdata(l, cpBody, NewTMXObjectBody(*o, *m));
    return 1;
}

int L_tmx_object_new_sprite(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    lua_Number r = luaL_optnumber(l, 3, 255);
    lua_Number g = luaL_optnumber(l, 4, 255);
    lua_Number b = luaL_optnumber(l, 5, 255);
    lua_Number a = luaL_optnumber(l, 6, 255);
    Color color = {
        r < 0 ? 0 : r > 255 ? 255 : r,
        g < 0 ? 0 : g > 255 ? 255 : g,
        b < 0 ? 0 : b > 255 ? 255 : b,
        a < 0 ? 0 : a > 255 ? 255 : a,
    };
    class_newuserdata(l, Sprite, NewTMXObjectSprite(*o, *m, color));
    return 1;
}

int luaopen_tmx(lua_State *l) {
    lua_getglobal(l, "_G");
    luaL_Reg globalFuncs[] = {
        l_func_reg(LoadMap),
        {0}
    };
    luaL_register(l, NULL, globalFuncs);
    lua_pop(l, 1);

    luaL_newmetatable(l, "tmx_layer");
    luaL_Reg tmx_layer_r[] = {
        class_method_reg(tmx_layer, __index),
        class_method_reg(tmx_layer, __newindex),
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
        class_method_reg(tmx_object, __index),
        class_method_reg(tmx_object, __newindex),
        class_method_reg(tmx_object, new_body),
        class_method_reg(tmx_object, new_sprite),
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

    return 0;
}