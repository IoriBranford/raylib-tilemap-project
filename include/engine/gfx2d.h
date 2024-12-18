#ifndef E222BE36_5310_48C7_9586_70543D02A1F0
#define E222BE36_5310_48C7_9586_70543D02A1F0

#include <raylib-tmx.h>
#include <raylib-aseprite.h>
#include <util.h>

typedef struct Sprite Sprite;
typedef void (*SpriteFunction)(Sprite*);

pool_typedef(Sprite, SpritePool)

typedef enum SpriteType {
    SPRITETYPE_NONE,
    SPRITETYPE_RECTANGLE,
    SPRITETYPE_TEXTURE,
    SPRITETYPE_TEXT,
    SPRITETYPE_TILE,
    SPRITETYPE_SHAPE,
    SPRITETYPE_TILELAYER,
    SPRITETYPE_ASEPRITETAG,
    SPRITETYPE_TYPES
} SpriteType;

typedef struct SpriteBehavior {
    SpriteType type;
    SpriteFunction update, draw;
} SpriteBehavior;

typedef struct SpriteText {
    Font font;
    const char *text;
    float fontSize;
    float spacing;
    float halign;   // 0 = left, 1 = right
    bool wrap;
} SpriteText;

struct Sprite {
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
    unsigned animSpeedMS;
    float animTimer;

    SpriteBehavior behavior;
    union {
        struct {
            Texture2D *texture;
            Rectangle source;
        } texture;

        SpriteText text;

        struct {
            Texture2D *texture;
            Rectangle source;
            tmx_tile *tile;
            unsigned frame;
        } tile;

        struct {
            tmx_layer *layer;
            tmx_map *map;
        } layer;

        struct {
            tmx_shape;
            float thick;
            bool closed;
        } shape;

        AsepriteTag asepriteTag;
    };
};

void InitSprites(unsigned n);
void CloseSprites();

void PruneSprites();
void UpdateSprites();
void SortSprites(int (*compare)(const void*,const void*));
void DrawSprites();

size_t NumSpritesAvailable();
Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color);
Sprite* NewTextSprite(SpriteText *text, Rectangle rect, Color color);
Sprite* NewTMXObjectSprite(tmx_object *o, tmx_tile **maptiles, Color color);
Sprite* NewTileSprite(tmx_tile *tile, Rectangle rect, float rotationDeg, Color color);
Sprite* NewTileLayerSprite(tmx_layer *layer, tmx_map *map);
void SetSpriteTile(Sprite *g, tmx_tile *tile, Vector2 flip);

void ReleaseSprite(Sprite* sprite);

#endif /* E222BE36_5310_48C7_9586_70543D02A1F0 */
