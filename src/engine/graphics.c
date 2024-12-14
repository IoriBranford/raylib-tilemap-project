#include <func.h>
#include <stdlib.h>
#include <assert.h>

#include <raylib-tmx.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include <raylib-aseprite.h>

struct Graphic;
typedef void (*GraphicFunction)(struct Graphic*);

typedef enum GraphicType {
    GRAPHICTYPE_NONE,
    GRAPHICTYPE_RECTANGLE,
    GRAPHICTYPE_TEXTURE,
    GRAPHICTYPE_TEXT,
    GRAPHICTYPE_TILE,
    GRAPHICTYPE_ASEPRITETAG,
    GRAPHICTYPE_TYPES
} GraphicType;

typedef struct GraphicBehavior {
    GraphicType type;
    GraphicFunction update, draw;
} GraphicBehavior;

typedef struct Graphic {
    Rectangle rect;
    Vector2 origin;
    float rotationDeg;
    Color color;

    GraphicBehavior behavior;
    union {
        struct {
            Texture2D texture;
            Rectangle source;
        } texture;

        struct {
            Font font;
            const char *text;
            float fontSize;
            float spacing;
        } text;

        struct {
            tmx_tile *tile;
            // TODO animation vars
        } tile;

        AsepriteTag asepriteTag;
    };
} Graphic;

void UpdateGraphic(Graphic *g) {
    g->behavior.update(g);
}

void DrawGraphic(Graphic *g) {
    g->behavior.draw(g);
}

void DrawGraphic_Rectangle(Graphic *g) {
    assert(g->behavior.type == GRAPHICTYPE_RECTANGLE);
    DrawRectanglePro(g->rect, g->origin, g->rotationDeg, g->color);
}

void DrawGraphic_Texture(Graphic *g) {
    assert(g->behavior.type == GRAPHICTYPE_TEXTURE);
    DrawTexturePro(g->texture.texture, g->texture.source, g->rect, g->origin, g->rotationDeg, g->color);
}

void DrawGraphic_Text(Graphic *g) {
    assert(g->behavior.type == GRAPHICTYPE_TEXT);
    Vector2 position = { g->rect.x, g->rect.y };
    DrawTextPro(g->text.font, g->text.text, position, g->origin, g->rotationDeg, g->text.fontSize, g->text.spacing, g->color);
}

void DrawGraphic_Tile(Graphic *g) {
    assert(g->behavior.type == GRAPHICTYPE_TILE);
    DrawTMXTilePro(g->tile.tile, g->rect, g->rotationDeg, g->color);
}

void UpdateGraphic_AsepriteTag(Graphic *g) {
    assert(g->behavior.type == GRAPHICTYPE_ASEPRITETAG);
    UpdateAsepriteTag(&g->asepriteTag);
}

void DrawGraphic_AsepriteTag(Graphic *g) {
    assert(g->behavior.type == GRAPHICTYPE_ASEPRITETAG);
    DrawAsepriteTagPro(g->asepriteTag, g->rect, g->origin, g->rotationDeg, g->color);
}

static void Nop(Graphic *_) {}

static const GraphicBehavior BEHAVIORS[GRAPHICTYPE_TYPES] = {
    [GRAPHICTYPE_NONE] = {
        .type = GRAPHICTYPE_NONE,
        .update = Nop,
        .draw = Nop
    },
    [GRAPHICTYPE_RECTANGLE] = {
        .type = GRAPHICTYPE_RECTANGLE,
        .update = Nop,
        .draw = DrawGraphic_Rectangle
    },
    [GRAPHICTYPE_TEXTURE] = {
        .type = GRAPHICTYPE_TEXTURE,
        .update = Nop,
        .draw = DrawGraphic_Texture
    },
    [GRAPHICTYPE_TEXT] = {
        .type = GRAPHICTYPE_TEXT,
        .update = Nop,
        .draw = DrawGraphic_Text
    },
    [GRAPHICTYPE_TILE] = {
        .type = GRAPHICTYPE_TILE,
        .update = Nop,
        .draw = DrawGraphic_Tile
    },
    [GRAPHICTYPE_ASEPRITETAG] = {
        .type = GRAPHICTYPE_ASEPRITETAG,
        .update = UpdateGraphic_AsepriteTag,
        .draw = DrawGraphic_AsepriteTag
    }
};

Graphic* GraphicsAlloc(unsigned n) {
    Graphic *graphics = MemAlloc(n*sizeof(Graphic));
    Graphic *g = graphics;
    for (unsigned i = 0; i < n; ++i) {
        g->behavior = BEHAVIORS[GRAPHICTYPE_NONE];
        ++g;
    }
    return graphics;
}

void GraphicsFree(Graphic *graphics) {
    MemFree(graphics);
}

// int CompareSprites(Sprite **ap, Sprite **bp) {
//     Sprite *a = *ap, *b = *bp;
//     float diff = a->order - b->order;
//     if (diff > 0.0f)
//         return 1;
//     if (diff < 0.0f)
//         return -1;
//     diff = a->dest.y - b->dest.y;
//     if (diff > 0.0f)
//         return 1;
//     if (diff < 0.0f)
//         return -1;
// }

// void SortSpriteList(unsigned n, Sprite **list, __compar_fn_t comp) {
//     qsort(list, n, sizeof(Sprite*), comp);
// }

// void UpdateGraphicList(Graphic **list) {

// }