#ifndef E222BE36_5310_48C7_9586_70543D02A1F0
#define E222BE36_5310_48C7_9586_70543D02A1F0

#include <raylib-tmx.h>
#include <raylib-aseprite.h>

typedef struct Sprite Sprite;

void InitSprites(unsigned n);
void CloseSprites();

void PruneSprites();
void UpdateSprites();
void DrawSprites();

size_t NumSpritesAvailable();
Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color);

void ReleaseSprite(Sprite* sprite);

#endif /* E222BE36_5310_48C7_9586_70543D02A1F0 */
