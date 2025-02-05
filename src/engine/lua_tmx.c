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

#define tmx_lclass_properties_getter(cls) \
int L_##cls##_getproperties(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    lua_newtable(l); \
    tmx_property_foreach((*o)->properties, L_put_property_in_table, l); \
    return 1; \
}
#define tmx_lclass_property_getter(cls) \
int L_##cls##_get_property(lua_State *l) { \
    cls **o = luaL_checkudata(l, 1, #cls); \
    L_push_property(l, tmx_get_property((**o).properties, luaL_checkstring(l, 2))); \
    return 1; \
}

lclass_ctor_1(tmx_map, *, LoadMap, , string)
lclass_gc(tmx_map, *, UnloadMap)
lclass_index_and_newindex(tmx_map)
lclass_getter(tmx_map, *, string, class_type)
lclass_getter(tmx_map, *, number, width)
lclass_getter(tmx_map, *, number, height)
lclass_getter(tmx_map, *, number, tile_width)
lclass_getter(tmx_map, *, number, tile_height)
tmx_lclass_properties_getter(tmx_map)
tmx_lclass_property_getter(tmx_map)

lclass_func_1_ud(tmx_map, *, find_object_by_id,
    tmx_find_object_by_id, integer,
    tmx_object, *, )
lclass_func_1_ud(tmx_map, *, find_layer_by_id,
    tmx_find_layer_by_id, integer,
    tmx_layer, *, )
lclass_func_1_ud(tmx_map, *, find_layer_by_name,
    tmx_find_layer_by_name, string,
    tmx_layer, *, )
lclass_func_1_ud(tmx_map, *, get_tile,
    tmx_get_tile, integer,
    tmx_tile, *, )

int L_tmx_map_get_layer_tile(lua_State *l) {
    tmx_map *map = *(tmx_map**)luaL_checkudata(l, 1, "tmx_map");
    tmx_layer *layer = *(tmx_layer**)luaL_checkudata(l, 2, "tmx_layer");
    int x = floor(luaL_checknumber(l, 3));
    int y = floor(luaL_checknumber(l, 4));
    uint32_t gid;
    tmx_tile *tile = tmx_get_layer_tile(map, layer, x, y, &gid);
    lclass_newuserdata(l, tmx_tile, tile);
    lua_pushboolean(l, gid & TMX_FLIPPED_HORIZONTALLY);
    lua_pushboolean(l, gid & TMX_FLIPPED_VERTICALLY);
    return 3;
}

int L_tmx_map_set_layer_tile(lua_State *l) {
    tmx_map *map = *(tmx_map**)luaL_checkudata(l, 1, "tmx_map");
    tmx_layer *layer = *(tmx_layer**)luaL_checkudata(l, 2, "tmx_layer");
    int x = floor(luaL_checknumber(l, 3));
    int y = floor(luaL_checknumber(l, 4));
    tmx_tile *tile = *(tmx_tile**)luaL_checkudata(l, 5, "tmx_tile");
    uint32_t flags = 0;
    if (lua_toboolean(l, 6))
        flags |= TMX_FLIPPED_HORIZONTALLY;
    if (lua_toboolean(l, 7))
        flags |= TMX_FLIPPED_VERTICALLY;
    tmx_set_layer_tile(map, layer, x, y, tile, flags);
    return 0;
}

int L_tmx_map_get_layer_gid(lua_State *l) {
    tmx_map *map = *(tmx_map**)luaL_checkudata(l, 1, "tmx_map");
    tmx_layer *layer = *(tmx_layer**)luaL_checkudata(l, 2, "tmx_layer");
    int x = floor(luaL_checknumber(l, 3));
    int y = floor(luaL_checknumber(l, 4));
    uint32_t gid = tmx_get_layer_gid(map, layer, x, y);
    lua_pushinteger(l, gid);
    return 1;
}

int L_tmx_map_set_layer_gid(lua_State *l) {
    tmx_map *map = *(tmx_map**)luaL_checkudata(l, 1, "tmx_map");
    tmx_layer *layer = *(tmx_layer**)luaL_checkudata(l, 2, "tmx_layer");
    int x = floor(luaL_checknumber(l, 3));
    int y = floor(luaL_checknumber(l, 4));
    uint32_t gid = floor(luaL_checknumber(l, 5));
    tmx_set_layer_gid(map, layer, x, y, gid);
    return 0;
}

