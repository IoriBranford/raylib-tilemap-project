#include <tmx.h>
#include <engine/assets.h>
#include <engine/gfx2d.h>
#include <engine/physics.h>
#include <engine/lua.h>

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
        lua_pushinteger(l, tmx2rl_ColorUint(property->value.color));
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
int L_##cls##_getproperties(lua_State *l) { \
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
tmx_class_property_getter(tmx_map)

class_func_1_ud(tmx_map, *, find_object_by_id,
    tmx_find_object_by_id, integer,
    tmx_object, *, )
class_func_1_ud(tmx_map, *, find_layer_by_id,
    tmx_find_layer_by_id, integer,
    tmx_layer, *, )
class_func_1_ud(tmx_map, *, find_layer_by_name,
    tmx_find_layer_by_name, string,
    tmx_layer, *, )

class_index_and_newindex(tmx_layer)
class_getter(tmx_layer, *, integer, id)
class_getter(tmx_layer, *, string, class_type)
class_getter(tmx_layer, *, number, type)
tmx_class_properties_getter(tmx_layer)
tmx_class_property_getter(tmx_layer)

int L_tmx_layer_getobjects(lua_State *l) {
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

int L_tmx_layer_new_sprites(lua_State *l) {
    tmx_layer **layer = (tmx_layer **)luaL_checkudata(l, 1, "tmx_layer");
    tmx_map **m = (tmx_map **)luaL_checkudata(l, 2, "tmx_map");
    lua_Number z = luaL_optnumber(l, 3, 0);
    lua_Number dz = luaL_optnumber(l, 4, 1);
    switch ((*layer)->type) {
        case L_IMAGE: {
            Sprite *spr = NewImageLayerSprite(*layer);
            spr->z = z;
            class_newuserdata(l, Sprite, spr);
        } break;
        case L_LAYER: {
            Sprite *spr = NewTileLayerSprite(*layer, *m);
            spr->z = z;
            class_newuserdata(l, Sprite, spr);
        } break;
        case L_OBJGR: {
            lua_newtable(l);
            tmx_object *o = (*layer)->content.objgr->head;
            Color tint = tmx2rl_Color((*layer)->tintcolor);
            for (int i = 1; o; ++i, o = o->next) {
                Sprite *spr = NewTMXObjectSprite(o, *m, tint);
                if (!spr) continue;
                spr->z = z;
                class_newuserdata(l, Sprite, spr);
                lua_rawseti(l, -2, i);
            }
        } break;
        case L_GROUP: {
            tmx_layer *sublayer = (*layer)->content.group_head;
            if (!sublayer)
                return 0;

            int n = 0;
            for (; sublayer; sublayer = sublayer->next) ++n;
            dz = dz/n;

            lua_newtable(l);
            sublayer = (*layer)->content.group_head;
            for (int i = 1; sublayer; ++i, sublayer = sublayer->next) {
                lua_pushcfunction(l, L_tmx_layer_new_sprites);
                class_newuserdata(l, tmx_layer, sublayer);
                lua_pushvalue(l, 2);
                lua_pushnumber(l, z);
                lua_pushnumber(l, dz);
                z += dz;
                lua_pcall(l, 4, 1, 0);
                lua_rawseti(l, -2, i);
            }
        } break;
    }
    return 1;
}

int L_tmx_map_new_sprites(lua_State *l) {
    tmx_map **m = (tmx_map **)luaL_checkudata(l, 1, "tmx_map");
    lua_Number z = luaL_optnumber(l, 2, 0);

    lua_newtable(l);
    tmx_layer *layer = (**m).ly_head;
    for (int i = 1; layer; ++i, layer = layer->next) {
        lua_pushcfunction(l, L_tmx_layer_new_sprites);
        class_newuserdata(l, tmx_layer, layer);
        lua_pushvalue(l, 1);
        lua_pushnumber(l, z);
        lua_pushnumber(l, 1);
        z += 1;
        lua_pcall(l, 4, 1, 0);
        lua_rawseti(l, -2, i);
    }
    return 1;
}

class_index_and_newindex(tmx_object)
class_getter(tmx_object, *, string, type)
class_getter(tmx_object, *, integer, id)
class_getter(tmx_object, *, number, x)
class_getter(tmx_object, *, number, y)
class_getter(tmx_object, *, number, width)
class_getter(tmx_object, *, number, height)
tmx_class_properties_getter(tmx_object)
tmx_class_property_getter(tmx_object)

int L_tmx_object_new_body(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    class_newuserdata(l, cpBody, NewTMXObjectBody(*o, *m));
    return 1;
}

int L_tmx_object_new_sprite(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    Color color = L_toColor(l, 3);
    class_newuserdata(l, Sprite, NewTMXObjectSprite(*o, *m, color));
    return 1;
}

int L_tmx_object_get_tile(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    tmx_tile *tile = GetTMXObjectTile(*o, *m);
    if (!tile)
        return 0;
    class_newuserdata(l, tmx_tile, tile);
    return 1;
}

class_index_and_newindex(tmx_tile)
class_getter(tmx_tile, *, integer, id)
class_getter(tmx_tile, *, string, type)
class_getter(tmx_tile, *, number, width)
class_getter(tmx_tile, *, number, height)
tmx_class_properties_getter(tmx_tile)
tmx_class_property_getter(tmx_tile)

int L_tmx_tile_getcollision(lua_State *l) {
    tmx_tile **o = luaL_checkudata(l, 1, "tmx_tile");
    lua_newtable(l);
    tmx_object *col = (**o).collision;
    for (int i = 1; col; ++i, col = col->next) {
        class_newuserdata(l, tmx_object, col);
        lua_rawseti(l, -2, i);
    }
    return 1;
}

l_global_funcs_luaopen(tmx_g, 
    l_func_reg(LoadMap)
)

class_luaopen(tmx_map,
    class_method_reg(tmx_map, __index),
    class_method_reg(tmx_map, __newindex),
    class_method_reg(tmx_map, __gc),
    class_method_reg(tmx_map, get_property),
    class_method_reg(tmx_map, find_object_by_id),
    class_method_reg(tmx_map, find_layer_by_id),
    class_method_reg(tmx_map, find_layer_by_name),
    class_method_reg(tmx_map, new_sprites),
    class_getter_reg(tmx_map, class_type),
    class_getter_reg(tmx_map, width),
    class_getter_reg(tmx_map, height),
    class_getter_reg(tmx_map, tile_width),
    class_getter_reg(tmx_map, tile_height),
    class_getter_reg(tmx_map, properties)
)

class_luaopen(tmx_layer,
    class_method_reg(tmx_layer, __index),
    class_method_reg(tmx_layer, __newindex),
    class_method_reg(tmx_layer, get_property),
    class_method_reg(tmx_layer, new_sprites),
    class_getter_reg(tmx_layer, id),
    class_getter_reg(tmx_layer, class_type),
    class_getter_reg(tmx_layer, type),
    class_getter_reg(tmx_layer, objects),
    class_getter_reg(tmx_layer, properties)
)

class_luaopen(tmx_tile,
    class_method_reg(tmx_tile, __index),
    class_method_reg(tmx_tile, __newindex),
    class_method_reg(tmx_tile, get_property),
    class_getter_reg(tmx_tile, id),
    class_getter_reg(tmx_tile, type),
    class_getter_reg(tmx_tile, width),
    class_getter_reg(tmx_tile, height),
    class_getter_reg(tmx_tile, collision),
    class_getter_reg(tmx_tile, properties)
)

class_luaopen(tmx_object,
    class_method_reg(tmx_object, __index),
    class_method_reg(tmx_object, __newindex),
    class_method_reg(tmx_object, get_property),
    class_method_reg(tmx_object, get_tile),
    class_method_reg(tmx_object, new_body),
    class_method_reg(tmx_object, new_sprite),
    class_getter_reg(tmx_object, id),
    class_getter_reg(tmx_object, type),
    class_getter_reg(tmx_object, x),
    class_getter_reg(tmx_object, y),
    class_getter_reg(tmx_object, width),
    class_getter_reg(tmx_object, height),
    class_getter_reg(tmx_object, properties)
)

int luaopen_tmx(lua_State *l) {
    lua_cpcall(l, luaopen_tmx_g, NULL);
    lua_cpcall(l, luaopen_tmx_layer, NULL);
    lua_cpcall(l, luaopen_tmx_tile, NULL);
    lua_cpcall(l, luaopen_tmx_object, NULL);
    lua_cpcall(l, luaopen_tmx_map, NULL);
    return 0;
}