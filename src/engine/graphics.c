#include <engine/graphics.h>
#include <func.h>
#include <stdlib.h>
#include <assert.h>
#include <util.h>

#include <raylib-tmx.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include <raylib-aseprite.h>

typedef void (*GraphicFunction)(Graphic*);

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

struct Graphic {
    union {
        struct {
            Vector2 position, size;
        };
        Rectangle rect;
    };
    Vector2 origin;
    float rotationDeg;
    Color color;
    bool used;

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
};

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
    DrawTextPro(g->text.font, g->text.text, g->position, g->origin, g->rotationDeg, g->text.fontSize, g->text.spacing, g->color);
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

pool_typedef(Graphic, GraphicPool)
pool_ctor(Graphic, GraphicPool, NewGraphicPool)

static GraphicPool *graphics;

#define IsUsed(g) (g->used)

void InitGraphics(unsigned n) {
    graphics = NewGraphicPool(n);
}

void CloseGraphics() {
    free_pool(graphics);
    graphics = NULL;
}

int CompareGraphics(const void *ap, const void *bp) {
    const Graphic *a = ap, *b = bp;
    float diff;
    // float diff = a->order - b->order;
    // if (diff > 0.0f)
    //     return 1;
    // if (diff < 0.0f)
    //     return -1;
    diff = a->position.y - b->position.y;
    if (diff > 0.0f)
        return 1;
    if (diff < 0.0f)
        return -1;
    diff = a->position.x - b->position.x;
    if (diff > 0.0f)
        return 1;
    if (diff < 0.0f)
        return -1;
    return 0;
}

void UpdateGraphics() {
    prune_pool(graphics, IsUsed);
    pool_foreachused(graphics, UpdateGraphic);
    sort_pool_used(graphics, CompareGraphics);
}

void DrawGraphics() {
    pool_foreachused(graphics, DrawGraphic);
}

Graphic* NewRectangleGraphic(Rectangle rect, Vector2 origin, float rotationDeg, Color color) {
    Graphic *g = take_from_pool(graphics);
    if (g) {
        g->behavior = BEHAVIORS[GRAPHICTYPE_RECTANGLE];
        g->rect = rect;
        g->origin = origin;
        g->rotationDeg = rotationDeg;
        g->color = color;
    }
    return g;
}