lclass_index_and_newindex(tmx_layer)
lclass_getter(tmx_layer, *, integer, id)
lclass_getter(tmx_layer, *, string, class_type)
lclass_getter(tmx_layer, *, number, type)
tmx_lclass_properties_getter(tmx_layer)
tmx_lclass_property_getter(tmx_layer)

int L_tmx_layer_getobjects(lua_State *l) {
    tmx_layer **ud = luaL_checkudata(l, 1, "tmx_layer");
    tmx_layer *layer = *ud;
    if (layer->type == L_OBJGR) {
        lua_newtable(l);
        tmx_object *o = layer->content.objgr->head;
        for (int i = 1; o; ++i, o = o->next) {
            lclass_newuserdata(l, tmx_object, o);
            lua_rawseti(l, -2, i);
        }
        return 1;
    }
    return 0;
}

int L_tmx_layer_new_tilelayer_sprite(lua_State *l) {
    tmx_layer *layer = *(tmx_layer **)luaL_checkudata(l, 1, "tmx_layer");
    if (layer->type != L_LAYER)
        return 0;
    
    tmx_map *map = *(tmx_map **)luaL_checkudata(l, 2, "tmx_map");
    Rectangle source = {
        .x = luaL_optnumber(l, 3, 0),
        .y = luaL_optnumber(l, 4, 0),
        .width = luaL_optnumber(l, 5, 0),
        .height = luaL_optnumber(l, 6, 0),
    };
    Rectangle rect = {
        .x = luaL_optnumber(l, 7, 0),
        .y = luaL_optnumber(l, 8, 0),
        .width = luaL_optnumber(l, 9, 0),
        .height = luaL_optnumber(l, 10, 0),
    };
    Sprite *spr = NewTileLayerSprite(layer, map, source, rect);
    lclass_newuserdata(l, Sprite, spr);
    return 1;
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
            lclass_newuserdata(l, Sprite, spr);
        } break;
        case L_LAYER: {
            Sprite *spr = NewTileLayerSprite(*layer, *m, (Rectangle){0}, (Rectangle){0});
            spr->z = z;
            lclass_newuserdata(l, Sprite, spr);
        } break;
        case L_OBJGR: {
            lua_newtable(l);
            tmx_object *o = (*layer)->content.objgr->head;
            Color tint = tmx2rl_Color((*layer)->tintcolor);
            for (int i = 1; o; ++i, o = o->next) {
                Sprite *spr = NewTMXObjectSprite(o, *m, tint);
                if (!spr) continue;
                spr->z = z;
                lclass_newuserdata(l, Sprite, spr);
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
                lclass_newuserdata(l, tmx_layer, sublayer);
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
        lclass_newuserdata(l, tmx_layer, layer);
        lua_pushvalue(l, 1);
        lua_pushnumber(l, z);
        lua_pushnumber(l, 1);
        z += 1;
        lua_pcall(l, 4, 1, 0);
        lua_rawseti(l, -2, i);
    }
    return 1;
}

lclass_index_and_newindex(tmx_object)
lclass_getter(tmx_object, *, string, type)
lclass_getter(tmx_object, *, integer, id)
lclass_getter(tmx_object, *, number, x)
lclass_getter(tmx_object, *, number, y)
lclass_getter(tmx_object, *, number, width)
lclass_getter(tmx_object, *, number, height)
tmx_lclass_properties_getter(tmx_object)
tmx_lclass_property_getter(tmx_object)

int L_tmx_object_new_body(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    lclass_newuserdata(l, cpBody, AddNewTMXObjectBody(*o, *m));
    return 1;
}

int L_tmx_object_new_sprite(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    Color color = L_toColor(l, 3);
    lclass_newuserdata(l, Sprite, NewTMXObjectSprite(*o, *m, color));
    return 1;
}

int L_tmx_object_get_tile(lua_State *l) {
    tmx_object **o = luaL_checkudata(l, 1, "tmx_object");
    tmx_map **m = luaL_checkudata(l, 2, "tmx_map");
    tmx_tile *tile = GetTMXObjectTile(*o, *m);
    if (!tile)
        return 0;
    lclass_newuserdata(l, tmx_tile, tile);
    return 1;
}

lclass_index_and_newindex(tmx_tile)
lclass_getter(tmx_tile, *, integer, id)
lclass_getter(tmx_tile, *, string, type)
lclass_getter(tmx_tile, *, number, width)
lclass_getter(tmx_tile, *, number, height)
tmx_lclass_properties_getter(tmx_tile)
tmx_lclass_property_getter(tmx_tile)

