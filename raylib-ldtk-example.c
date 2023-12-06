#include <ldtk.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *ldtk_text = LoadFileText("assets/level.ldtk");
    if (!ldtk_text) {
        return 1;
    }

    struct LDtk *ldtk = cJSON_ParseLDtk(ldtk_text);
    free(ldtk_text);

    list_t *levels = ldtk->levels;
    struct Level *level = list_get_head(levels);
    list_t *layers = level->layer_instances;
    struct LayerInstance *layer;
    for (layer = list_get_head(layers); layer; layer = list_get_next(layers)) {
        if (strcmp("Ground", layer->identifier) == 0) {
            break;
        }
    }

    char filepath[256];

    snprintf(filepath, 255, "assets/%s", layer->tileset_rel_path);
    list_t *tiles = layer->auto_layer_tiles;

    InitWindow(level->px_wid * 4, level->px_hei * 4, "ldtk - Raylib");
    SetTargetFPS(60);

    Texture2D texture = LoadTexture(filepath);
    RenderTexture2D renderer = LoadRenderTexture(level->px_wid, level->px_hei);

    // Draw all the tiles.
    BeginTextureMode(renderer);
    ClearBackground(BLACK);
    for (struct TileInstance *tile = list_get_head(tiles); tile; tile = list_get_next(tiles)) {
        int64_t srcx = *(int64_t*)list_get_head(tile->src);
        int64_t srcy = *(int64_t*)list_get_next(tile->src);
        int64_t destx = *(int64_t*)list_get_head(tile->px);
        int64_t desty = *(int64_t*)list_get_next(tile->px);
        Vector2 dest = {destx, desty};
        float sizex = layer->grid_size * (tile->f & 1 ? -1.f : 1.f);
        float sizey = layer->grid_size * (tile->f & 2 ? -1.f : 1.f);
        Rectangle src = {
            srcx, srcy, sizex, sizey
        };
        DrawTextureRec(texture, src, dest, WHITE);
    }
    EndTextureMode();

    while (!WindowShouldClose()) {
        // Scale up the Renderer times 4.
        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        BeginDrawing();
        Rectangle src = {
            0,
            0,
            (renderer.texture.width),
            -(renderer.texture.height)
        };
        Rectangle dest = {
            0,
            0,
            (renderer.texture.width) * 4,
            (renderer.texture.height) * 4
        };
        DrawTexturePro(renderer.texture, src, dest, (Vector2){0, 0}, .0f, WHITE);
        EndDrawing();
    }

    // Unload everything before leaving.
    UnloadRenderTexture(renderer);
    UnloadTexture(texture);
    CloseWindow();

    cJSON_DeleteLDtk(ldtk);
    return 0;
}