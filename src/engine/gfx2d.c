#include "gfx2d.h"

#include <assert.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include <raylib-aseprite.h>

void UpdateSprite(Sprite *spr) {
    if (spr->behavior.update) spr->behavior.update(spr);
}

void DrawSprite(Sprite *spr) {
    if (spr->behavior.draw) spr->behavior.draw(spr);
}

void DrawSprite_Rectangle(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_RECTANGLE);
    DrawRectanglePro(spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

void DrawSprite_Texture(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_TEXTURE);
    DrawTexturePro(*spr->texture.texture, spr->texture.source, spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

static void DrawTextBoxed(SpriteText *spriteText, Rectangle rec, Color tint);

void DrawSprite_Text(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_TEXT);
    DrawTextBoxed(&spr->text, spr->rect, spr->color);
}

void UpdateSprite_AsepriteTag(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_ASEPRITETAG);
    UpdateAsepriteTag(&spr->asepriteTag);
}

void DrawSprite_AsepriteTag(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_ASEPRITETAG);
    DrawAsepriteTagPro(spr->asepriteTag, spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

pool_ctor(Sprite, SpritePool, NewSpritePool)

SpritePool *sprites;

#define IsUsed(g) (g->used)

static void InitEmptySprite(Sprite *spr) {
    spr->used = false;
    spr->behavior.type = SPRITETYPE_NONE;
    spr->behavior.update = spr->behavior.draw = NULL;
}

void InitSprites(unsigned n) {
    if (sprites)
        CloseSprites();
    sprites = NewSpritePool(n);
    pool_foreachall(sprites, InitEmptySprite);
}

void CloseSprites() {
    if (sprites)
        free_pool(sprites);
    sprites = NULL;
}

size_t NumSpritesActive() {
    return sprites->used;
}

size_t NumSpritesAvailable() {
    return count_free_pool_objs(sprites);
}

int CompareSprites(const void *ap, const void *bp) {
    const Sprite *a = ap, *b = bp;
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

void UpdateSprites() {
    pool_foreachused(sprites, UpdateSprite);
}

void SortSprites(int (*compare)(const void*,const void*)) {
    sort_pool_used(sprites, compare);
}

void PruneSprites() {
    prune_pool(sprites, IsUsed);
}

void DrawSprites() {
    pool_foreachused(sprites, DrawSprite);
}

Sprite* NewSprite() {
    return take_from_pool(sprites);
}

Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color) {
    Sprite *spr = NewSprite();
    if (spr) {
        spr->used = true;
        spr->behavior.type = SPRITETYPE_RECTANGLE;
        spr->behavior.update = NULL;
        spr->behavior.draw = DrawSprite_Rectangle;
        spr->rect = rect;
        spr->origin = origin;
        spr->rotationDeg = rotationDeg;
        spr->color = color;
    }
    return spr;
}

Sprite* NewTextSprite(SpriteText *text, Rectangle rect, Color color) {
    Sprite *spr = NewSprite();
    if (spr) {
        spr->used = true;
        spr->rect = rect;
        spr->origin = (Vector2){0};
        spr->rotationDeg = 0;
        spr->color = color;
        spr->behavior.type = SPRITETYPE_TEXT;
        spr->behavior.update = NULL;
        spr->behavior.draw = DrawSprite_Text;
        spr->text = *text;
    }
    return spr;
}

void ReleaseSprite(Sprite* spr) {
    spr->used = false;
}

static void DrawTextBoxed(SpriteText *spriteText, Rectangle rec, Color tint) {
    Font font = spriteText->font;
    const char *text = spriteText->text; 
    float fontSize = spriteText->fontSize;
    float spacing = spriteText->spacing;
    bool wordWrap = spriteText->wrap;

    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}