int L_tmx_tile_new_sprite(lua_State *l) {
    tmx_tile *t = *(tmx_tile**)luaL_checkudata(l, 1, "tmx_tile");
    Rectangle r = {
        .x = luaL_optnumber(l, 2, 0),
        .y = luaL_optnumber(l, 3, 0),
        .width = luaL_optnumber(l, 4, t->width),
        .height = luaL_optnumber(l, 5, t->height),
    };
    lua_Number rotationDeg = luaL_optnumber(l, 6, 0);
    Color color = L_toColor(l, 7);
    lclass_newuserdata(l, Sprite, NewTileSprite(t, r, rotationDeg, color));
    return 1;
}

int L_tmx_tile_getcollision(lua_State *l) {
    tmx_tile **o = luaL_checkudata(l, 1, "tmx_tile");
    lua_newtable(l);
    tmx_object *col = (**o).collision;
    for (int i = 1; col; ++i, col = col->next) {
        lclass_newuserdata(l, tmx_object, col);
        lua_rawseti(l, -2, i);
    }
    return 1;
}

l_global_funcs_luaopen(tmx_g, 
    lfunc_reg(LoadMap)
)

lclass_luaopen(tmx_map,
    lclass_method_reg(tmx_map, __index),
    lclass_method_reg(tmx_map, __newindex),
    lclass_method_reg(tmx_map, __gc),
    lclass_method_reg(tmx_map, get_tile),
    lclass_method_reg(tmx_map, get_property),
    lclass_method_reg(tmx_map, get_layer_tile),
    lclass_method_reg(tmx_map, set_layer_tile),
    lclass_method_reg(tmx_map, get_layer_gid),
    lclass_method_reg(tmx_map, set_layer_gid),
    lclass_method_reg(tmx_map, find_object_by_id),
    lclass_method_reg(tmx_map, find_layer_by_id),
    lclass_method_reg(tmx_map, find_layer_by_name),
    lclass_method_reg(tmx_map, new_sprites),
    lclass_getter_reg(tmx_map, class_type),
    lclass_getter_reg(tmx_map, width),
    lclass_getter_reg(tmx_map, height),
    lclass_getter_reg(tmx_map, tile_width),
    lclass_getter_reg(tmx_map, tile_height),
    lclass_getter_reg(tmx_map, properties)
)

lclass_luaopen(tmx_layer,
    lclass_method_reg(tmx_layer, __index),
    lclass_method_reg(tmx_layer, __newindex),
    lclass_method_reg(tmx_layer, get_property),
    lclass_method_reg(tmx_layer, new_tilelayer_sprite),
    lclass_method_reg(tmx_layer, new_sprites),
    lclass_getter_reg(tmx_layer, id),
    lclass_getter_reg(tmx_layer, class_type),
    lclass_getter_reg(tmx_layer, type),
    lclass_getter_reg(tmx_layer, objects),
    lclass_getter_reg(tmx_layer, properties)
)

lclass_luaopen(tmx_tile,
    lclass_method_reg(tmx_tile, __index),
    lclass_method_reg(tmx_tile, __newindex),
    lclass_method_reg(tmx_tile, get_property),
    lclass_method_reg(tmx_tile, new_sprite),
    lclass_getter_reg(tmx_tile, id),
    lclass_getter_reg(tmx_tile, type),
    lclass_getter_reg(tmx_tile, width),
    lclass_getter_reg(tmx_tile, height),
    lclass_getter_reg(tmx_tile, collision),
    lclass_getter_reg(tmx_tile, properties)
)

lclass_luaopen(tmx_object,
    lclass_method_reg(tmx_object, __index),
    lclass_method_reg(tmx_object, __newindex),
    lclass_method_reg(tmx_object, get_property),
    lclass_method_reg(tmx_object, get_tile),
    lclass_method_reg(tmx_object, new_body),
    lclass_method_reg(tmx_object, new_sprite),
    lclass_getter_reg(tmx_object, id),
    lclass_getter_reg(tmx_object, type),
    lclass_getter_reg(tmx_object, x),
    lclass_getter_reg(tmx_object, y),
    lclass_getter_reg(tmx_object, width),
    lclass_getter_reg(tmx_object, height),
    lclass_getter_reg(tmx_object, properties)
)

int luaopen_tmx(lua_State *l) {
    lua_cpcall(l, luaopen_tmx_g, NULL);
    lua_cpcall(l, luaopen_tmx_layer, NULL);
    lua_cpcall(l, luaopen_tmx_tile, NULL);
    lua_cpcall(l, luaopen_tmx_object, NULL);
    lua_cpcall(l, luaopen_tmx_map, NULL);
    return 0;
}