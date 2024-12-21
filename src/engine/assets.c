#include <tmx.h>
#include <stdio.h>
#include <raylib.h>

size_t FontFileNameSize(const char *dir, tmx_text *text, const char *ext) {
    size_t n = TextLength(text->fontfamily);
    if (dir) n += TextLength(dir);
    if (text->bold) n += sizeof(" Bold")-1;
    if (text->italic) n += sizeof(" Italic")-1;
    if (text->underline) n += sizeof(" Underline")-1;
    if (ext) n += TextLength(ext);
    return n;
}

int BuildFontFilePath(char *s, const char *dir, tmx_text *text, const char *ext) {
    return sprintf(s, "%s%s%s%s%s%s",
        dir ? dir : "",
        text->fontfamily,
        text->bold ? " Bold" : "",
        text->italic ? " Italic" : "",
        text->underline ? " Underline" : "",
        ext ? ext : "");
}

void* LoadTMXFont(const char *dir, tmx_text *text) {
    const char *ext = ".ttf";

    size_t filenameSize = FontFileNameSize(dir, text, ext);
    char *filename = MemAlloc(filenameSize+1);

    BuildFontFilePath(filename, dir, text, ext);

    Font *font = MemAlloc(sizeof(Font));
    *font = LoadFont(filename);

    MemFree(filename);
    return font;
}

void UnloadTMXFont(void *ptr) {
    if (ptr != NULL) {
        UnloadFont(*((Font *) ptr));
        MemFree(ptr);
    }
}