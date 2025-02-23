#include "gfx2d.h"

#include <math.h>
#include <string.h>
#include <assert.h>

void SetSpriteTextN(Sprite *spr, const char *text, size_t n) {
    assert(spr->behavior.type == SPRITETYPE_TEXT);
    if (!n) n = 1;
    if (!spr->text.text || n > spr->text.capacity) {
        spr->text.text = MemRealloc(spr->text.text, n);
        spr->text.capacity = n;
    }
    if (text) {
        strncpy(spr->text.text, text, n);
        spr->text.text[n-1] = '\0';
    } else {
        spr->text.text[0] = '\0';
    }
}

void SetSpriteText(Sprite *spr, const char *text) {
    SetSpriteTextN(spr, text, TextLength(text)+1);
}

bool IsWordChar(int c) {
    return c != ' ' && c != '\t' && c != '\n';
}

const char* NextWordBoundary(const char *wordStart) {
    const char *p = wordStart;
    int cSize = 0;
    int c = GetCodepoint(p, &cSize);
    bool isWord = IsWordChar(c);

    while (c && isWord == IsWordChar(c)) {
        p += cSize;
        c = GetCodepoint(p, &cSize);
    };
    return p;
}

float MeasureTextRangeWidth(Font font, const char *text, ptrdiff_t size, float fontSize, float spacing)
{
    if (((font.texture.id == 0)) || !size ||
        (text == NULL) || (text[0] == '\0')) return 0; // Security check

    int byteCounter = 0;
    float textWidth = 0.0f;

    float textHeight = fontSize;
    float scaleFactor = fontSize/(float)font.baseSize;

    int letter = 0;                 // Current character
    int index = 0;                  // Index position in sprite font

    for (ptrdiff_t i = 0; i < size;)
    {
        byteCounter++;

        int codepointByteCount = 0;
        letter = GetCodepointNext(&text[i], &codepointByteCount);
        index = GetGlyphIndex(font, letter);

        if (letter != '\n')
        {
            if (font.glyphs[index].advanceX > 0) textWidth += font.glyphs[index].advanceX;
            else textWidth += (font.recs[index].width + font.glyphs[index].offsetX);

            i += codepointByteCount;
        }
        else
        {
            i = size;
        }
    }

    return textWidth*scaleFactor + (float)((byteCounter - 1)*spacing);
}

const char* WrappedLineEnd(Font font, const char *lineStart, float fontSize, float spacing, float wrapWidth) {
    float lineWidth = 0;
    
    const char *p = lineStart;
    int cSize = 0;
    int c = GetCodepoint(p, &cSize);

    while (c) {
        if (c == '\n') {
            if (p == lineStart)
                p += cSize;
            break;
        }

        const char *wordBoundary = NextWordBoundary(p);
        float wordWidth = MeasureTextRangeWidth(font, p, wordBoundary - p, fontSize, spacing);
        if (lineWidth + wordWidth > wrapWidth) {
            if (p == lineStart) {
                float charWidth = MeasureTextRangeWidth(font, p, 1, fontSize, spacing);
                do {
                    lineWidth += charWidth;
                    p += cSize;
                    c = GetCodepoint(p, &cSize);
                    charWidth = MeasureTextRangeWidth(font, p, 1, fontSize, spacing) + spacing;
                } while (c && lineWidth <= wrapWidth);
            }
            break;
        }
        
        lineWidth += wordWidth;
        p = wordBoundary;

        c = GetCodepoint(p, &cSize);
    }

    return p;
}

const char* TrimSpaceStart(const char *start, const char *end) {
    while (start < end) {
        int cSize;
        int c = GetCodepoint(start, &cSize);
        if (!c || IsWordChar(c))
            break;
        start += cSize;
    }
    return start;
}

const char* TrimSpaceEnd(const char *start, const char *end) {
    while (start < end) {
        int cSize;
        int c = GetCodepointPrevious(end, &cSize);
        if (!c || IsWordChar(c))
            break;
        end -= cSize;
    }
    return end;
}

void DrawTextRangeEx(Font font, const char *text, ptrdiff_t size, Vector2 position, float fontSize, float spacing, Color tint)
{
    if (font.texture.id == 0) font = GetFontDefault();  // Security check in case of not valid font

    float textOffsetY = 0;          // Offset between lines (on linebreak '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/font.baseSize;         // Character quad scaling factor

    for (int i = 0; i < size;)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepointNext(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        if (codepoint == '\n')
        {
            // TODO get textLineSpacing from raylib when possible
            textOffsetY += (fontSize + 2);
            textOffsetX = 0.0f;
        }
        else
        {
            if ((codepoint != ' ') && (codepoint != '\t'))
            {
                DrawTextCodepoint(font, codepoint, (Vector2){ position.x + textOffsetX, position.y + textOffsetY }, fontSize, tint);
            }

            if (font.glyphs[index].advanceX == 0) textOffsetX += ((float)font.recs[index].width*scaleFactor + spacing);
            else textOffsetX += ((float)font.glyphs[index].advanceX*scaleFactor + spacing);
        }

        i += codepointByteCount;   // Move text bytes counter to next codepoint
    }
}

void DrawTextBoxed(SpriteText *spriteText, Rectangle rec, Color tint) {
    Font font = spriteText->font;
    float fontSize = spriteText->fontSize;
    float spacing = spriteText->spacing;
    float halign = spriteText->halign;
    float valign = spriteText->valign;
    float wrapWidth = spriteText->wrap ? rec.width : INFINITY;

    int lineCount = 0;
    const char *textEnd = spriteText->text + TextLength(spriteText->text);

    const char *lineStart = spriteText->text;
    while (lineStart < textEnd) {
        const char *lineEnd = WrappedLineEnd(font, lineStart, fontSize, spacing, wrapWidth);
        ++lineCount;
        lineStart = lineEnd;
    }

    float scaleFactor = fontSize / (float)font.baseSize;     // Character rectangle scaling factor
    float lineSpacing = scaleFactor * 2; // TODO get textLineSpacing from raylib when possible
    float lineHeight = fontSize + lineSpacing;
    float totalHeight = lineHeight * lineCount;

    Vector2 linePos = (Vector2) {
        rec.x,
        rec.y + (rec.height - totalHeight + lineSpacing) * valign
    };

    lineStart = spriteText->text;

    // // DEBUG text area
    // DrawRectangleLinesEx(rec, 2, DARKGREEN);

    while (lineStart < textEnd) {
        const char *lineEnd = WrappedLineEnd(font, lineStart, fontSize, spacing, wrapWidth);

        const char *trimmedStart = lineStart;
        const char *trimmedEnd = lineEnd;
        if (lineStart > spriteText->text && halign < 1)
            trimmedStart = TrimSpaceStart(trimmedStart, trimmedEnd);
        if (lineEnd < textEnd && halign > 0)
            trimmedEnd = TrimSpaceEnd(trimmedStart, trimmedEnd);

        float lineWidth = MeasureTextRangeWidth(font, trimmedStart, trimmedEnd - trimmedStart, fontSize, spacing);
        
        linePos.x = rec.x + (rec.width - lineWidth) * halign;
        
        // // DEBUG line area
        // DrawRectangleLines(linePos.x, linePos.y - (valign*lineSpacing), lineWidth, lineHeight, GREEN);

        DrawTextRangeEx(font, trimmedStart, trimmedEnd - trimmedStart, linePos, fontSize, spacing, tint);

        linePos.y += lineHeight;
        lineStart = lineEnd;
    }
}
