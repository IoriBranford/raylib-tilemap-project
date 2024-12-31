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

// following adapted from raylib-tmx
// https://github.com/RobLoach/raylib-tmx

void *LoadTMXImage(const char *fileName) {
	Texture2D *returnValue = MemAlloc(sizeof(Texture2D));
	*returnValue = LoadTexture(fileName);
	return returnValue;
}

void UnloadTMXImage(void *ptr) {
    if (ptr != NULL) {
        UnloadTexture(*((Texture2D *) ptr));
        MemFree(ptr);
    }
}

void* MemReallocTMX(void* address, size_t len) {
    return MemRealloc(address, (int)len);
}

tmx_map* LoadMap(const char *fileName) {
    tmx_alloc_func = MemReallocTMX;
    tmx_free_func = MemFree;
    tmx_img_load_func = LoadTMXImage;
	tmx_img_free_func = UnloadTMXImage;
    tmx_font_load_func = LoadTMXFont;
    tmx_font_free_func = UnloadTMXFont;

    // Load the TMX file.
    tmx_map* map = tmx_load(fileName);
    if (!map) {
        TraceLog(LOG_ERROR, "TMX: Failed to load TMX file %s", fileName);
        return NULL;
    }
    TraceLog(LOG_INFO, "TMX: Loaded %ix%i map", map->width, map->height);
    return map;
}

void UnloadMap(tmx_map* map) {
    if (map) {
        tmx_map_free(map);
        TraceLog(LOG_INFO, "TMX: Unloaded map");
    }
}