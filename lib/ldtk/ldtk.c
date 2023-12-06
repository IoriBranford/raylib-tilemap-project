#include "ldtk.h"

#include <stdlib.h>
#include <string.h>
#include <cJSON.h>

enum When cJSON_GetWhenValue(const cJSON * j) {
    enum When x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "AfterLoad")) x = WHEN_AFTER_LOAD;
        else if (!strcmp(cJSON_GetStringValue(j), "AfterSave")) x = WHEN_AFTER_SAVE;
        else if (!strcmp(cJSON_GetStringValue(j), "BeforeSave")) x = WHEN_BEFORE_SAVE;
        else if (!strcmp(cJSON_GetStringValue(j), "Manual")) x = WHEN_MANUAL;
    }
    return x;
}

cJSON * cJSON_CreateWhen(const enum When x) {
    cJSON * j = NULL;
    switch (x) {
        case WHEN_AFTER_LOAD: j = cJSON_CreateString("AfterLoad"); break;
        case WHEN_AFTER_SAVE: j = cJSON_CreateString("AfterSave"); break;
        case WHEN_BEFORE_SAVE: j = cJSON_CreateString("BeforeSave"); break;
        case WHEN_MANUAL: j = cJSON_CreateString("Manual"); break;
    }
    return j;
}

enum AllowedRefs cJSON_GetAllowedRefsValue(const cJSON * j) {
    enum AllowedRefs x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Any")) x = ALLOWEDREFS_ANY;
        else if (!strcmp(cJSON_GetStringValue(j), "OnlySame")) x = ALLOWEDREFS_ONLY_SAME;
        else if (!strcmp(cJSON_GetStringValue(j), "OnlySpecificEntity")) x = ALLOWEDREFS_ONLY_SPECIFIC_ENTITY;
        else if (!strcmp(cJSON_GetStringValue(j), "OnlyTags")) x = ALLOWEDREFS_ONLY_TAGS;
    }
    return x;
}

cJSON * cJSON_CreateAllowedRefs(const enum AllowedRefs x) {
    cJSON * j = NULL;
    switch (x) {
        case ALLOWEDREFS_ANY: j = cJSON_CreateString("Any"); break;
        case ALLOWEDREFS_ONLY_SAME: j = cJSON_CreateString("OnlySame"); break;
        case ALLOWEDREFS_ONLY_SPECIFIC_ENTITY: j = cJSON_CreateString("OnlySpecificEntity"); break;
        case ALLOWEDREFS_ONLY_TAGS: j = cJSON_CreateString("OnlyTags"); break;
    }
    return j;
}

enum EditorDisplayMode cJSON_GetEditorDisplayModeValue(const cJSON * j) {
    enum EditorDisplayMode x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "ArrayCountNoLabel")) x = EDITORDISPLAYMODE_ARRAY_COUNT_NO_LABEL;
        else if (!strcmp(cJSON_GetStringValue(j), "ArrayCountWithLabel")) x = EDITORDISPLAYMODE_ARRAY_COUNT_WITH_LABEL;
        else if (!strcmp(cJSON_GetStringValue(j), "EntityTile")) x = EDITORDISPLAYMODE_ENTITY_TILE;
        else if (!strcmp(cJSON_GetStringValue(j), "Hidden")) x = EDITORDISPLAYMODE_HIDDEN;
        else if (!strcmp(cJSON_GetStringValue(j), "LevelTile")) x = EDITORDISPLAYMODE_LEVEL_TILE;
        else if (!strcmp(cJSON_GetStringValue(j), "NameAndValue")) x = EDITORDISPLAYMODE_NAME_AND_VALUE;
        else if (!strcmp(cJSON_GetStringValue(j), "Points")) x = EDITORDISPLAYMODE_POINTS;
        else if (!strcmp(cJSON_GetStringValue(j), "PointPath")) x = EDITORDISPLAYMODE_POINT_PATH;
        else if (!strcmp(cJSON_GetStringValue(j), "PointPathLoop")) x = EDITORDISPLAYMODE_POINT_PATH_LOOP;
        else if (!strcmp(cJSON_GetStringValue(j), "PointStar")) x = EDITORDISPLAYMODE_POINT_STAR;
        else if (!strcmp(cJSON_GetStringValue(j), "RadiusGrid")) x = EDITORDISPLAYMODE_RADIUS_GRID;
        else if (!strcmp(cJSON_GetStringValue(j), "RadiusPx")) x = EDITORDISPLAYMODE_RADIUS_PX;
        else if (!strcmp(cJSON_GetStringValue(j), "RefLinkBetweenCenters")) x = EDITORDISPLAYMODE_REF_LINK_BETWEEN_CENTERS;
        else if (!strcmp(cJSON_GetStringValue(j), "RefLinkBetweenPivots")) x = EDITORDISPLAYMODE_REF_LINK_BETWEEN_PIVOTS;
        else if (!strcmp(cJSON_GetStringValue(j), "ValueOnly")) x = EDITORDISPLAYMODE_VALUE_ONLY;
    }
    return x;
}

cJSON * cJSON_CreateEditorDisplayMode(const enum EditorDisplayMode x) {
    cJSON * j = NULL;
    switch (x) {
        case EDITORDISPLAYMODE_ARRAY_COUNT_NO_LABEL: j = cJSON_CreateString("ArrayCountNoLabel"); break;
        case EDITORDISPLAYMODE_ARRAY_COUNT_WITH_LABEL: j = cJSON_CreateString("ArrayCountWithLabel"); break;
        case EDITORDISPLAYMODE_ENTITY_TILE: j = cJSON_CreateString("EntityTile"); break;
        case EDITORDISPLAYMODE_HIDDEN: j = cJSON_CreateString("Hidden"); break;
        case EDITORDISPLAYMODE_LEVEL_TILE: j = cJSON_CreateString("LevelTile"); break;
        case EDITORDISPLAYMODE_NAME_AND_VALUE: j = cJSON_CreateString("NameAndValue"); break;
        case EDITORDISPLAYMODE_POINTS: j = cJSON_CreateString("Points"); break;
        case EDITORDISPLAYMODE_POINT_PATH: j = cJSON_CreateString("PointPath"); break;
        case EDITORDISPLAYMODE_POINT_PATH_LOOP: j = cJSON_CreateString("PointPathLoop"); break;
        case EDITORDISPLAYMODE_POINT_STAR: j = cJSON_CreateString("PointStar"); break;
        case EDITORDISPLAYMODE_RADIUS_GRID: j = cJSON_CreateString("RadiusGrid"); break;
        case EDITORDISPLAYMODE_RADIUS_PX: j = cJSON_CreateString("RadiusPx"); break;
        case EDITORDISPLAYMODE_REF_LINK_BETWEEN_CENTERS: j = cJSON_CreateString("RefLinkBetweenCenters"); break;
        case EDITORDISPLAYMODE_REF_LINK_BETWEEN_PIVOTS: j = cJSON_CreateString("RefLinkBetweenPivots"); break;
        case EDITORDISPLAYMODE_VALUE_ONLY: j = cJSON_CreateString("ValueOnly"); break;
    }
    return j;
}

enum EditorDisplayPos cJSON_GetEditorDisplayPosValue(const cJSON * j) {
    enum EditorDisplayPos x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Above")) x = EDITORDISPLAYPOS_ABOVE;
        else if (!strcmp(cJSON_GetStringValue(j), "Beneath")) x = EDITORDISPLAYPOS_BENEATH;
        else if (!strcmp(cJSON_GetStringValue(j), "Center")) x = EDITORDISPLAYPOS_CENTER;
    }
    return x;
}

cJSON * cJSON_CreateEditorDisplayPos(const enum EditorDisplayPos x) {
    cJSON * j = NULL;
    switch (x) {
        case EDITORDISPLAYPOS_ABOVE: j = cJSON_CreateString("Above"); break;
        case EDITORDISPLAYPOS_BENEATH: j = cJSON_CreateString("Beneath"); break;
        case EDITORDISPLAYPOS_CENTER: j = cJSON_CreateString("Center"); break;
    }
    return j;
}

enum EditorLinkStyle cJSON_GetEditorLinkStyleValue(const cJSON * j) {
    enum EditorLinkStyle x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "ArrowsLine")) x = EDITORLINKSTYLE_ARROWS_LINE;
        else if (!strcmp(cJSON_GetStringValue(j), "CurvedArrow")) x = EDITORLINKSTYLE_CURVED_ARROW;
        else if (!strcmp(cJSON_GetStringValue(j), "DashedLine")) x = EDITORLINKSTYLE_DASHED_LINE;
        else if (!strcmp(cJSON_GetStringValue(j), "StraightArrow")) x = EDITORLINKSTYLE_STRAIGHT_ARROW;
        else if (!strcmp(cJSON_GetStringValue(j), "ZigZag")) x = EDITORLINKSTYLE_ZIG_ZAG;
    }
    return x;
}

cJSON * cJSON_CreateEditorLinkStyle(const enum EditorLinkStyle x) {
    cJSON * j = NULL;
    switch (x) {
        case EDITORLINKSTYLE_ARROWS_LINE: j = cJSON_CreateString("ArrowsLine"); break;
        case EDITORLINKSTYLE_CURVED_ARROW: j = cJSON_CreateString("CurvedArrow"); break;
        case EDITORLINKSTYLE_DASHED_LINE: j = cJSON_CreateString("DashedLine"); break;
        case EDITORLINKSTYLE_STRAIGHT_ARROW: j = cJSON_CreateString("StraightArrow"); break;
        case EDITORLINKSTYLE_ZIG_ZAG: j = cJSON_CreateString("ZigZag"); break;
    }
    return j;
}

enum TextLanguageMode cJSON_GetTextLanguageModeValue(const cJSON * j) {
    enum TextLanguageMode x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "LangC")) x = TEXTLANGUAGEMODE_LANG_C;
        else if (!strcmp(cJSON_GetStringValue(j), "LangHaxe")) x = TEXTLANGUAGEMODE_LANG_HAXE;
        else if (!strcmp(cJSON_GetStringValue(j), "LangJS")) x = TEXTLANGUAGEMODE_LANG_JS;
        else if (!strcmp(cJSON_GetStringValue(j), "LangJson")) x = TEXTLANGUAGEMODE_LANG_JSON;
        else if (!strcmp(cJSON_GetStringValue(j), "LangLog")) x = TEXTLANGUAGEMODE_LANG_LOG;
        else if (!strcmp(cJSON_GetStringValue(j), "LangLua")) x = TEXTLANGUAGEMODE_LANG_LUA;
        else if (!strcmp(cJSON_GetStringValue(j), "LangMarkdown")) x = TEXTLANGUAGEMODE_LANG_MARKDOWN;
        else if (!strcmp(cJSON_GetStringValue(j), "LangPython")) x = TEXTLANGUAGEMODE_LANG_PYTHON;
        else if (!strcmp(cJSON_GetStringValue(j), "LangRuby")) x = TEXTLANGUAGEMODE_LANG_RUBY;
        else if (!strcmp(cJSON_GetStringValue(j), "LangXml")) x = TEXTLANGUAGEMODE_LANG_XML;
    }
    return x;
}

cJSON * cJSON_CreateTextLanguageMode(const enum TextLanguageMode x) {
    cJSON * j = NULL;
    switch (x) {
        case TEXTLANGUAGEMODE_LANG_C: j = cJSON_CreateString("LangC"); break;
        case TEXTLANGUAGEMODE_LANG_HAXE: j = cJSON_CreateString("LangHaxe"); break;
        case TEXTLANGUAGEMODE_LANG_JS: j = cJSON_CreateString("LangJS"); break;
        case TEXTLANGUAGEMODE_LANG_JSON: j = cJSON_CreateString("LangJson"); break;
        case TEXTLANGUAGEMODE_LANG_LOG: j = cJSON_CreateString("LangLog"); break;
        case TEXTLANGUAGEMODE_LANG_LUA: j = cJSON_CreateString("LangLua"); break;
        case TEXTLANGUAGEMODE_LANG_MARKDOWN: j = cJSON_CreateString("LangMarkdown"); break;
        case TEXTLANGUAGEMODE_LANG_PYTHON: j = cJSON_CreateString("LangPython"); break;
        case TEXTLANGUAGEMODE_LANG_RUBY: j = cJSON_CreateString("LangRuby"); break;
        case TEXTLANGUAGEMODE_LANG_XML: j = cJSON_CreateString("LangXml"); break;
    }
    return j;
}

enum LimitBehavior cJSON_GetLimitBehaviorValue(const cJSON * j) {
    enum LimitBehavior x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "DiscardOldOnes")) x = LIMITBEHAVIOR_DISCARD_OLD_ONES;
        else if (!strcmp(cJSON_GetStringValue(j), "MoveLastOne")) x = LIMITBEHAVIOR_MOVE_LAST_ONE;
        else if (!strcmp(cJSON_GetStringValue(j), "PreventAdding")) x = LIMITBEHAVIOR_PREVENT_ADDING;
    }
    return x;
}

cJSON * cJSON_CreateLimitBehavior(const enum LimitBehavior x) {
    cJSON * j = NULL;
    switch (x) {
        case LIMITBEHAVIOR_DISCARD_OLD_ONES: j = cJSON_CreateString("DiscardOldOnes"); break;
        case LIMITBEHAVIOR_MOVE_LAST_ONE: j = cJSON_CreateString("MoveLastOne"); break;
        case LIMITBEHAVIOR_PREVENT_ADDING: j = cJSON_CreateString("PreventAdding"); break;
    }
    return j;
}

enum LimitScope cJSON_GetLimitScopeValue(const cJSON * j) {
    enum LimitScope x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "PerLayer")) x = LIMITSCOPE_PER_LAYER;
        else if (!strcmp(cJSON_GetStringValue(j), "PerLevel")) x = LIMITSCOPE_PER_LEVEL;
        else if (!strcmp(cJSON_GetStringValue(j), "PerWorld")) x = LIMITSCOPE_PER_WORLD;
    }
    return x;
}

cJSON * cJSON_CreateLimitScope(const enum LimitScope x) {
    cJSON * j = NULL;
    switch (x) {
        case LIMITSCOPE_PER_LAYER: j = cJSON_CreateString("PerLayer"); break;
        case LIMITSCOPE_PER_LEVEL: j = cJSON_CreateString("PerLevel"); break;
        case LIMITSCOPE_PER_WORLD: j = cJSON_CreateString("PerWorld"); break;
    }
    return j;
}

enum RenderMode cJSON_GetRenderModeValue(const cJSON * j) {
    enum RenderMode x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Cross")) x = RENDERMODE_CROSS;
        else if (!strcmp(cJSON_GetStringValue(j), "Ellipse")) x = RENDERMODE_ELLIPSE;
        else if (!strcmp(cJSON_GetStringValue(j), "Rectangle")) x = RENDERMODE_RECTANGLE;
        else if (!strcmp(cJSON_GetStringValue(j), "Tile")) x = RENDERMODE_TILE;
    }
    return x;
}

cJSON * cJSON_CreateRenderMode(const enum RenderMode x) {
    cJSON * j = NULL;
    switch (x) {
        case RENDERMODE_CROSS: j = cJSON_CreateString("Cross"); break;
        case RENDERMODE_ELLIPSE: j = cJSON_CreateString("Ellipse"); break;
        case RENDERMODE_RECTANGLE: j = cJSON_CreateString("Rectangle"); break;
        case RENDERMODE_TILE: j = cJSON_CreateString("Tile"); break;
    }
    return j;
}

enum TileRenderMode cJSON_GetTileRenderModeValue(const cJSON * j) {
    enum TileRenderMode x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Cover")) x = TILERENDERMODE_COVER;
        else if (!strcmp(cJSON_GetStringValue(j), "FitInside")) x = TILERENDERMODE_FIT_INSIDE;
        else if (!strcmp(cJSON_GetStringValue(j), "FullSizeCropped")) x = TILERENDERMODE_FULL_SIZE_CROPPED;
        else if (!strcmp(cJSON_GetStringValue(j), "FullSizeUncropped")) x = TILERENDERMODE_FULL_SIZE_UNCROPPED;
        else if (!strcmp(cJSON_GetStringValue(j), "NineSlice")) x = TILERENDERMODE_NINE_SLICE;
        else if (!strcmp(cJSON_GetStringValue(j), "Repeat")) x = TILERENDERMODE_REPEAT;
        else if (!strcmp(cJSON_GetStringValue(j), "Stretch")) x = TILERENDERMODE_STRETCH;
    }
    return x;
}

cJSON * cJSON_CreateTileRenderMode(const enum TileRenderMode x) {
    cJSON * j = NULL;
    switch (x) {
        case TILERENDERMODE_COVER: j = cJSON_CreateString("Cover"); break;
        case TILERENDERMODE_FIT_INSIDE: j = cJSON_CreateString("FitInside"); break;
        case TILERENDERMODE_FULL_SIZE_CROPPED: j = cJSON_CreateString("FullSizeCropped"); break;
        case TILERENDERMODE_FULL_SIZE_UNCROPPED: j = cJSON_CreateString("FullSizeUncropped"); break;
        case TILERENDERMODE_NINE_SLICE: j = cJSON_CreateString("NineSlice"); break;
        case TILERENDERMODE_REPEAT: j = cJSON_CreateString("Repeat"); break;
        case TILERENDERMODE_STRETCH: j = cJSON_CreateString("Stretch"); break;
    }
    return j;
}

enum Checker cJSON_GetCheckerValue(const cJSON * j) {
    enum Checker x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Horizontal")) x = CHECKER_HORIZONTAL;
        else if (!strcmp(cJSON_GetStringValue(j), "None")) x = CHECKER_NONE;
        else if (!strcmp(cJSON_GetStringValue(j), "Vertical")) x = CHECKER_VERTICAL;
    }
    return x;
}

cJSON * cJSON_CreateChecker(const enum Checker x) {
    cJSON * j = NULL;
    switch (x) {
        case CHECKER_HORIZONTAL: j = cJSON_CreateString("Horizontal"); break;
        case CHECKER_NONE: j = cJSON_CreateString("None"); break;
        case CHECKER_VERTICAL: j = cJSON_CreateString("Vertical"); break;
    }
    return j;
}

enum TileMode cJSON_GetTileModeValue(const cJSON * j) {
    enum TileMode x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Single")) x = TILEMODE_SINGLE;
        else if (!strcmp(cJSON_GetStringValue(j), "Stamp")) x = TILEMODE_STAMP;
    }
    return x;
}

cJSON * cJSON_CreateTileMode(const enum TileMode x) {
    cJSON * j = NULL;
    switch (x) {
        case TILEMODE_SINGLE: j = cJSON_CreateString("Single"); break;
        case TILEMODE_STAMP: j = cJSON_CreateString("Stamp"); break;
    }
    return j;
}

enum Type cJSON_GetTypeValue(const cJSON * j) {
    enum Type x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "AutoLayer")) x = TYPE_AUTO_LAYER;
        else if (!strcmp(cJSON_GetStringValue(j), "Entities")) x = TYPE_ENTITIES;
        else if (!strcmp(cJSON_GetStringValue(j), "IntGrid")) x = TYPE_INT_GRID;
        else if (!strcmp(cJSON_GetStringValue(j), "Tiles")) x = TYPE_TILES;
    }
    return x;
}

cJSON * cJSON_CreateType(const enum Type x) {
    cJSON * j = NULL;
    switch (x) {
        case TYPE_AUTO_LAYER: j = cJSON_CreateString("AutoLayer"); break;
        case TYPE_ENTITIES: j = cJSON_CreateString("Entities"); break;
        case TYPE_INT_GRID: j = cJSON_CreateString("IntGrid"); break;
        case TYPE_TILES: j = cJSON_CreateString("Tiles"); break;
    }
    return j;
}

enum EmbedAtlas cJSON_GetEmbedAtlasValue(const cJSON * j) {
    enum EmbedAtlas x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "LdtkIcons")) x = EMBEDATLAS_LDTK_ICONS;
    }
    return x;
}

cJSON * cJSON_CreateEmbedAtlas(const enum EmbedAtlas x) {
    cJSON * j = NULL;
    switch (x) {
        case EMBEDATLAS_LDTK_ICONS: j = cJSON_CreateString("LdtkIcons"); break;
    }
    return j;
}

enum Flag cJSON_GetFlagValue(const cJSON * j) {
    enum Flag x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "DiscardPreCsvIntGrid")) x = FLAG_DISCARD_PRE_CSV_INT_GRID;
        else if (!strcmp(cJSON_GetStringValue(j), "ExportPreCsvIntGridFormat")) x = FLAG_EXPORT_PRE_CSV_INT_GRID_FORMAT;
        else if (!strcmp(cJSON_GetStringValue(j), "IgnoreBackupSuggest")) x = FLAG_IGNORE_BACKUP_SUGGEST;
        else if (!strcmp(cJSON_GetStringValue(j), "MultiWorlds")) x = FLAG_MULTI_WORLDS;
        else if (!strcmp(cJSON_GetStringValue(j), "PrependIndexToLevelFileNames")) x = FLAG_PREPEND_INDEX_TO_LEVEL_FILE_NAMES;
        else if (!strcmp(cJSON_GetStringValue(j), "UseMultilinesType")) x = FLAG_USE_MULTILINES_TYPE;
    }
    return x;
}

cJSON * cJSON_CreateFlag(const enum Flag x) {
    cJSON * j = NULL;
    switch (x) {
        case FLAG_DISCARD_PRE_CSV_INT_GRID: j = cJSON_CreateString("DiscardPreCsvIntGrid"); break;
        case FLAG_EXPORT_PRE_CSV_INT_GRID_FORMAT: j = cJSON_CreateString("ExportPreCsvIntGridFormat"); break;
        case FLAG_IGNORE_BACKUP_SUGGEST: j = cJSON_CreateString("IgnoreBackupSuggest"); break;
        case FLAG_MULTI_WORLDS: j = cJSON_CreateString("MultiWorlds"); break;
        case FLAG_PREPEND_INDEX_TO_LEVEL_FILE_NAMES: j = cJSON_CreateString("PrependIndexToLevelFileNames"); break;
        case FLAG_USE_MULTILINES_TYPE: j = cJSON_CreateString("UseMultilinesType"); break;
    }
    return j;
}

enum BgPos cJSON_GetBgPosValue(const cJSON * j) {
    enum BgPos x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Contain")) x = BGPOS_CONTAIN;
        else if (!strcmp(cJSON_GetStringValue(j), "Cover")) x = BGPOS_COVER;
        else if (!strcmp(cJSON_GetStringValue(j), "CoverDirty")) x = BGPOS_COVER_DIRTY;
        else if (!strcmp(cJSON_GetStringValue(j), "Repeat")) x = BGPOS_REPEAT;
        else if (!strcmp(cJSON_GetStringValue(j), "Unscaled")) x = BGPOS_UNSCALED;
    }
    return x;
}

cJSON * cJSON_CreateBgPos(const enum BgPos x) {
    cJSON * j = NULL;
    switch (x) {
        case BGPOS_CONTAIN: j = cJSON_CreateString("Contain"); break;
        case BGPOS_COVER: j = cJSON_CreateString("Cover"); break;
        case BGPOS_COVER_DIRTY: j = cJSON_CreateString("CoverDirty"); break;
        case BGPOS_REPEAT: j = cJSON_CreateString("Repeat"); break;
        case BGPOS_UNSCALED: j = cJSON_CreateString("Unscaled"); break;
    }
    return j;
}

enum WorldLayout cJSON_GetWorldLayoutValue(const cJSON * j) {
    enum WorldLayout x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Free")) x = WORLDLAYOUT_FREE;
        else if (!strcmp(cJSON_GetStringValue(j), "GridVania")) x = WORLDLAYOUT_GRID_VANIA;
        else if (!strcmp(cJSON_GetStringValue(j), "LinearHorizontal")) x = WORLDLAYOUT_LINEAR_HORIZONTAL;
        else if (!strcmp(cJSON_GetStringValue(j), "LinearVertical")) x = WORLDLAYOUT_LINEAR_VERTICAL;
    }
    return x;
}

cJSON * cJSON_CreateWorldLayout(const enum WorldLayout x) {
    cJSON * j = NULL;
    switch (x) {
        case WORLDLAYOUT_FREE: j = cJSON_CreateString("Free"); break;
        case WORLDLAYOUT_GRID_VANIA: j = cJSON_CreateString("GridVania"); break;
        case WORLDLAYOUT_LINEAR_HORIZONTAL: j = cJSON_CreateString("LinearHorizontal"); break;
        case WORLDLAYOUT_LINEAR_VERTICAL: j = cJSON_CreateString("LinearVertical"); break;
    }
    return j;
}

enum IdentifierStyle cJSON_GetIdentifierStyleValue(const cJSON * j) {
    enum IdentifierStyle x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "Capitalize")) x = IDENTIFIERSTYLE_CAPITALIZE;
        else if (!strcmp(cJSON_GetStringValue(j), "Free")) x = IDENTIFIERSTYLE_FREE;
        else if (!strcmp(cJSON_GetStringValue(j), "Lowercase")) x = IDENTIFIERSTYLE_LOWERCASE;
        else if (!strcmp(cJSON_GetStringValue(j), "Uppercase")) x = IDENTIFIERSTYLE_UPPERCASE;
    }
    return x;
}

cJSON * cJSON_CreateIdentifierStyle(const enum IdentifierStyle x) {
    cJSON * j = NULL;
    switch (x) {
        case IDENTIFIERSTYLE_CAPITALIZE: j = cJSON_CreateString("Capitalize"); break;
        case IDENTIFIERSTYLE_FREE: j = cJSON_CreateString("Free"); break;
        case IDENTIFIERSTYLE_LOWERCASE: j = cJSON_CreateString("Lowercase"); break;
        case IDENTIFIERSTYLE_UPPERCASE: j = cJSON_CreateString("Uppercase"); break;
    }
    return j;
}

enum ImageExportMode cJSON_GetImageExportModeValue(const cJSON * j) {
    enum ImageExportMode x = 0;
    if (NULL != j) {
        if (!strcmp(cJSON_GetStringValue(j), "LayersAndLevels")) x = IMAGEEXPORTMODE_LAYERS_AND_LEVELS;
        else if (!strcmp(cJSON_GetStringValue(j), "None")) x = IMAGEEXPORTMODE_NONE;
        else if (!strcmp(cJSON_GetStringValue(j), "OneImagePerLayer")) x = IMAGEEXPORTMODE_ONE_IMAGE_PER_LAYER;
        else if (!strcmp(cJSON_GetStringValue(j), "OneImagePerLevel")) x = IMAGEEXPORTMODE_ONE_IMAGE_PER_LEVEL;
    }
    return x;
}

cJSON * cJSON_CreateImageExportMode(const enum ImageExportMode x) {
    cJSON * j = NULL;
    switch (x) {
        case IMAGEEXPORTMODE_LAYERS_AND_LEVELS: j = cJSON_CreateString("LayersAndLevels"); break;
        case IMAGEEXPORTMODE_NONE: j = cJSON_CreateString("None"); break;
        case IMAGEEXPORTMODE_ONE_IMAGE_PER_LAYER: j = cJSON_CreateString("OneImagePerLayer"); break;
        case IMAGEEXPORTMODE_ONE_IMAGE_PER_LEVEL: j = cJSON_CreateString("OneImagePerLevel"); break;
    }
    return j;
}

struct LdtkCustomCommand * cJSON_ParseLdtkCustomCommand(const char * s) {
    struct LdtkCustomCommand * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLdtkCustomCommandValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct LdtkCustomCommand * cJSON_GetLdtkCustomCommandValue(const cJSON * j) {
    struct LdtkCustomCommand * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct LdtkCustomCommand)))) {
            memset(x, 0, sizeof(struct LdtkCustomCommand));
            if (cJSON_HasObjectItem(j, "command")) {
                x->command = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "command")));
            }
            else {
                if (NULL != (x->command = cJSON_malloc(sizeof(char)))) {
                    x->command[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "when")) {
                x->when = cJSON_GetWhenValue(cJSON_GetObjectItemCaseSensitive(j, "when"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLdtkCustomCommand(const struct LdtkCustomCommand * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->command) {
                cJSON_AddStringToObject(j, "command", x->command);
            }
            else {
                cJSON_AddStringToObject(j, "command", "");
            }
            cJSON_AddItemToObject(j, "when", cJSON_CreateWhen(x->when));
        }
    }
    return j;
}

char * cJSON_PrintLdtkCustomCommand(const struct LdtkCustomCommand * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLdtkCustomCommand(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLdtkCustomCommand(struct LdtkCustomCommand * x) {
    if (NULL != x) {
        if (NULL != x->command) {
            cJSON_free(x->command);
        }
        cJSON_free(x);
    }
}

struct FieldDefinition * cJSON_ParseFieldDefinition(const char * s) {
    struct FieldDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetFieldDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct FieldDefinition * cJSON_GetFieldDefinitionValue(const cJSON * j) {
    struct FieldDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct FieldDefinition)))) {
            memset(x, 0, sizeof(struct FieldDefinition));
            if (cJSON_HasObjectItem(j, "__type")) {
                x->type = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__type")));
            }
            else {
                if (NULL != (x->type = cJSON_malloc(sizeof(char)))) {
                    x->type[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "acceptFileTypes")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "acceptFileTypes")))) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "acceptFileTypes");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->accept_file_types = x1;
                }
            }
            if (cJSON_HasObjectItem(j, "allowedRefs")) {
                x->allowed_refs = cJSON_GetAllowedRefsValue(cJSON_GetObjectItemCaseSensitive(j, "allowedRefs"));
            }
            if ((cJSON_HasObjectItem(j, "allowedRefsEntityUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "allowedRefsEntityUid")))) {
                if (NULL != (x->allowed_refs_entity_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->allowed_refs_entity_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "allowedRefsEntityUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "allowedRefTags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "allowedRefTags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->allowed_ref_tags = x1;
                }
            }
            else {
                x->allowed_ref_tags = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "allowOutOfLevelRef")) {
                x->allow_out_of_level_ref = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "allowOutOfLevelRef"));
            }
            if ((cJSON_HasObjectItem(j, "arrayMaxLength")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "arrayMaxLength")))) {
                if (NULL != (x->array_max_length = cJSON_malloc(sizeof(int64_t)))) {
                    *x->array_max_length = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "arrayMaxLength"));
                }
            }
            if ((cJSON_HasObjectItem(j, "arrayMinLength")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "arrayMinLength")))) {
                if (NULL != (x->array_min_length = cJSON_malloc(sizeof(int64_t)))) {
                    *x->array_min_length = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "arrayMinLength"));
                }
            }
            if (cJSON_HasObjectItem(j, "autoChainRef")) {
                x->auto_chain_ref = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "autoChainRef"));
            }
            if (cJSON_HasObjectItem(j, "canBeNull")) {
                x->can_be_null = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "canBeNull"));
            }
            if (cJSON_HasObjectItem(j, "defaultOverride")) {
                x->default_override = (void *)0xDEADBEEF;
            }
            if ((cJSON_HasObjectItem(j, "doc")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "doc")))) {
                x->doc = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "doc")));
            }
            if (cJSON_HasObjectItem(j, "editorAlwaysShow")) {
                x->editor_always_show = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "editorAlwaysShow"));
            }
            if (cJSON_HasObjectItem(j, "editorCutLongValues")) {
                x->editor_cut_long_values = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "editorCutLongValues"));
            }
            if ((cJSON_HasObjectItem(j, "editorDisplayColor")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "editorDisplayColor")))) {
                x->editor_display_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "editorDisplayColor")));
            }
            if (cJSON_HasObjectItem(j, "editorDisplayMode")) {
                x->editor_display_mode = cJSON_GetEditorDisplayModeValue(cJSON_GetObjectItemCaseSensitive(j, "editorDisplayMode"));
            }
            if (cJSON_HasObjectItem(j, "editorDisplayPos")) {
                x->editor_display_pos = cJSON_GetEditorDisplayPosValue(cJSON_GetObjectItemCaseSensitive(j, "editorDisplayPos"));
            }
            if (cJSON_HasObjectItem(j, "editorDisplayScale")) {
                x->editor_display_scale = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "editorDisplayScale"));
            }
            if (cJSON_HasObjectItem(j, "editorLinkStyle")) {
                x->editor_link_style = cJSON_GetEditorLinkStyleValue(cJSON_GetObjectItemCaseSensitive(j, "editorLinkStyle"));
            }
            if (cJSON_HasObjectItem(j, "editorShowInWorld")) {
                x->editor_show_in_world = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "editorShowInWorld"));
            }
            if ((cJSON_HasObjectItem(j, "editorTextPrefix")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "editorTextPrefix")))) {
                x->editor_text_prefix = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "editorTextPrefix")));
            }
            if ((cJSON_HasObjectItem(j, "editorTextSuffix")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "editorTextSuffix")))) {
                x->editor_text_suffix = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "editorTextSuffix")));
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "isArray")) {
                x->is_array = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "isArray"));
            }
            if ((cJSON_HasObjectItem(j, "max")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "max")))) {
                if (NULL != (x->max = cJSON_malloc(sizeof(double)))) {
                    *x->max = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "max"));
                }
            }
            if ((cJSON_HasObjectItem(j, "min")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "min")))) {
                if (NULL != (x->min = cJSON_malloc(sizeof(double)))) {
                    *x->min = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "min"));
                }
            }
            if ((cJSON_HasObjectItem(j, "regex")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "regex")))) {
                x->regex = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "regex")));
            }
            if (cJSON_HasObjectItem(j, "symmetricalRef")) {
                x->symmetrical_ref = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "symmetricalRef"));
            }
            if ((cJSON_HasObjectItem(j, "textLanguageMode")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "textLanguageMode")))) {
                if (NULL != (x->text_language_mode = cJSON_malloc(sizeof(enum TextLanguageMode)))) {
                    *x->text_language_mode = cJSON_GetTextLanguageModeValue(cJSON_GetObjectItemCaseSensitive(j, "textLanguageMode"));
                }
            }
            if ((cJSON_HasObjectItem(j, "tilesetUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tilesetUid")))) {
                if (NULL != (x->tileset_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tileset_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tilesetUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "type")) {
                x->field_definition_type = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "type")));
            }
            else {
                if (NULL != (x->field_definition_type = cJSON_malloc(sizeof(char)))) {
                    x->field_definition_type[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
            if (cJSON_HasObjectItem(j, "useForSmartColor")) {
                x->use_for_smart_color = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "useForSmartColor"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateFieldDefinition(const struct FieldDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->type) {
                cJSON_AddStringToObject(j, "__type", x->type);
            }
            else {
                cJSON_AddStringToObject(j, "__type", "");
            }
            if (NULL != x->accept_file_types) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "acceptFileTypes");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->accept_file_types);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->accept_file_types);
                    }
                }
            }
            else {
                cJSON_AddNullToObject(j, "acceptFileTypes");
            }
            cJSON_AddItemToObject(j, "allowedRefs", cJSON_CreateAllowedRefs(x->allowed_refs));
            if (NULL != x->allowed_refs_entity_uid) {
                cJSON_AddNumberToObject(j, "allowedRefsEntityUid", *x->allowed_refs_entity_uid);
            }
            else {
                cJSON_AddNullToObject(j, "allowedRefsEntityUid");
            }
            if (NULL != x->allowed_ref_tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "allowedRefTags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->allowed_ref_tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->allowed_ref_tags);
                    }
                }
            }
            cJSON_AddBoolToObject(j, "allowOutOfLevelRef", x->allow_out_of_level_ref);
            if (NULL != x->array_max_length) {
                cJSON_AddNumberToObject(j, "arrayMaxLength", *x->array_max_length);
            }
            else {
                cJSON_AddNullToObject(j, "arrayMaxLength");
            }
            if (NULL != x->array_min_length) {
                cJSON_AddNumberToObject(j, "arrayMinLength", *x->array_min_length);
            }
            else {
                cJSON_AddNullToObject(j, "arrayMinLength");
            }
            cJSON_AddBoolToObject(j, "autoChainRef", x->auto_chain_ref);
            cJSON_AddBoolToObject(j, "canBeNull", x->can_be_null);
            if (NULL != x->doc) {
                cJSON_AddStringToObject(j, "doc", x->doc);
            }
            else {
                cJSON_AddNullToObject(j, "doc");
            }
            cJSON_AddBoolToObject(j, "editorAlwaysShow", x->editor_always_show);
            cJSON_AddBoolToObject(j, "editorCutLongValues", x->editor_cut_long_values);
            if (NULL != x->editor_display_color) {
                cJSON_AddStringToObject(j, "editorDisplayColor", x->editor_display_color);
            }
            else {
                cJSON_AddNullToObject(j, "editorDisplayColor");
            }
            cJSON_AddItemToObject(j, "editorDisplayMode", cJSON_CreateEditorDisplayMode(x->editor_display_mode));
            cJSON_AddItemToObject(j, "editorDisplayPos", cJSON_CreateEditorDisplayPos(x->editor_display_pos));
            cJSON_AddNumberToObject(j, "editorDisplayScale", x->editor_display_scale);
            cJSON_AddItemToObject(j, "editorLinkStyle", cJSON_CreateEditorLinkStyle(x->editor_link_style));
            cJSON_AddBoolToObject(j, "editorShowInWorld", x->editor_show_in_world);
            if (NULL != x->editor_text_prefix) {
                cJSON_AddStringToObject(j, "editorTextPrefix", x->editor_text_prefix);
            }
            else {
                cJSON_AddNullToObject(j, "editorTextPrefix");
            }
            if (NULL != x->editor_text_suffix) {
                cJSON_AddStringToObject(j, "editorTextSuffix", x->editor_text_suffix);
            }
            else {
                cJSON_AddNullToObject(j, "editorTextSuffix");
            }
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            cJSON_AddBoolToObject(j, "isArray", x->is_array);
            if (NULL != x->max) {
                cJSON_AddNumberToObject(j, "max", *x->max);
            }
            else {
                cJSON_AddNullToObject(j, "max");
            }
            if (NULL != x->min) {
                cJSON_AddNumberToObject(j, "min", *x->min);
            }
            else {
                cJSON_AddNullToObject(j, "min");
            }
            if (NULL != x->regex) {
                cJSON_AddStringToObject(j, "regex", x->regex);
            }
            else {
                cJSON_AddNullToObject(j, "regex");
            }
            cJSON_AddBoolToObject(j, "symmetricalRef", x->symmetrical_ref);
            if (NULL != x->text_language_mode) {
                cJSON_AddItemToObject(j, "textLanguageMode", cJSON_CreateTextLanguageMode(*x->text_language_mode));
            }
            else {
                cJSON_AddNullToObject(j, "textLanguageMode");
            }
            if (NULL != x->tileset_uid) {
                cJSON_AddNumberToObject(j, "tilesetUid", *x->tileset_uid);
            }
            else {
                cJSON_AddNullToObject(j, "tilesetUid");
            }
            if (NULL != x->field_definition_type) {
                cJSON_AddStringToObject(j, "type", x->field_definition_type);
            }
            else {
                cJSON_AddStringToObject(j, "type", "");
            }
            cJSON_AddNumberToObject(j, "uid", x->uid);
            cJSON_AddBoolToObject(j, "useForSmartColor", x->use_for_smart_color);
        }
    }
    return j;
}

char * cJSON_PrintFieldDefinition(const struct FieldDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateFieldDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteFieldDefinition(struct FieldDefinition * x) {
    if (NULL != x) {
        if (NULL != x->type) {
            cJSON_free(x->type);
        }
        if (NULL != x->accept_file_types) {
            char * x1 = list_get_head(x->accept_file_types);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->accept_file_types);
            }
            list_release(x->accept_file_types);
        }
        if (NULL != x->allowed_refs_entity_uid) {
            cJSON_free(x->allowed_refs_entity_uid);
        }
        if (NULL != x->allowed_ref_tags) {
            char * x1 = list_get_head(x->allowed_ref_tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->allowed_ref_tags);
            }
            list_release(x->allowed_ref_tags);
        }
        if (NULL != x->array_max_length) {
            cJSON_free(x->array_max_length);
        }
        if (NULL != x->array_min_length) {
            cJSON_free(x->array_min_length);
        }
        if (NULL != x->doc) {
            cJSON_free(x->doc);
        }
        if (NULL != x->editor_display_color) {
            cJSON_free(x->editor_display_color);
        }
        if (NULL != x->editor_text_prefix) {
            cJSON_free(x->editor_text_prefix);
        }
        if (NULL != x->editor_text_suffix) {
            cJSON_free(x->editor_text_suffix);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->max) {
            cJSON_free(x->max);
        }
        if (NULL != x->min) {
            cJSON_free(x->min);
        }
        if (NULL != x->regex) {
            cJSON_free(x->regex);
        }
        if (NULL != x->text_language_mode) {
            cJSON_free(x->text_language_mode);
        }
        if (NULL != x->tileset_uid) {
            cJSON_free(x->tileset_uid);
        }
        if (NULL != x->field_definition_type) {
            cJSON_free(x->field_definition_type);
        }
        cJSON_free(x);
    }
}

struct TilesetRectangle * cJSON_ParseTilesetRectangle(const char * s) {
    struct TilesetRectangle * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetTilesetRectangleValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct TilesetRectangle * cJSON_GetTilesetRectangleValue(const cJSON * j) {
    struct TilesetRectangle * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct TilesetRectangle)))) {
            memset(x, 0, sizeof(struct TilesetRectangle));
            if (cJSON_HasObjectItem(j, "h")) {
                x->h = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "h"));
            }
            if (cJSON_HasObjectItem(j, "tilesetUid")) {
                x->tileset_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tilesetUid"));
            }
            if (cJSON_HasObjectItem(j, "w")) {
                x->w = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "w"));
            }
            if (cJSON_HasObjectItem(j, "x")) {
                x->x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "x"));
            }
            if (cJSON_HasObjectItem(j, "y")) {
                x->y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "y"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateTilesetRectangle(const struct TilesetRectangle * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "h", x->h);
            cJSON_AddNumberToObject(j, "tilesetUid", x->tileset_uid);
            cJSON_AddNumberToObject(j, "w", x->w);
            cJSON_AddNumberToObject(j, "x", x->x);
            cJSON_AddNumberToObject(j, "y", x->y);
        }
    }
    return j;
}

char * cJSON_PrintTilesetRectangle(const struct TilesetRectangle * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateTilesetRectangle(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteTilesetRectangle(struct TilesetRectangle * x) {
    if (NULL != x) {
        cJSON_free(x);
    }
}

struct EntityDefinition * cJSON_ParseEntityDefinition(const char * s) {
    struct EntityDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetEntityDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct EntityDefinition * cJSON_GetEntityDefinitionValue(const cJSON * j) {
    struct EntityDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct EntityDefinition)))) {
            memset(x, 0, sizeof(struct EntityDefinition));
            if (cJSON_HasObjectItem(j, "color")) {
                x->color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "color")));
            }
            else {
                if (NULL != (x->color = cJSON_malloc(sizeof(char)))) {
                    x->color[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "doc")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "doc")))) {
                x->doc = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "doc")));
            }
            if (cJSON_HasObjectItem(j, "exportToToc")) {
                x->export_to_toc = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "exportToToc"));
            }
            if (cJSON_HasObjectItem(j, "fieldDefs")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "fieldDefs");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetFieldDefinitionValue(e1), sizeof(struct FieldDefinition *));
                    }
                    x->field_defs = x1;
                }
            }
            else {
                x->field_defs = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "fillOpacity")) {
                x->fill_opacity = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "fillOpacity"));
            }
            if (cJSON_HasObjectItem(j, "height")) {
                x->height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "height"));
            }
            if (cJSON_HasObjectItem(j, "hollow")) {
                x->hollow = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "hollow"));
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "keepAspectRatio")) {
                x->keep_aspect_ratio = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "keepAspectRatio"));
            }
            if (cJSON_HasObjectItem(j, "limitBehavior")) {
                x->limit_behavior = cJSON_GetLimitBehaviorValue(cJSON_GetObjectItemCaseSensitive(j, "limitBehavior"));
            }
            if (cJSON_HasObjectItem(j, "limitScope")) {
                x->limit_scope = cJSON_GetLimitScopeValue(cJSON_GetObjectItemCaseSensitive(j, "limitScope"));
            }
            if (cJSON_HasObjectItem(j, "lineOpacity")) {
                x->line_opacity = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "lineOpacity"));
            }
            if (cJSON_HasObjectItem(j, "maxCount")) {
                x->max_count = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "maxCount"));
            }
            if ((cJSON_HasObjectItem(j, "maxHeight")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "maxHeight")))) {
                if (NULL != (x->max_height = cJSON_malloc(sizeof(int64_t)))) {
                    *x->max_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "maxHeight"));
                }
            }
            if ((cJSON_HasObjectItem(j, "maxWidth")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "maxWidth")))) {
                if (NULL != (x->max_width = cJSON_malloc(sizeof(int64_t)))) {
                    *x->max_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "maxWidth"));
                }
            }
            if ((cJSON_HasObjectItem(j, "minHeight")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "minHeight")))) {
                if (NULL != (x->min_height = cJSON_malloc(sizeof(int64_t)))) {
                    *x->min_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "minHeight"));
                }
            }
            if ((cJSON_HasObjectItem(j, "minWidth")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "minWidth")))) {
                if (NULL != (x->min_width = cJSON_malloc(sizeof(int64_t)))) {
                    *x->min_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "minWidth"));
                }
            }
            if (cJSON_HasObjectItem(j, "nineSliceBorders")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "nineSliceBorders");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->nine_slice_borders = x1;
                }
            }
            else {
                x->nine_slice_borders = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "pivotX")) {
                x->pivot_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pivotX"));
            }
            if (cJSON_HasObjectItem(j, "pivotY")) {
                x->pivot_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pivotY"));
            }
            if (cJSON_HasObjectItem(j, "renderMode")) {
                x->render_mode = cJSON_GetRenderModeValue(cJSON_GetObjectItemCaseSensitive(j, "renderMode"));
            }
            if (cJSON_HasObjectItem(j, "resizableX")) {
                x->resizable_x = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "resizableX"));
            }
            if (cJSON_HasObjectItem(j, "resizableY")) {
                x->resizable_y = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "resizableY"));
            }
            if (cJSON_HasObjectItem(j, "showName")) {
                x->show_name = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "showName"));
            }
            if (cJSON_HasObjectItem(j, "tags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "tags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->tags = x1;
                }
            }
            else {
                x->tags = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "tileId")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tileId")))) {
                if (NULL != (x->tile_id = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tile_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileId"));
                }
            }
            if (cJSON_HasObjectItem(j, "tileOpacity")) {
                x->tile_opacity = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileOpacity"));
            }
            if ((cJSON_HasObjectItem(j, "tileRect")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tileRect")))) {
                x->tile_rect = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "tileRect"));
            }
            if (cJSON_HasObjectItem(j, "tileRenderMode")) {
                x->tile_render_mode = cJSON_GetTileRenderModeValue(cJSON_GetObjectItemCaseSensitive(j, "tileRenderMode"));
            }
            if ((cJSON_HasObjectItem(j, "tilesetId")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tilesetId")))) {
                if (NULL != (x->tileset_id = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tileset_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tilesetId"));
                }
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
            if ((cJSON_HasObjectItem(j, "uiTileRect")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "uiTileRect")))) {
                x->ui_tile_rect = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "uiTileRect"));
            }
            if (cJSON_HasObjectItem(j, "width")) {
                x->width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "width"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateEntityDefinition(const struct EntityDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->color) {
                cJSON_AddStringToObject(j, "color", x->color);
            }
            else {
                cJSON_AddStringToObject(j, "color", "");
            }
            if (NULL != x->doc) {
                cJSON_AddStringToObject(j, "doc", x->doc);
            }
            else {
                cJSON_AddNullToObject(j, "doc");
            }
            cJSON_AddBoolToObject(j, "exportToToc", x->export_to_toc);
            if (NULL != x->field_defs) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "fieldDefs");
                if (NULL != j1) {
                    struct FieldDefinition * x1 = list_get_head(x->field_defs);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateFieldDefinition(x1));
                        x1 = list_get_next(x->field_defs);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "fillOpacity", x->fill_opacity);
            cJSON_AddNumberToObject(j, "height", x->height);
            cJSON_AddBoolToObject(j, "hollow", x->hollow);
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            cJSON_AddBoolToObject(j, "keepAspectRatio", x->keep_aspect_ratio);
            cJSON_AddItemToObject(j, "limitBehavior", cJSON_CreateLimitBehavior(x->limit_behavior));
            cJSON_AddItemToObject(j, "limitScope", cJSON_CreateLimitScope(x->limit_scope));
            cJSON_AddNumberToObject(j, "lineOpacity", x->line_opacity);
            cJSON_AddNumberToObject(j, "maxCount", x->max_count);
            if (NULL != x->max_height) {
                cJSON_AddNumberToObject(j, "maxHeight", *x->max_height);
            }
            else {
                cJSON_AddNullToObject(j, "maxHeight");
            }
            if (NULL != x->max_width) {
                cJSON_AddNumberToObject(j, "maxWidth", *x->max_width);
            }
            else {
                cJSON_AddNullToObject(j, "maxWidth");
            }
            if (NULL != x->min_height) {
                cJSON_AddNumberToObject(j, "minHeight", *x->min_height);
            }
            else {
                cJSON_AddNullToObject(j, "minHeight");
            }
            if (NULL != x->min_width) {
                cJSON_AddNumberToObject(j, "minWidth", *x->min_width);
            }
            else {
                cJSON_AddNullToObject(j, "minWidth");
            }
            if (NULL != x->nine_slice_borders) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "nineSliceBorders");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->nine_slice_borders);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->nine_slice_borders);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "pivotX", x->pivot_x);
            cJSON_AddNumberToObject(j, "pivotY", x->pivot_y);
            cJSON_AddItemToObject(j, "renderMode", cJSON_CreateRenderMode(x->render_mode));
            cJSON_AddBoolToObject(j, "resizableX", x->resizable_x);
            cJSON_AddBoolToObject(j, "resizableY", x->resizable_y);
            cJSON_AddBoolToObject(j, "showName", x->show_name);
            if (NULL != x->tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "tags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->tags);
                    }
                }
            }
            if (NULL != x->tile_id) {
                cJSON_AddNumberToObject(j, "tileId", *x->tile_id);
            }
            else {
                cJSON_AddNullToObject(j, "tileId");
            }
            cJSON_AddNumberToObject(j, "tileOpacity", x->tile_opacity);
            if (NULL != x->tile_rect) {
                cJSON_AddItemToObject(j, "tileRect", cJSON_CreateTilesetRectangle(x->tile_rect));
            }
            else {
                cJSON_AddNullToObject(j, "tileRect");
            }
            cJSON_AddItemToObject(j, "tileRenderMode", cJSON_CreateTileRenderMode(x->tile_render_mode));
            if (NULL != x->tileset_id) {
                cJSON_AddNumberToObject(j, "tilesetId", *x->tileset_id);
            }
            else {
                cJSON_AddNullToObject(j, "tilesetId");
            }
            cJSON_AddNumberToObject(j, "uid", x->uid);
            if (NULL != x->ui_tile_rect) {
                cJSON_AddItemToObject(j, "uiTileRect", cJSON_CreateTilesetRectangle(x->ui_tile_rect));
            }
            else {
                cJSON_AddNullToObject(j, "uiTileRect");
            }
            cJSON_AddNumberToObject(j, "width", x->width);
        }
    }
    return j;
}

char * cJSON_PrintEntityDefinition(const struct EntityDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateEntityDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteEntityDefinition(struct EntityDefinition * x) {
    if (NULL != x) {
        if (NULL != x->color) {
            cJSON_free(x->color);
        }
        if (NULL != x->doc) {
            cJSON_free(x->doc);
        }
        if (NULL != x->field_defs) {
            struct FieldDefinition * x1 = list_get_head(x->field_defs);
            while (NULL != x1) {
                cJSON_DeleteFieldDefinition(x1);
                x1 = list_get_next(x->field_defs);
            }
            list_release(x->field_defs);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->max_height) {
            cJSON_free(x->max_height);
        }
        if (NULL != x->max_width) {
            cJSON_free(x->max_width);
        }
        if (NULL != x->min_height) {
            cJSON_free(x->min_height);
        }
        if (NULL != x->min_width) {
            cJSON_free(x->min_width);
        }
        if (NULL != x->nine_slice_borders) {
            int64_t * x1 = list_get_head(x->nine_slice_borders);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->nine_slice_borders);
            }
            list_release(x->nine_slice_borders);
        }
        if (NULL != x->tags) {
            char * x1 = list_get_head(x->tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tags);
            }
            list_release(x->tags);
        }
        if (NULL != x->tile_id) {
            cJSON_free(x->tile_id);
        }
        if (NULL != x->tile_rect) {
            cJSON_DeleteTilesetRectangle(x->tile_rect);
        }
        if (NULL != x->tileset_id) {
            cJSON_free(x->tileset_id);
        }
        if (NULL != x->ui_tile_rect) {
            cJSON_DeleteTilesetRectangle(x->ui_tile_rect);
        }
        cJSON_free(x);
    }
}

struct EnumValueDefinition * cJSON_ParseEnumValueDefinition(const char * s) {
    struct EnumValueDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetEnumValueDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct EnumValueDefinition * cJSON_GetEnumValueDefinitionValue(const cJSON * j) {
    struct EnumValueDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct EnumValueDefinition)))) {
            memset(x, 0, sizeof(struct EnumValueDefinition));
            if ((cJSON_HasObjectItem(j, "__tileSrcRect")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "__tileSrcRect")))) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "__tileSrcRect");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->tile_src_rect = x1;
                }
            }
            if (cJSON_HasObjectItem(j, "color")) {
                x->color = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "color"));
            }
            if (cJSON_HasObjectItem(j, "id")) {
                x->id = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "id")));
            }
            else {
                if (NULL != (x->id = cJSON_malloc(sizeof(char)))) {
                    x->id[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "tileId")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tileId")))) {
                if (NULL != (x->tile_id = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tile_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileId"));
                }
            }
            if ((cJSON_HasObjectItem(j, "tileRect")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tileRect")))) {
                x->tile_rect = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "tileRect"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateEnumValueDefinition(const struct EnumValueDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->tile_src_rect) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "__tileSrcRect");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->tile_src_rect);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->tile_src_rect);
                    }
                }
            }
            else {
                cJSON_AddNullToObject(j, "__tileSrcRect");
            }
            cJSON_AddNumberToObject(j, "color", x->color);
            if (NULL != x->id) {
                cJSON_AddStringToObject(j, "id", x->id);
            }
            else {
                cJSON_AddStringToObject(j, "id", "");
            }
            if (NULL != x->tile_id) {
                cJSON_AddNumberToObject(j, "tileId", *x->tile_id);
            }
            else {
                cJSON_AddNullToObject(j, "tileId");
            }
            if (NULL != x->tile_rect) {
                cJSON_AddItemToObject(j, "tileRect", cJSON_CreateTilesetRectangle(x->tile_rect));
            }
            else {
                cJSON_AddNullToObject(j, "tileRect");
            }
        }
    }
    return j;
}

char * cJSON_PrintEnumValueDefinition(const struct EnumValueDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateEnumValueDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteEnumValueDefinition(struct EnumValueDefinition * x) {
    if (NULL != x) {
        if (NULL != x->tile_src_rect) {
            int64_t * x1 = list_get_head(x->tile_src_rect);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tile_src_rect);
            }
            list_release(x->tile_src_rect);
        }
        if (NULL != x->id) {
            cJSON_free(x->id);
        }
        if (NULL != x->tile_id) {
            cJSON_free(x->tile_id);
        }
        if (NULL != x->tile_rect) {
            cJSON_DeleteTilesetRectangle(x->tile_rect);
        }
        cJSON_free(x);
    }
}

struct EnumDefinition * cJSON_ParseEnumDefinition(const char * s) {
    struct EnumDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetEnumDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct EnumDefinition * cJSON_GetEnumDefinitionValue(const cJSON * j) {
    struct EnumDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct EnumDefinition)))) {
            memset(x, 0, sizeof(struct EnumDefinition));
            if ((cJSON_HasObjectItem(j, "externalFileChecksum")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "externalFileChecksum")))) {
                x->external_file_checksum = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "externalFileChecksum")));
            }
            if ((cJSON_HasObjectItem(j, "externalRelPath")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "externalRelPath")))) {
                x->external_rel_path = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "externalRelPath")));
            }
            if ((cJSON_HasObjectItem(j, "iconTilesetUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "iconTilesetUid")))) {
                if (NULL != (x->icon_tileset_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->icon_tileset_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "iconTilesetUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "tags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "tags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->tags = x1;
                }
            }
            else {
                x->tags = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
            if (cJSON_HasObjectItem(j, "values")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "values");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetEnumValueDefinitionValue(e1), sizeof(struct EnumValueDefinition *));
                    }
                    x->values = x1;
                }
            }
            else {
                x->values = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateEnumDefinition(const struct EnumDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->external_file_checksum) {
                cJSON_AddStringToObject(j, "externalFileChecksum", x->external_file_checksum);
            }
            else {
                cJSON_AddNullToObject(j, "externalFileChecksum");
            }
            if (NULL != x->external_rel_path) {
                cJSON_AddStringToObject(j, "externalRelPath", x->external_rel_path);
            }
            else {
                cJSON_AddNullToObject(j, "externalRelPath");
            }
            if (NULL != x->icon_tileset_uid) {
                cJSON_AddNumberToObject(j, "iconTilesetUid", *x->icon_tileset_uid);
            }
            else {
                cJSON_AddNullToObject(j, "iconTilesetUid");
            }
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            if (NULL != x->tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "tags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->tags);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "uid", x->uid);
            if (NULL != x->values) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "values");
                if (NULL != j1) {
                    struct EnumValueDefinition * x1 = list_get_head(x->values);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateEnumValueDefinition(x1));
                        x1 = list_get_next(x->values);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintEnumDefinition(const struct EnumDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateEnumDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteEnumDefinition(struct EnumDefinition * x) {
    if (NULL != x) {
        if (NULL != x->external_file_checksum) {
            cJSON_free(x->external_file_checksum);
        }
        if (NULL != x->external_rel_path) {
            cJSON_free(x->external_rel_path);
        }
        if (NULL != x->icon_tileset_uid) {
            cJSON_free(x->icon_tileset_uid);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->tags) {
            char * x1 = list_get_head(x->tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tags);
            }
            list_release(x->tags);
        }
        if (NULL != x->values) {
            struct EnumValueDefinition * x1 = list_get_head(x->values);
            while (NULL != x1) {
                cJSON_DeleteEnumValueDefinition(x1);
                x1 = list_get_next(x->values);
            }
            list_release(x->values);
        }
        cJSON_free(x);
    }
}

struct AutoLayerRuleDefinition * cJSON_ParseAutoLayerRuleDefinition(const char * s) {
    struct AutoLayerRuleDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetAutoLayerRuleDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct AutoLayerRuleDefinition * cJSON_GetAutoLayerRuleDefinitionValue(const cJSON * j) {
    struct AutoLayerRuleDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct AutoLayerRuleDefinition)))) {
            memset(x, 0, sizeof(struct AutoLayerRuleDefinition));
            if (cJSON_HasObjectItem(j, "active")) {
                x->active = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "active"));
            }
            if (cJSON_HasObjectItem(j, "alpha")) {
                x->alpha = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "alpha"));
            }
            if (cJSON_HasObjectItem(j, "breakOnMatch")) {
                x->break_on_match = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "breakOnMatch"));
            }
            if (cJSON_HasObjectItem(j, "chance")) {
                x->chance = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "chance"));
            }
            if (cJSON_HasObjectItem(j, "checker")) {
                x->checker = cJSON_GetCheckerValue(cJSON_GetObjectItemCaseSensitive(j, "checker"));
            }
            if (cJSON_HasObjectItem(j, "flipX")) {
                x->flip_x = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "flipX"));
            }
            if (cJSON_HasObjectItem(j, "flipY")) {
                x->flip_y = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "flipY"));
            }
            if ((cJSON_HasObjectItem(j, "outOfBoundsValue")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "outOfBoundsValue")))) {
                if (NULL != (x->out_of_bounds_value = cJSON_malloc(sizeof(int64_t)))) {
                    *x->out_of_bounds_value = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "outOfBoundsValue"));
                }
            }
            if (cJSON_HasObjectItem(j, "pattern")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "pattern");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->pattern = x1;
                }
            }
            else {
                x->pattern = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "perlinActive")) {
                x->perlin_active = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "perlinActive"));
            }
            if (cJSON_HasObjectItem(j, "perlinOctaves")) {
                x->perlin_octaves = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "perlinOctaves"));
            }
            if (cJSON_HasObjectItem(j, "perlinScale")) {
                x->perlin_scale = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "perlinScale"));
            }
            if (cJSON_HasObjectItem(j, "perlinSeed")) {
                x->perlin_seed = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "perlinSeed"));
            }
            if (cJSON_HasObjectItem(j, "pivotX")) {
                x->pivot_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pivotX"));
            }
            if (cJSON_HasObjectItem(j, "pivotY")) {
                x->pivot_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pivotY"));
            }
            if (cJSON_HasObjectItem(j, "size")) {
                x->size = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "size"));
            }
            if (cJSON_HasObjectItem(j, "tileIds")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "tileIds");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->tile_ids = x1;
                }
            }
            else {
                x->tile_ids = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "tileMode")) {
                x->tile_mode = cJSON_GetTileModeValue(cJSON_GetObjectItemCaseSensitive(j, "tileMode"));
            }
            if (cJSON_HasObjectItem(j, "tileRandomXMax")) {
                x->tile_random_x_max = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileRandomXMax"));
            }
            if (cJSON_HasObjectItem(j, "tileRandomXMin")) {
                x->tile_random_x_min = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileRandomXMin"));
            }
            if (cJSON_HasObjectItem(j, "tileRandomYMax")) {
                x->tile_random_y_max = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileRandomYMax"));
            }
            if (cJSON_HasObjectItem(j, "tileRandomYMin")) {
                x->tile_random_y_min = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileRandomYMin"));
            }
            if (cJSON_HasObjectItem(j, "tileXOffset")) {
                x->tile_x_offset = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileXOffset"));
            }
            if (cJSON_HasObjectItem(j, "tileYOffset")) {
                x->tile_y_offset = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileYOffset"));
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
            if (cJSON_HasObjectItem(j, "xModulo")) {
                x->x_modulo = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "xModulo"));
            }
            if (cJSON_HasObjectItem(j, "xOffset")) {
                x->x_offset = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "xOffset"));
            }
            if (cJSON_HasObjectItem(j, "yModulo")) {
                x->y_modulo = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "yModulo"));
            }
            if (cJSON_HasObjectItem(j, "yOffset")) {
                x->y_offset = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "yOffset"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateAutoLayerRuleDefinition(const struct AutoLayerRuleDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddBoolToObject(j, "active", x->active);
            cJSON_AddNumberToObject(j, "alpha", x->alpha);
            cJSON_AddBoolToObject(j, "breakOnMatch", x->break_on_match);
            cJSON_AddNumberToObject(j, "chance", x->chance);
            cJSON_AddItemToObject(j, "checker", cJSON_CreateChecker(x->checker));
            cJSON_AddBoolToObject(j, "flipX", x->flip_x);
            cJSON_AddBoolToObject(j, "flipY", x->flip_y);
            if (NULL != x->out_of_bounds_value) {
                cJSON_AddNumberToObject(j, "outOfBoundsValue", *x->out_of_bounds_value);
            }
            else {
                cJSON_AddNullToObject(j, "outOfBoundsValue");
            }
            if (NULL != x->pattern) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "pattern");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->pattern);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->pattern);
                    }
                }
            }
            cJSON_AddBoolToObject(j, "perlinActive", x->perlin_active);
            cJSON_AddNumberToObject(j, "perlinOctaves", x->perlin_octaves);
            cJSON_AddNumberToObject(j, "perlinScale", x->perlin_scale);
            cJSON_AddNumberToObject(j, "perlinSeed", x->perlin_seed);
            cJSON_AddNumberToObject(j, "pivotX", x->pivot_x);
            cJSON_AddNumberToObject(j, "pivotY", x->pivot_y);
            cJSON_AddNumberToObject(j, "size", x->size);
            if (NULL != x->tile_ids) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "tileIds");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->tile_ids);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->tile_ids);
                    }
                }
            }
            cJSON_AddItemToObject(j, "tileMode", cJSON_CreateTileMode(x->tile_mode));
            cJSON_AddNumberToObject(j, "tileRandomXMax", x->tile_random_x_max);
            cJSON_AddNumberToObject(j, "tileRandomXMin", x->tile_random_x_min);
            cJSON_AddNumberToObject(j, "tileRandomYMax", x->tile_random_y_max);
            cJSON_AddNumberToObject(j, "tileRandomYMin", x->tile_random_y_min);
            cJSON_AddNumberToObject(j, "tileXOffset", x->tile_x_offset);
            cJSON_AddNumberToObject(j, "tileYOffset", x->tile_y_offset);
            cJSON_AddNumberToObject(j, "uid", x->uid);
            cJSON_AddNumberToObject(j, "xModulo", x->x_modulo);
            cJSON_AddNumberToObject(j, "xOffset", x->x_offset);
            cJSON_AddNumberToObject(j, "yModulo", x->y_modulo);
            cJSON_AddNumberToObject(j, "yOffset", x->y_offset);
        }
    }
    return j;
}

char * cJSON_PrintAutoLayerRuleDefinition(const struct AutoLayerRuleDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateAutoLayerRuleDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteAutoLayerRuleDefinition(struct AutoLayerRuleDefinition * x) {
    if (NULL != x) {
        if (NULL != x->out_of_bounds_value) {
            cJSON_free(x->out_of_bounds_value);
        }
        if (NULL != x->pattern) {
            int64_t * x1 = list_get_head(x->pattern);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->pattern);
            }
            list_release(x->pattern);
        }
        if (NULL != x->tile_ids) {
            int64_t * x1 = list_get_head(x->tile_ids);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tile_ids);
            }
            list_release(x->tile_ids);
        }
        cJSON_free(x);
    }
}

struct AutoLayerRuleGroup * cJSON_ParseAutoLayerRuleGroup(const char * s) {
    struct AutoLayerRuleGroup * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetAutoLayerRuleGroupValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct AutoLayerRuleGroup * cJSON_GetAutoLayerRuleGroupValue(const cJSON * j) {
    struct AutoLayerRuleGroup * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct AutoLayerRuleGroup)))) {
            memset(x, 0, sizeof(struct AutoLayerRuleGroup));
            if (cJSON_HasObjectItem(j, "active")) {
                x->active = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "active"));
            }
            if ((cJSON_HasObjectItem(j, "collapsed")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "collapsed")))) {
                if (NULL != (x->collapsed = cJSON_malloc(sizeof(bool)))) {
                    *x->collapsed = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "collapsed"));
                }
            }
            if ((cJSON_HasObjectItem(j, "color")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "color")))) {
                x->color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "color")));
            }
            if ((cJSON_HasObjectItem(j, "icon")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "icon")))) {
                x->icon = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "icon"));
            }
            if (cJSON_HasObjectItem(j, "isOptional")) {
                x->is_optional = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "isOptional"));
            }
            if (cJSON_HasObjectItem(j, "name")) {
                x->name = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "name")));
            }
            else {
                if (NULL != (x->name = cJSON_malloc(sizeof(char)))) {
                    x->name[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "rules")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "rules");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetAutoLayerRuleDefinitionValue(e1), sizeof(struct AutoLayerRuleDefinition *));
                    }
                    x->rules = x1;
                }
            }
            else {
                x->rules = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
            if (cJSON_HasObjectItem(j, "usesWizard")) {
                x->uses_wizard = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "usesWizard"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateAutoLayerRuleGroup(const struct AutoLayerRuleGroup * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddBoolToObject(j, "active", x->active);
            if (NULL != x->collapsed) {
                cJSON_AddBoolToObject(j, "collapsed", *x->collapsed);
            }
            else {
                cJSON_AddNullToObject(j, "collapsed");
            }
            if (NULL != x->color) {
                cJSON_AddStringToObject(j, "color", x->color);
            }
            else {
                cJSON_AddNullToObject(j, "color");
            }
            if (NULL != x->icon) {
                cJSON_AddItemToObject(j, "icon", cJSON_CreateTilesetRectangle(x->icon));
            }
            else {
                cJSON_AddNullToObject(j, "icon");
            }
            cJSON_AddBoolToObject(j, "isOptional", x->is_optional);
            if (NULL != x->name) {
                cJSON_AddStringToObject(j, "name", x->name);
            }
            else {
                cJSON_AddStringToObject(j, "name", "");
            }
            if (NULL != x->rules) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "rules");
                if (NULL != j1) {
                    struct AutoLayerRuleDefinition * x1 = list_get_head(x->rules);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateAutoLayerRuleDefinition(x1));
                        x1 = list_get_next(x->rules);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "uid", x->uid);
            cJSON_AddBoolToObject(j, "usesWizard", x->uses_wizard);
        }
    }
    return j;
}

char * cJSON_PrintAutoLayerRuleGroup(const struct AutoLayerRuleGroup * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateAutoLayerRuleGroup(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteAutoLayerRuleGroup(struct AutoLayerRuleGroup * x) {
    if (NULL != x) {
        if (NULL != x->collapsed) {
            cJSON_free(x->collapsed);
        }
        if (NULL != x->color) {
            cJSON_free(x->color);
        }
        if (NULL != x->icon) {
            cJSON_DeleteTilesetRectangle(x->icon);
        }
        if (NULL != x->name) {
            cJSON_free(x->name);
        }
        if (NULL != x->rules) {
            struct AutoLayerRuleDefinition * x1 = list_get_head(x->rules);
            while (NULL != x1) {
                cJSON_DeleteAutoLayerRuleDefinition(x1);
                x1 = list_get_next(x->rules);
            }
            list_release(x->rules);
        }
        cJSON_free(x);
    }
}

struct IntGridValueDefinition * cJSON_ParseIntGridValueDefinition(const char * s) {
    struct IntGridValueDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetIntGridValueDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct IntGridValueDefinition * cJSON_GetIntGridValueDefinitionValue(const cJSON * j) {
    struct IntGridValueDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct IntGridValueDefinition)))) {
            memset(x, 0, sizeof(struct IntGridValueDefinition));
            if (cJSON_HasObjectItem(j, "color")) {
                x->color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "color")));
            }
            else {
                if (NULL != (x->color = cJSON_malloc(sizeof(char)))) {
                    x->color[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "groupUid")) {
                x->group_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "groupUid"));
            }
            if ((cJSON_HasObjectItem(j, "identifier")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "identifier")))) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            if ((cJSON_HasObjectItem(j, "tile")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tile")))) {
                x->tile = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "tile"));
            }
            if (cJSON_HasObjectItem(j, "value")) {
                x->value = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "value"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateIntGridValueDefinition(const struct IntGridValueDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->color) {
                cJSON_AddStringToObject(j, "color", x->color);
            }
            else {
                cJSON_AddStringToObject(j, "color", "");
            }
            cJSON_AddNumberToObject(j, "groupUid", x->group_uid);
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddNullToObject(j, "identifier");
            }
            if (NULL != x->tile) {
                cJSON_AddItemToObject(j, "tile", cJSON_CreateTilesetRectangle(x->tile));
            }
            else {
                cJSON_AddNullToObject(j, "tile");
            }
            cJSON_AddNumberToObject(j, "value", x->value);
        }
    }
    return j;
}

char * cJSON_PrintIntGridValueDefinition(const struct IntGridValueDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateIntGridValueDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteIntGridValueDefinition(struct IntGridValueDefinition * x) {
    if (NULL != x) {
        if (NULL != x->color) {
            cJSON_free(x->color);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->tile) {
            cJSON_DeleteTilesetRectangle(x->tile);
        }
        cJSON_free(x);
    }
}

struct IntGridValueGroupDefinition * cJSON_ParseIntGridValueGroupDefinition(const char * s) {
    struct IntGridValueGroupDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetIntGridValueGroupDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct IntGridValueGroupDefinition * cJSON_GetIntGridValueGroupDefinitionValue(const cJSON * j) {
    struct IntGridValueGroupDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct IntGridValueGroupDefinition)))) {
            memset(x, 0, sizeof(struct IntGridValueGroupDefinition));
            if ((cJSON_HasObjectItem(j, "color")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "color")))) {
                x->color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "color")));
            }
            if ((cJSON_HasObjectItem(j, "identifier")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "identifier")))) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateIntGridValueGroupDefinition(const struct IntGridValueGroupDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->color) {
                cJSON_AddStringToObject(j, "color", x->color);
            }
            else {
                cJSON_AddNullToObject(j, "color");
            }
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddNullToObject(j, "identifier");
            }
            cJSON_AddNumberToObject(j, "uid", x->uid);
        }
    }
    return j;
}

char * cJSON_PrintIntGridValueGroupDefinition(const struct IntGridValueGroupDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateIntGridValueGroupDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteIntGridValueGroupDefinition(struct IntGridValueGroupDefinition * x) {
    if (NULL != x) {
        if (NULL != x->color) {
            cJSON_free(x->color);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        cJSON_free(x);
    }
}

struct LayerDefinition * cJSON_ParseLayerDefinition(const char * s) {
    struct LayerDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLayerDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct LayerDefinition * cJSON_GetLayerDefinitionValue(const cJSON * j) {
    struct LayerDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct LayerDefinition)))) {
            memset(x, 0, sizeof(struct LayerDefinition));
            if (cJSON_HasObjectItem(j, "__type")) {
                x->type = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__type")));
            }
            else {
                if (NULL != (x->type = cJSON_malloc(sizeof(char)))) {
                    x->type[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "autoRuleGroups")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "autoRuleGroups");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetAutoLayerRuleGroupValue(e1), sizeof(struct AutoLayerRuleGroup *));
                    }
                    x->auto_rule_groups = x1;
                }
            }
            else {
                x->auto_rule_groups = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "autoSourceLayerDefUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "autoSourceLayerDefUid")))) {
                if (NULL != (x->auto_source_layer_def_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->auto_source_layer_def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "autoSourceLayerDefUid"));
                }
            }
            if ((cJSON_HasObjectItem(j, "autoTilesetDefUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "autoTilesetDefUid")))) {
                if (NULL != (x->auto_tileset_def_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->auto_tileset_def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "autoTilesetDefUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "canSelectWhenInactive")) {
                x->can_select_when_inactive = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "canSelectWhenInactive"));
            }
            if (cJSON_HasObjectItem(j, "displayOpacity")) {
                x->display_opacity = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "displayOpacity"));
            }
            if ((cJSON_HasObjectItem(j, "doc")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "doc")))) {
                x->doc = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "doc")));
            }
            if (cJSON_HasObjectItem(j, "excludedTags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "excludedTags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->excluded_tags = x1;
                }
            }
            else {
                x->excluded_tags = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "gridSize")) {
                x->grid_size = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "gridSize"));
            }
            if (cJSON_HasObjectItem(j, "guideGridHei")) {
                x->guide_grid_hei = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "guideGridHei"));
            }
            if (cJSON_HasObjectItem(j, "guideGridWid")) {
                x->guide_grid_wid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "guideGridWid"));
            }
            if (cJSON_HasObjectItem(j, "hideFieldsWhenInactive")) {
                x->hide_fields_when_inactive = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "hideFieldsWhenInactive"));
            }
            if (cJSON_HasObjectItem(j, "hideInList")) {
                x->hide_in_list = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "hideInList"));
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "inactiveOpacity")) {
                x->inactive_opacity = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "inactiveOpacity"));
            }
            if (cJSON_HasObjectItem(j, "intGridValues")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "intGridValues");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetIntGridValueDefinitionValue(e1), sizeof(struct IntGridValueDefinition *));
                    }
                    x->int_grid_values = x1;
                }
            }
            else {
                x->int_grid_values = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "intGridValuesGroups")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "intGridValuesGroups");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetIntGridValueGroupDefinitionValue(e1), sizeof(struct IntGridValueGroupDefinition *));
                    }
                    x->int_grid_values_groups = x1;
                }
            }
            else {
                x->int_grid_values_groups = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "parallaxFactorX")) {
                x->parallax_factor_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "parallaxFactorX"));
            }
            if (cJSON_HasObjectItem(j, "parallaxFactorY")) {
                x->parallax_factor_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "parallaxFactorY"));
            }
            if (cJSON_HasObjectItem(j, "parallaxScaling")) {
                x->parallax_scaling = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "parallaxScaling"));
            }
            if (cJSON_HasObjectItem(j, "pxOffsetX")) {
                x->px_offset_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxOffsetX"));
            }
            if (cJSON_HasObjectItem(j, "pxOffsetY")) {
                x->px_offset_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxOffsetY"));
            }
            if (cJSON_HasObjectItem(j, "renderInWorldView")) {
                x->render_in_world_view = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "renderInWorldView"));
            }
            if (cJSON_HasObjectItem(j, "requiredTags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "requiredTags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->required_tags = x1;
                }
            }
            else {
                x->required_tags = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "tilePivotX")) {
                x->tile_pivot_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tilePivotX"));
            }
            if (cJSON_HasObjectItem(j, "tilePivotY")) {
                x->tile_pivot_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tilePivotY"));
            }
            if ((cJSON_HasObjectItem(j, "tilesetDefUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tilesetDefUid")))) {
                if (NULL != (x->tileset_def_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tileset_def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tilesetDefUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "type")) {
                x->layer_definition_type = cJSON_GetTypeValue(cJSON_GetObjectItemCaseSensitive(j, "type"));
            }
            if ((cJSON_HasObjectItem(j, "uiColor")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "uiColor")))) {
                x->ui_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "uiColor")));
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLayerDefinition(const struct LayerDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->type) {
                cJSON_AddStringToObject(j, "__type", x->type);
            }
            else {
                cJSON_AddStringToObject(j, "__type", "");
            }
            if (NULL != x->auto_rule_groups) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "autoRuleGroups");
                if (NULL != j1) {
                    struct AutoLayerRuleGroup * x1 = list_get_head(x->auto_rule_groups);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateAutoLayerRuleGroup(x1));
                        x1 = list_get_next(x->auto_rule_groups);
                    }
                }
            }
            if (NULL != x->auto_source_layer_def_uid) {
                cJSON_AddNumberToObject(j, "autoSourceLayerDefUid", *x->auto_source_layer_def_uid);
            }
            else {
                cJSON_AddNullToObject(j, "autoSourceLayerDefUid");
            }
            if (NULL != x->auto_tileset_def_uid) {
                cJSON_AddNumberToObject(j, "autoTilesetDefUid", *x->auto_tileset_def_uid);
            }
            else {
                cJSON_AddNullToObject(j, "autoTilesetDefUid");
            }
            cJSON_AddBoolToObject(j, "canSelectWhenInactive", x->can_select_when_inactive);
            cJSON_AddNumberToObject(j, "displayOpacity", x->display_opacity);
            if (NULL != x->doc) {
                cJSON_AddStringToObject(j, "doc", x->doc);
            }
            else {
                cJSON_AddNullToObject(j, "doc");
            }
            if (NULL != x->excluded_tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "excludedTags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->excluded_tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->excluded_tags);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "gridSize", x->grid_size);
            cJSON_AddNumberToObject(j, "guideGridHei", x->guide_grid_hei);
            cJSON_AddNumberToObject(j, "guideGridWid", x->guide_grid_wid);
            cJSON_AddBoolToObject(j, "hideFieldsWhenInactive", x->hide_fields_when_inactive);
            cJSON_AddBoolToObject(j, "hideInList", x->hide_in_list);
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            cJSON_AddNumberToObject(j, "inactiveOpacity", x->inactive_opacity);
            if (NULL != x->int_grid_values) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "intGridValues");
                if (NULL != j1) {
                    struct IntGridValueDefinition * x1 = list_get_head(x->int_grid_values);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateIntGridValueDefinition(x1));
                        x1 = list_get_next(x->int_grid_values);
                    }
                }
            }
            if (NULL != x->int_grid_values_groups) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "intGridValuesGroups");
                if (NULL != j1) {
                    struct IntGridValueGroupDefinition * x1 = list_get_head(x->int_grid_values_groups);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateIntGridValueGroupDefinition(x1));
                        x1 = list_get_next(x->int_grid_values_groups);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "parallaxFactorX", x->parallax_factor_x);
            cJSON_AddNumberToObject(j, "parallaxFactorY", x->parallax_factor_y);
            cJSON_AddBoolToObject(j, "parallaxScaling", x->parallax_scaling);
            cJSON_AddNumberToObject(j, "pxOffsetX", x->px_offset_x);
            cJSON_AddNumberToObject(j, "pxOffsetY", x->px_offset_y);
            cJSON_AddBoolToObject(j, "renderInWorldView", x->render_in_world_view);
            if (NULL != x->required_tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "requiredTags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->required_tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->required_tags);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "tilePivotX", x->tile_pivot_x);
            cJSON_AddNumberToObject(j, "tilePivotY", x->tile_pivot_y);
            if (NULL != x->tileset_def_uid) {
                cJSON_AddNumberToObject(j, "tilesetDefUid", *x->tileset_def_uid);
            }
            else {
                cJSON_AddNullToObject(j, "tilesetDefUid");
            }
            cJSON_AddItemToObject(j, "type", cJSON_CreateType(x->layer_definition_type));
            if (NULL != x->ui_color) {
                cJSON_AddStringToObject(j, "uiColor", x->ui_color);
            }
            else {
                cJSON_AddNullToObject(j, "uiColor");
            }
            cJSON_AddNumberToObject(j, "uid", x->uid);
        }
    }
    return j;
}

char * cJSON_PrintLayerDefinition(const struct LayerDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLayerDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLayerDefinition(struct LayerDefinition * x) {
    if (NULL != x) {
        if (NULL != x->type) {
            cJSON_free(x->type);
        }
        if (NULL != x->auto_rule_groups) {
            struct AutoLayerRuleGroup * x1 = list_get_head(x->auto_rule_groups);
            while (NULL != x1) {
                cJSON_DeleteAutoLayerRuleGroup(x1);
                x1 = list_get_next(x->auto_rule_groups);
            }
            list_release(x->auto_rule_groups);
        }
        if (NULL != x->auto_source_layer_def_uid) {
            cJSON_free(x->auto_source_layer_def_uid);
        }
        if (NULL != x->auto_tileset_def_uid) {
            cJSON_free(x->auto_tileset_def_uid);
        }
        if (NULL != x->doc) {
            cJSON_free(x->doc);
        }
        if (NULL != x->excluded_tags) {
            char * x1 = list_get_head(x->excluded_tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->excluded_tags);
            }
            list_release(x->excluded_tags);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->int_grid_values) {
            struct IntGridValueDefinition * x1 = list_get_head(x->int_grid_values);
            while (NULL != x1) {
                cJSON_DeleteIntGridValueDefinition(x1);
                x1 = list_get_next(x->int_grid_values);
            }
            list_release(x->int_grid_values);
        }
        if (NULL != x->int_grid_values_groups) {
            struct IntGridValueGroupDefinition * x1 = list_get_head(x->int_grid_values_groups);
            while (NULL != x1) {
                cJSON_DeleteIntGridValueGroupDefinition(x1);
                x1 = list_get_next(x->int_grid_values_groups);
            }
            list_release(x->int_grid_values_groups);
        }
        if (NULL != x->required_tags) {
            char * x1 = list_get_head(x->required_tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->required_tags);
            }
            list_release(x->required_tags);
        }
        if (NULL != x->tileset_def_uid) {
            cJSON_free(x->tileset_def_uid);
        }
        if (NULL != x->ui_color) {
            cJSON_free(x->ui_color);
        }
        cJSON_free(x);
    }
}

struct TileCustomMetadata * cJSON_ParseTileCustomMetadata(const char * s) {
    struct TileCustomMetadata * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetTileCustomMetadataValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct TileCustomMetadata * cJSON_GetTileCustomMetadataValue(const cJSON * j) {
    struct TileCustomMetadata * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct TileCustomMetadata)))) {
            memset(x, 0, sizeof(struct TileCustomMetadata));
            if (cJSON_HasObjectItem(j, "data")) {
                x->data = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "data")));
            }
            else {
                if (NULL != (x->data = cJSON_malloc(sizeof(char)))) {
                    x->data[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "tileId")) {
                x->tile_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileId"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateTileCustomMetadata(const struct TileCustomMetadata * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->data) {
                cJSON_AddStringToObject(j, "data", x->data);
            }
            else {
                cJSON_AddStringToObject(j, "data", "");
            }
            cJSON_AddNumberToObject(j, "tileId", x->tile_id);
        }
    }
    return j;
}

char * cJSON_PrintTileCustomMetadata(const struct TileCustomMetadata * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateTileCustomMetadata(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteTileCustomMetadata(struct TileCustomMetadata * x) {
    if (NULL != x) {
        if (NULL != x->data) {
            cJSON_free(x->data);
        }
        cJSON_free(x);
    }
}

struct EnumTagValue * cJSON_ParseEnumTagValue(const char * s) {
    struct EnumTagValue * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetEnumTagValueValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct EnumTagValue * cJSON_GetEnumTagValueValue(const cJSON * j) {
    struct EnumTagValue * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct EnumTagValue)))) {
            memset(x, 0, sizeof(struct EnumTagValue));
            if (cJSON_HasObjectItem(j, "enumValueId")) {
                x->enum_value_id = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "enumValueId")));
            }
            else {
                if (NULL != (x->enum_value_id = cJSON_malloc(sizeof(char)))) {
                    x->enum_value_id[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "tileIds")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "tileIds");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->tile_ids = x1;
                }
            }
            else {
                x->tile_ids = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateEnumTagValue(const struct EnumTagValue * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->enum_value_id) {
                cJSON_AddStringToObject(j, "enumValueId", x->enum_value_id);
            }
            else {
                cJSON_AddStringToObject(j, "enumValueId", "");
            }
            if (NULL != x->tile_ids) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "tileIds");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->tile_ids);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->tile_ids);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintEnumTagValue(const struct EnumTagValue * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateEnumTagValue(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteEnumTagValue(struct EnumTagValue * x) {
    if (NULL != x) {
        if (NULL != x->enum_value_id) {
            cJSON_free(x->enum_value_id);
        }
        if (NULL != x->tile_ids) {
            int64_t * x1 = list_get_head(x->tile_ids);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tile_ids);
            }
            list_release(x->tile_ids);
        }
        cJSON_free(x);
    }
}

struct TilesetDefinition * cJSON_ParseTilesetDefinition(const char * s) {
    struct TilesetDefinition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetTilesetDefinitionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct TilesetDefinition * cJSON_GetTilesetDefinitionValue(const cJSON * j) {
    struct TilesetDefinition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct TilesetDefinition)))) {
            memset(x, 0, sizeof(struct TilesetDefinition));
            if (cJSON_HasObjectItem(j, "__cHei")) {
                x->c_hei = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__cHei"));
            }
            if (cJSON_HasObjectItem(j, "__cWid")) {
                x->c_wid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__cWid"));
            }
            if ((cJSON_HasObjectItem(j, "cachedPixelData")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "cachedPixelData")))) {
                hashtable_t * x1 = hashtable_create(64, false);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "cachedPixelData");
                    cJSON_ArrayForEach(e1, j1) {
                        hashtable_add(x1, e1->string, (void *)0xDEADBEEF, sizeof(void *));
                    }
                    x->cached_pixel_data = x1;
                }
            }
            if (cJSON_HasObjectItem(j, "customData")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "customData");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetTileCustomMetadataValue(e1), sizeof(struct TileCustomMetadata *));
                    }
                    x->custom_data = x1;
                }
            }
            else {
                x->custom_data = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "embedAtlas")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "embedAtlas")))) {
                if (NULL != (x->embed_atlas = cJSON_malloc(sizeof(enum EmbedAtlas)))) {
                    *x->embed_atlas = cJSON_GetEmbedAtlasValue(cJSON_GetObjectItemCaseSensitive(j, "embedAtlas"));
                }
            }
            if (cJSON_HasObjectItem(j, "enumTags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "enumTags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetEnumTagValueValue(e1), sizeof(struct EnumTagValue *));
                    }
                    x->enum_tags = x1;
                }
            }
            else {
                x->enum_tags = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "padding")) {
                x->padding = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "padding"));
            }
            if (cJSON_HasObjectItem(j, "pxHei")) {
                x->px_hei = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxHei"));
            }
            if (cJSON_HasObjectItem(j, "pxWid")) {
                x->px_wid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxWid"));
            }
            if ((cJSON_HasObjectItem(j, "relPath")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "relPath")))) {
                x->rel_path = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "relPath")));
            }
            if (cJSON_HasObjectItem(j, "savedSelections")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "savedSelections");
                    cJSON_ArrayForEach(e1, j1) {
                    }
                    x->saved_selections = x1;
                }
            }
            else {
                x->saved_selections = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "spacing")) {
                x->spacing = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "spacing"));
            }
            if (cJSON_HasObjectItem(j, "tags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "tags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->tags = x1;
                }
            }
            else {
                x->tags = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "tagsSourceEnumUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tagsSourceEnumUid")))) {
                if (NULL != (x->tags_source_enum_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tags_source_enum_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tagsSourceEnumUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "tileGridSize")) {
                x->tile_grid_size = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "tileGridSize"));
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateTilesetDefinition(const struct TilesetDefinition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "__cHei", x->c_hei);
            cJSON_AddNumberToObject(j, "__cWid", x->c_wid);
            if (NULL != x->cached_pixel_data) {
                cJSON * j1 = cJSON_CreateObject();
                if (NULL != j1) {
                    char **keys1 = NULL;
                    size_t count1 = hashtable_get_keys(x->cached_pixel_data, &keys1);
                    if (NULL != keys1) {
                        for (size_t index1 = 0; index1 < count1; index1++) {
                            void *x1 = hashtable_lookup(x->cached_pixel_data, keys1[index1]);
                        }
                        cJSON_free(keys1);
                    }
                    cJSON_AddItemToObject(j, "cachedPixelData", j1);
                }
            }
            else {
                cJSON_AddNullToObject(j, "cachedPixelData");
            }
            if (NULL != x->custom_data) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "customData");
                if (NULL != j1) {
                    struct TileCustomMetadata * x1 = list_get_head(x->custom_data);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateTileCustomMetadata(x1));
                        x1 = list_get_next(x->custom_data);
                    }
                }
            }
            if (NULL != x->embed_atlas) {
                cJSON_AddItemToObject(j, "embedAtlas", cJSON_CreateEmbedAtlas(*x->embed_atlas));
            }
            else {
                cJSON_AddNullToObject(j, "embedAtlas");
            }
            if (NULL != x->enum_tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "enumTags");
                if (NULL != j1) {
                    struct EnumTagValue * x1 = list_get_head(x->enum_tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateEnumTagValue(x1));
                        x1 = list_get_next(x->enum_tags);
                    }
                }
            }
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            cJSON_AddNumberToObject(j, "padding", x->padding);
            cJSON_AddNumberToObject(j, "pxHei", x->px_hei);
            cJSON_AddNumberToObject(j, "pxWid", x->px_wid);
            if (NULL != x->rel_path) {
                cJSON_AddStringToObject(j, "relPath", x->rel_path);
            }
            else {
                cJSON_AddNullToObject(j, "relPath");
            }
            if (NULL != x->saved_selections) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "savedSelections");
                if (NULL != j1) {
                    hashtable_t * x1 = list_get_head(x->saved_selections);
                    while (NULL != x1) {
                        x1 = list_get_next(x->saved_selections);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "spacing", x->spacing);
            if (NULL != x->tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "tags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->tags);
                    }
                }
            }
            if (NULL != x->tags_source_enum_uid) {
                cJSON_AddNumberToObject(j, "tagsSourceEnumUid", *x->tags_source_enum_uid);
            }
            else {
                cJSON_AddNullToObject(j, "tagsSourceEnumUid");
            }
            cJSON_AddNumberToObject(j, "tileGridSize", x->tile_grid_size);
            cJSON_AddNumberToObject(j, "uid", x->uid);
        }
    }
    return j;
}

char * cJSON_PrintTilesetDefinition(const struct TilesetDefinition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateTilesetDefinition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteTilesetDefinition(struct TilesetDefinition * x) {
    if (NULL != x) {
        if (NULL != x->cached_pixel_data) {
            char **keys1 = NULL;
            size_t count1 = hashtable_get_keys(x->cached_pixel_data, &keys1);
            if (NULL != keys1) {
                for (size_t index1 = 0; index1 < count1; index1++) {
                    void *x1 = hashtable_lookup(x->cached_pixel_data, keys1[index1]);
                    if (NULL != x1) {
                    }
                }
                cJSON_free(keys1);
            }
            hashtable_release(x->cached_pixel_data);
        }
        if (NULL != x->custom_data) {
            struct TileCustomMetadata * x1 = list_get_head(x->custom_data);
            while (NULL != x1) {
                cJSON_DeleteTileCustomMetadata(x1);
                x1 = list_get_next(x->custom_data);
            }
            list_release(x->custom_data);
        }
        if (NULL != x->embed_atlas) {
            cJSON_free(x->embed_atlas);
        }
        if (NULL != x->enum_tags) {
            struct EnumTagValue * x1 = list_get_head(x->enum_tags);
            while (NULL != x1) {
                cJSON_DeleteEnumTagValue(x1);
                x1 = list_get_next(x->enum_tags);
            }
            list_release(x->enum_tags);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->rel_path) {
            cJSON_free(x->rel_path);
        }
        if (NULL != x->saved_selections) {
            hashtable_t * x1 = list_get_head(x->saved_selections);
            while (NULL != x1) {
                x1 = list_get_next(x->saved_selections);
            }
            list_release(x->saved_selections);
        }
        if (NULL != x->tags) {
            char * x1 = list_get_head(x->tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tags);
            }
            list_release(x->tags);
        }
        if (NULL != x->tags_source_enum_uid) {
            cJSON_free(x->tags_source_enum_uid);
        }
        cJSON_free(x);
    }
}

struct Definitions * cJSON_ParseDefinitions(const char * s) {
    struct Definitions * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetDefinitionsValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct Definitions * cJSON_GetDefinitionsValue(const cJSON * j) {
    struct Definitions * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct Definitions)))) {
            memset(x, 0, sizeof(struct Definitions));
            if (cJSON_HasObjectItem(j, "entities")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "entities");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetEntityDefinitionValue(e1), sizeof(struct EntityDefinition *));
                    }
                    x->entities = x1;
                }
            }
            else {
                x->entities = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "enums")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "enums");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetEnumDefinitionValue(e1), sizeof(struct EnumDefinition *));
                    }
                    x->enums = x1;
                }
            }
            else {
                x->enums = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "externalEnums")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "externalEnums");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetEnumDefinitionValue(e1), sizeof(struct EnumDefinition *));
                    }
                    x->external_enums = x1;
                }
            }
            else {
                x->external_enums = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "layers")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "layers");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetLayerDefinitionValue(e1), sizeof(struct LayerDefinition *));
                    }
                    x->layers = x1;
                }
            }
            else {
                x->layers = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "levelFields")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "levelFields");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetFieldDefinitionValue(e1), sizeof(struct FieldDefinition *));
                    }
                    x->level_fields = x1;
                }
            }
            else {
                x->level_fields = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "tilesets")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "tilesets");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetTilesetDefinitionValue(e1), sizeof(struct TilesetDefinition *));
                    }
                    x->tilesets = x1;
                }
            }
            else {
                x->tilesets = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateDefinitions(const struct Definitions * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->entities) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "entities");
                if (NULL != j1) {
                    struct EntityDefinition * x1 = list_get_head(x->entities);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateEntityDefinition(x1));
                        x1 = list_get_next(x->entities);
                    }
                }
            }
            if (NULL != x->enums) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "enums");
                if (NULL != j1) {
                    struct EnumDefinition * x1 = list_get_head(x->enums);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateEnumDefinition(x1));
                        x1 = list_get_next(x->enums);
                    }
                }
            }
            if (NULL != x->external_enums) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "externalEnums");
                if (NULL != j1) {
                    struct EnumDefinition * x1 = list_get_head(x->external_enums);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateEnumDefinition(x1));
                        x1 = list_get_next(x->external_enums);
                    }
                }
            }
            if (NULL != x->layers) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "layers");
                if (NULL != j1) {
                    struct LayerDefinition * x1 = list_get_head(x->layers);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateLayerDefinition(x1));
                        x1 = list_get_next(x->layers);
                    }
                }
            }
            if (NULL != x->level_fields) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "levelFields");
                if (NULL != j1) {
                    struct FieldDefinition * x1 = list_get_head(x->level_fields);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateFieldDefinition(x1));
                        x1 = list_get_next(x->level_fields);
                    }
                }
            }
            if (NULL != x->tilesets) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "tilesets");
                if (NULL != j1) {
                    struct TilesetDefinition * x1 = list_get_head(x->tilesets);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateTilesetDefinition(x1));
                        x1 = list_get_next(x->tilesets);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintDefinitions(const struct Definitions * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateDefinitions(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteDefinitions(struct Definitions * x) {
    if (NULL != x) {
        if (NULL != x->entities) {
            struct EntityDefinition * x1 = list_get_head(x->entities);
            while (NULL != x1) {
                cJSON_DeleteEntityDefinition(x1);
                x1 = list_get_next(x->entities);
            }
            list_release(x->entities);
        }
        if (NULL != x->enums) {
            struct EnumDefinition * x1 = list_get_head(x->enums);
            while (NULL != x1) {
                cJSON_DeleteEnumDefinition(x1);
                x1 = list_get_next(x->enums);
            }
            list_release(x->enums);
        }
        if (NULL != x->external_enums) {
            struct EnumDefinition * x1 = list_get_head(x->external_enums);
            while (NULL != x1) {
                cJSON_DeleteEnumDefinition(x1);
                x1 = list_get_next(x->external_enums);
            }
            list_release(x->external_enums);
        }
        if (NULL != x->layers) {
            struct LayerDefinition * x1 = list_get_head(x->layers);
            while (NULL != x1) {
                cJSON_DeleteLayerDefinition(x1);
                x1 = list_get_next(x->layers);
            }
            list_release(x->layers);
        }
        if (NULL != x->level_fields) {
            struct FieldDefinition * x1 = list_get_head(x->level_fields);
            while (NULL != x1) {
                cJSON_DeleteFieldDefinition(x1);
                x1 = list_get_next(x->level_fields);
            }
            list_release(x->level_fields);
        }
        if (NULL != x->tilesets) {
            struct TilesetDefinition * x1 = list_get_head(x->tilesets);
            while (NULL != x1) {
                cJSON_DeleteTilesetDefinition(x1);
                x1 = list_get_next(x->tilesets);
            }
            list_release(x->tilesets);
        }
        cJSON_free(x);
    }
}

struct FieldInstance * cJSON_ParseFieldInstance(const char * s) {
    struct FieldInstance * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetFieldInstanceValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct FieldInstance * cJSON_GetFieldInstanceValue(const cJSON * j) {
    struct FieldInstance * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct FieldInstance)))) {
            memset(x, 0, sizeof(struct FieldInstance));
            if (cJSON_HasObjectItem(j, "__identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "__tile")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "__tile")))) {
                x->tile = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "__tile"));
            }
            if (cJSON_HasObjectItem(j, "__type")) {
                x->type = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__type")));
            }
            else {
                if (NULL != (x->type = cJSON_malloc(sizeof(char)))) {
                    x->type[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "__value")) {
                x->value = (void *)0xDEADBEEF;
            }
            else {
                x->value = (void *)0xDEADBEEF;
            }
            if (cJSON_HasObjectItem(j, "defUid")) {
                x->def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defUid"));
            }
            if (cJSON_HasObjectItem(j, "realEditorValues")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "realEditorValues");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, (void *)0xDEADBEEF, sizeof(void *));
                    }
                    x->real_editor_values = x1;
                }
            }
            else {
                x->real_editor_values = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateFieldInstance(const struct FieldInstance * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "__identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "__identifier", "");
            }
            if (NULL != x->tile) {
                cJSON_AddItemToObject(j, "__tile", cJSON_CreateTilesetRectangle(x->tile));
            }
            else {
                cJSON_AddNullToObject(j, "__tile");
            }
            if (NULL != x->type) {
                cJSON_AddStringToObject(j, "__type", x->type);
            }
            else {
                cJSON_AddStringToObject(j, "__type", "");
            }
            cJSON_AddNumberToObject(j, "defUid", x->def_uid);
            if (NULL != x->real_editor_values) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "realEditorValues");
                if (NULL != j1) {
                    void * x1 = list_get_head(x->real_editor_values);
                    while (NULL != x1) {
                        x1 = list_get_next(x->real_editor_values);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintFieldInstance(const struct FieldInstance * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateFieldInstance(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteFieldInstance(struct FieldInstance * x) {
    if (NULL != x) {
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->tile) {
            cJSON_DeleteTilesetRectangle(x->tile);
        }
        if (NULL != x->type) {
            cJSON_free(x->type);
        }
        if (NULL != x->real_editor_values) {
            void * x1 = list_get_head(x->real_editor_values);
            while (NULL != x1) {
                x1 = list_get_next(x->real_editor_values);
            }
            list_release(x->real_editor_values);
        }
        cJSON_free(x);
    }
}

struct EntityInstance * cJSON_ParseEntityInstance(const char * s) {
    struct EntityInstance * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetEntityInstanceValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct EntityInstance * cJSON_GetEntityInstanceValue(const cJSON * j) {
    struct EntityInstance * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct EntityInstance)))) {
            memset(x, 0, sizeof(struct EntityInstance));
            if (cJSON_HasObjectItem(j, "__grid")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "__grid");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->grid = x1;
                }
            }
            else {
                x->grid = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "__identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "__pivot")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "__pivot");
                    cJSON_ArrayForEach(e1, j1) {
                        double * tmp = cJSON_malloc(sizeof(double));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(double *));
                        }
                    }
                    x->pivot = x1;
                }
            }
            else {
                x->pivot = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "__smartColor")) {
                x->smart_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__smartColor")));
            }
            else {
                if (NULL != (x->smart_color = cJSON_malloc(sizeof(char)))) {
                    x->smart_color[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "__tags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "__tags");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, strdup(cJSON_GetStringValue(e1)), sizeof(char *));
                    }
                    x->tags = x1;
                }
            }
            else {
                x->tags = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "__tile")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "__tile")))) {
                x->tile = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "__tile"));
            }
            if (cJSON_HasObjectItem(j, "__worldX")) {
                x->world_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__worldX"));
            }
            if (cJSON_HasObjectItem(j, "__worldY")) {
                x->world_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__worldY"));
            }
            if (cJSON_HasObjectItem(j, "defUid")) {
                x->def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defUid"));
            }
            if (cJSON_HasObjectItem(j, "fieldInstances")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "fieldInstances");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetFieldInstanceValue(e1), sizeof(struct FieldInstance *));
                    }
                    x->field_instances = x1;
                }
            }
            else {
                x->field_instances = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "height")) {
                x->height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "height"));
            }
            if (cJSON_HasObjectItem(j, "iid")) {
                x->iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "iid")));
            }
            else {
                if (NULL != (x->iid = cJSON_malloc(sizeof(char)))) {
                    x->iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "px")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "px");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->px = x1;
                }
            }
            else {
                x->px = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "width")) {
                x->width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "width"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateEntityInstance(const struct EntityInstance * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->grid) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "__grid");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->grid);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->grid);
                    }
                }
            }
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "__identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "__identifier", "");
            }
            if (NULL != x->pivot) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "__pivot");
                if (NULL != j1) {
                    double * x1 = list_get_head(x->pivot);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->pivot);
                    }
                }
            }
            if (NULL != x->smart_color) {
                cJSON_AddStringToObject(j, "__smartColor", x->smart_color);
            }
            else {
                cJSON_AddStringToObject(j, "__smartColor", "");
            }
            if (NULL != x->tags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "__tags");
                if (NULL != j1) {
                    char * x1 = list_get_head(x->tags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateString(x1));
                        x1 = list_get_next(x->tags);
                    }
                }
            }
            if (NULL != x->tile) {
                cJSON_AddItemToObject(j, "__tile", cJSON_CreateTilesetRectangle(x->tile));
            }
            else {
                cJSON_AddNullToObject(j, "__tile");
            }
            cJSON_AddNumberToObject(j, "__worldX", x->world_x);
            cJSON_AddNumberToObject(j, "__worldY", x->world_y);
            cJSON_AddNumberToObject(j, "defUid", x->def_uid);
            if (NULL != x->field_instances) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "fieldInstances");
                if (NULL != j1) {
                    struct FieldInstance * x1 = list_get_head(x->field_instances);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateFieldInstance(x1));
                        x1 = list_get_next(x->field_instances);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "height", x->height);
            if (NULL != x->iid) {
                cJSON_AddStringToObject(j, "iid", x->iid);
            }
            else {
                cJSON_AddStringToObject(j, "iid", "");
            }
            if (NULL != x->px) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "px");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->px);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->px);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "width", x->width);
        }
    }
    return j;
}

char * cJSON_PrintEntityInstance(const struct EntityInstance * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateEntityInstance(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteEntityInstance(struct EntityInstance * x) {
    if (NULL != x) {
        if (NULL != x->grid) {
            int64_t * x1 = list_get_head(x->grid);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->grid);
            }
            list_release(x->grid);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->pivot) {
            double * x1 = list_get_head(x->pivot);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->pivot);
            }
            list_release(x->pivot);
        }
        if (NULL != x->smart_color) {
            cJSON_free(x->smart_color);
        }
        if (NULL != x->tags) {
            char * x1 = list_get_head(x->tags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->tags);
            }
            list_release(x->tags);
        }
        if (NULL != x->tile) {
            cJSON_DeleteTilesetRectangle(x->tile);
        }
        if (NULL != x->field_instances) {
            struct FieldInstance * x1 = list_get_head(x->field_instances);
            while (NULL != x1) {
                cJSON_DeleteFieldInstance(x1);
                x1 = list_get_next(x->field_instances);
            }
            list_release(x->field_instances);
        }
        if (NULL != x->iid) {
            cJSON_free(x->iid);
        }
        if (NULL != x->px) {
            int64_t * x1 = list_get_head(x->px);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->px);
            }
            list_release(x->px);
        }
        cJSON_free(x);
    }
}

struct ReferenceToAnEntityInstance * cJSON_ParseReferenceToAnEntityInstance(const char * s) {
    struct ReferenceToAnEntityInstance * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetReferenceToAnEntityInstanceValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct ReferenceToAnEntityInstance * cJSON_GetReferenceToAnEntityInstanceValue(const cJSON * j) {
    struct ReferenceToAnEntityInstance * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct ReferenceToAnEntityInstance)))) {
            memset(x, 0, sizeof(struct ReferenceToAnEntityInstance));
            if (cJSON_HasObjectItem(j, "entityIid")) {
                x->entity_iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "entityIid")));
            }
            else {
                if (NULL != (x->entity_iid = cJSON_malloc(sizeof(char)))) {
                    x->entity_iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "layerIid")) {
                x->layer_iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "layerIid")));
            }
            else {
                if (NULL != (x->layer_iid = cJSON_malloc(sizeof(char)))) {
                    x->layer_iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "levelIid")) {
                x->level_iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "levelIid")));
            }
            else {
                if (NULL != (x->level_iid = cJSON_malloc(sizeof(char)))) {
                    x->level_iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "worldIid")) {
                x->world_iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "worldIid")));
            }
            else {
                if (NULL != (x->world_iid = cJSON_malloc(sizeof(char)))) {
                    x->world_iid[0] = '\0';
                }
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateReferenceToAnEntityInstance(const struct ReferenceToAnEntityInstance * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->entity_iid) {
                cJSON_AddStringToObject(j, "entityIid", x->entity_iid);
            }
            else {
                cJSON_AddStringToObject(j, "entityIid", "");
            }
            if (NULL != x->layer_iid) {
                cJSON_AddStringToObject(j, "layerIid", x->layer_iid);
            }
            else {
                cJSON_AddStringToObject(j, "layerIid", "");
            }
            if (NULL != x->level_iid) {
                cJSON_AddStringToObject(j, "levelIid", x->level_iid);
            }
            else {
                cJSON_AddStringToObject(j, "levelIid", "");
            }
            if (NULL != x->world_iid) {
                cJSON_AddStringToObject(j, "worldIid", x->world_iid);
            }
            else {
                cJSON_AddStringToObject(j, "worldIid", "");
            }
        }
    }
    return j;
}

char * cJSON_PrintReferenceToAnEntityInstance(const struct ReferenceToAnEntityInstance * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateReferenceToAnEntityInstance(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteReferenceToAnEntityInstance(struct ReferenceToAnEntityInstance * x) {
    if (NULL != x) {
        if (NULL != x->entity_iid) {
            cJSON_free(x->entity_iid);
        }
        if (NULL != x->layer_iid) {
            cJSON_free(x->layer_iid);
        }
        if (NULL != x->level_iid) {
            cJSON_free(x->level_iid);
        }
        if (NULL != x->world_iid) {
            cJSON_free(x->world_iid);
        }
        cJSON_free(x);
    }
}

struct GridPoint * cJSON_ParseGridPoint(const char * s) {
    struct GridPoint * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetGridPointValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct GridPoint * cJSON_GetGridPointValue(const cJSON * j) {
    struct GridPoint * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct GridPoint)))) {
            memset(x, 0, sizeof(struct GridPoint));
            if (cJSON_HasObjectItem(j, "cx")) {
                x->cx = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "cx"));
            }
            if (cJSON_HasObjectItem(j, "cy")) {
                x->cy = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "cy"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateGridPoint(const struct GridPoint * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "cx", x->cx);
            cJSON_AddNumberToObject(j, "cy", x->cy);
        }
    }
    return j;
}

char * cJSON_PrintGridPoint(const struct GridPoint * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateGridPoint(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteGridPoint(struct GridPoint * x) {
    if (NULL != x) {
        cJSON_free(x);
    }
}

struct IntGridValueInstance * cJSON_ParseIntGridValueInstance(const char * s) {
    struct IntGridValueInstance * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetIntGridValueInstanceValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct IntGridValueInstance * cJSON_GetIntGridValueInstanceValue(const cJSON * j) {
    struct IntGridValueInstance * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct IntGridValueInstance)))) {
            memset(x, 0, sizeof(struct IntGridValueInstance));
            if (cJSON_HasObjectItem(j, "coordId")) {
                x->coord_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "coordId"));
            }
            if (cJSON_HasObjectItem(j, "v")) {
                x->v = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "v"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateIntGridValueInstance(const struct IntGridValueInstance * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "coordId", x->coord_id);
            cJSON_AddNumberToObject(j, "v", x->v);
        }
    }
    return j;
}

char * cJSON_PrintIntGridValueInstance(const struct IntGridValueInstance * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateIntGridValueInstance(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteIntGridValueInstance(struct IntGridValueInstance * x) {
    if (NULL != x) {
        cJSON_free(x);
    }
}

struct TileInstance * cJSON_ParseTileInstance(const char * s) {
    struct TileInstance * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetTileInstanceValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct TileInstance * cJSON_GetTileInstanceValue(const cJSON * j) {
    struct TileInstance * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct TileInstance)))) {
            memset(x, 0, sizeof(struct TileInstance));
            if (cJSON_HasObjectItem(j, "a")) {
                x->a = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "a"));
            }
            if (cJSON_HasObjectItem(j, "d")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "d");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->d = x1;
                }
            }
            else {
                x->d = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "f")) {
                x->f = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "f"));
            }
            if (cJSON_HasObjectItem(j, "px")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "px");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->px = x1;
                }
            }
            else {
                x->px = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "src")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "src");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->src = x1;
                }
            }
            else {
                x->src = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "t")) {
                x->t = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "t"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateTileInstance(const struct TileInstance * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "a", x->a);
            if (NULL != x->d) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "d");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->d);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->d);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "f", x->f);
            if (NULL != x->px) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "px");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->px);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->px);
                    }
                }
            }
            if (NULL != x->src) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "src");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->src);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->src);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "t", x->t);
        }
    }
    return j;
}

char * cJSON_PrintTileInstance(const struct TileInstance * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateTileInstance(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteTileInstance(struct TileInstance * x) {
    if (NULL != x) {
        if (NULL != x->d) {
            int64_t * x1 = list_get_head(x->d);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->d);
            }
            list_release(x->d);
        }
        if (NULL != x->px) {
            int64_t * x1 = list_get_head(x->px);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->px);
            }
            list_release(x->px);
        }
        if (NULL != x->src) {
            int64_t * x1 = list_get_head(x->src);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->src);
            }
            list_release(x->src);
        }
        cJSON_free(x);
    }
}

struct LayerInstance * cJSON_ParseLayerInstance(const char * s) {
    struct LayerInstance * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLayerInstanceValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct LayerInstance * cJSON_GetLayerInstanceValue(const cJSON * j) {
    struct LayerInstance * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct LayerInstance)))) {
            memset(x, 0, sizeof(struct LayerInstance));
            if (cJSON_HasObjectItem(j, "__cHei")) {
                x->c_hei = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__cHei"));
            }
            if (cJSON_HasObjectItem(j, "__cWid")) {
                x->c_wid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__cWid"));
            }
            if (cJSON_HasObjectItem(j, "__gridSize")) {
                x->grid_size = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__gridSize"));
            }
            if (cJSON_HasObjectItem(j, "__identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "__opacity")) {
                x->opacity = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__opacity"));
            }
            if (cJSON_HasObjectItem(j, "__pxTotalOffsetX")) {
                x->px_total_offset_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__pxTotalOffsetX"));
            }
            if (cJSON_HasObjectItem(j, "__pxTotalOffsetY")) {
                x->px_total_offset_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__pxTotalOffsetY"));
            }
            if ((cJSON_HasObjectItem(j, "__tilesetDefUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "__tilesetDefUid")))) {
                if (NULL != (x->tileset_def_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->tileset_def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "__tilesetDefUid"));
                }
            }
            if ((cJSON_HasObjectItem(j, "__tilesetRelPath")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "__tilesetRelPath")))) {
                x->tileset_rel_path = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__tilesetRelPath")));
            }
            if (cJSON_HasObjectItem(j, "__type")) {
                x->type = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__type")));
            }
            else {
                if (NULL != (x->type = cJSON_malloc(sizeof(char)))) {
                    x->type[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "autoLayerTiles")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "autoLayerTiles");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetTileInstanceValue(e1), sizeof(struct TileInstance *));
                    }
                    x->auto_layer_tiles = x1;
                }
            }
            else {
                x->auto_layer_tiles = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "entityInstances")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "entityInstances");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetEntityInstanceValue(e1), sizeof(struct EntityInstance *));
                    }
                    x->entity_instances = x1;
                }
            }
            else {
                x->entity_instances = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "gridTiles")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "gridTiles");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetTileInstanceValue(e1), sizeof(struct TileInstance *));
                    }
                    x->grid_tiles = x1;
                }
            }
            else {
                x->grid_tiles = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "iid")) {
                x->iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "iid")));
            }
            else {
                if (NULL != (x->iid = cJSON_malloc(sizeof(char)))) {
                    x->iid[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "intGrid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "intGrid")))) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "intGrid");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetIntGridValueInstanceValue(e1), sizeof(struct IntGridValueInstance *));
                    }
                    x->int_grid = x1;
                }
            }
            if (cJSON_HasObjectItem(j, "intGridCsv")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "intGridCsv");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->int_grid_csv = x1;
                }
            }
            else {
                x->int_grid_csv = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "layerDefUid")) {
                x->layer_def_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "layerDefUid"));
            }
            if (cJSON_HasObjectItem(j, "levelId")) {
                x->level_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "levelId"));
            }
            if (cJSON_HasObjectItem(j, "optionalRules")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "optionalRules");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->optional_rules = x1;
                }
            }
            else {
                x->optional_rules = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "overrideTilesetUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "overrideTilesetUid")))) {
                if (NULL != (x->override_tileset_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->override_tileset_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "overrideTilesetUid"));
                }
            }
            if (cJSON_HasObjectItem(j, "pxOffsetX")) {
                x->px_offset_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxOffsetX"));
            }
            if (cJSON_HasObjectItem(j, "pxOffsetY")) {
                x->px_offset_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxOffsetY"));
            }
            if (cJSON_HasObjectItem(j, "seed")) {
                x->seed = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "seed"));
            }
            if (cJSON_HasObjectItem(j, "visible")) {
                x->visible = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "visible"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLayerInstance(const struct LayerInstance * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "__cHei", x->c_hei);
            cJSON_AddNumberToObject(j, "__cWid", x->c_wid);
            cJSON_AddNumberToObject(j, "__gridSize", x->grid_size);
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "__identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "__identifier", "");
            }
            cJSON_AddNumberToObject(j, "__opacity", x->opacity);
            cJSON_AddNumberToObject(j, "__pxTotalOffsetX", x->px_total_offset_x);
            cJSON_AddNumberToObject(j, "__pxTotalOffsetY", x->px_total_offset_y);
            if (NULL != x->tileset_def_uid) {
                cJSON_AddNumberToObject(j, "__tilesetDefUid", *x->tileset_def_uid);
            }
            else {
                cJSON_AddNullToObject(j, "__tilesetDefUid");
            }
            if (NULL != x->tileset_rel_path) {
                cJSON_AddStringToObject(j, "__tilesetRelPath", x->tileset_rel_path);
            }
            else {
                cJSON_AddNullToObject(j, "__tilesetRelPath");
            }
            if (NULL != x->type) {
                cJSON_AddStringToObject(j, "__type", x->type);
            }
            else {
                cJSON_AddStringToObject(j, "__type", "");
            }
            if (NULL != x->auto_layer_tiles) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "autoLayerTiles");
                if (NULL != j1) {
                    struct TileInstance * x1 = list_get_head(x->auto_layer_tiles);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateTileInstance(x1));
                        x1 = list_get_next(x->auto_layer_tiles);
                    }
                }
            }
            if (NULL != x->entity_instances) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "entityInstances");
                if (NULL != j1) {
                    struct EntityInstance * x1 = list_get_head(x->entity_instances);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateEntityInstance(x1));
                        x1 = list_get_next(x->entity_instances);
                    }
                }
            }
            if (NULL != x->grid_tiles) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "gridTiles");
                if (NULL != j1) {
                    struct TileInstance * x1 = list_get_head(x->grid_tiles);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateTileInstance(x1));
                        x1 = list_get_next(x->grid_tiles);
                    }
                }
            }
            if (NULL != x->iid) {
                cJSON_AddStringToObject(j, "iid", x->iid);
            }
            else {
                cJSON_AddStringToObject(j, "iid", "");
            }
            if (NULL != x->int_grid) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "intGrid");
                if (NULL != j1) {
                    struct IntGridValueInstance * x1 = list_get_head(x->int_grid);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateIntGridValueInstance(x1));
                        x1 = list_get_next(x->int_grid);
                    }
                }
            }
            else {
                cJSON_AddNullToObject(j, "intGrid");
            }
            if (NULL != x->int_grid_csv) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "intGridCsv");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->int_grid_csv);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->int_grid_csv);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "layerDefUid", x->layer_def_uid);
            cJSON_AddNumberToObject(j, "levelId", x->level_id);
            if (NULL != x->optional_rules) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "optionalRules");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->optional_rules);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->optional_rules);
                    }
                }
            }
            if (NULL != x->override_tileset_uid) {
                cJSON_AddNumberToObject(j, "overrideTilesetUid", *x->override_tileset_uid);
            }
            else {
                cJSON_AddNullToObject(j, "overrideTilesetUid");
            }
            cJSON_AddNumberToObject(j, "pxOffsetX", x->px_offset_x);
            cJSON_AddNumberToObject(j, "pxOffsetY", x->px_offset_y);
            cJSON_AddNumberToObject(j, "seed", x->seed);
            cJSON_AddBoolToObject(j, "visible", x->visible);
        }
    }
    return j;
}

char * cJSON_PrintLayerInstance(const struct LayerInstance * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLayerInstance(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLayerInstance(struct LayerInstance * x) {
    if (NULL != x) {
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->tileset_def_uid) {
            cJSON_free(x->tileset_def_uid);
        }
        if (NULL != x->tileset_rel_path) {
            cJSON_free(x->tileset_rel_path);
        }
        if (NULL != x->type) {
            cJSON_free(x->type);
        }
        if (NULL != x->auto_layer_tiles) {
            struct TileInstance * x1 = list_get_head(x->auto_layer_tiles);
            while (NULL != x1) {
                cJSON_DeleteTileInstance(x1);
                x1 = list_get_next(x->auto_layer_tiles);
            }
            list_release(x->auto_layer_tiles);
        }
        if (NULL != x->entity_instances) {
            struct EntityInstance * x1 = list_get_head(x->entity_instances);
            while (NULL != x1) {
                cJSON_DeleteEntityInstance(x1);
                x1 = list_get_next(x->entity_instances);
            }
            list_release(x->entity_instances);
        }
        if (NULL != x->grid_tiles) {
            struct TileInstance * x1 = list_get_head(x->grid_tiles);
            while (NULL != x1) {
                cJSON_DeleteTileInstance(x1);
                x1 = list_get_next(x->grid_tiles);
            }
            list_release(x->grid_tiles);
        }
        if (NULL != x->iid) {
            cJSON_free(x->iid);
        }
        if (NULL != x->int_grid) {
            struct IntGridValueInstance * x1 = list_get_head(x->int_grid);
            while (NULL != x1) {
                cJSON_DeleteIntGridValueInstance(x1);
                x1 = list_get_next(x->int_grid);
            }
            list_release(x->int_grid);
        }
        if (NULL != x->int_grid_csv) {
            int64_t * x1 = list_get_head(x->int_grid_csv);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->int_grid_csv);
            }
            list_release(x->int_grid_csv);
        }
        if (NULL != x->optional_rules) {
            int64_t * x1 = list_get_head(x->optional_rules);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->optional_rules);
            }
            list_release(x->optional_rules);
        }
        if (NULL != x->override_tileset_uid) {
            cJSON_free(x->override_tileset_uid);
        }
        cJSON_free(x);
    }
}

struct LevelBackgroundPosition * cJSON_ParseLevelBackgroundPosition(const char * s) {
    struct LevelBackgroundPosition * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLevelBackgroundPositionValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct LevelBackgroundPosition * cJSON_GetLevelBackgroundPositionValue(const cJSON * j) {
    struct LevelBackgroundPosition * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct LevelBackgroundPosition)))) {
            memset(x, 0, sizeof(struct LevelBackgroundPosition));
            if (cJSON_HasObjectItem(j, "cropRect")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "cropRect");
                    cJSON_ArrayForEach(e1, j1) {
                        double * tmp = cJSON_malloc(sizeof(double));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(double *));
                        }
                    }
                    x->crop_rect = x1;
                }
            }
            else {
                x->crop_rect = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "scale")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "scale");
                    cJSON_ArrayForEach(e1, j1) {
                        double * tmp = cJSON_malloc(sizeof(double));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(double *));
                        }
                    }
                    x->scale = x1;
                }
            }
            else {
                x->scale = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "topLeftPx")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "topLeftPx");
                    cJSON_ArrayForEach(e1, j1) {
                        int64_t * tmp = cJSON_malloc(sizeof(int64_t));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetNumberValue(e1);
                            list_add_tail(x1, tmp, sizeof(int64_t *));
                        }
                    }
                    x->top_left_px = x1;
                }
            }
            else {
                x->top_left_px = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLevelBackgroundPosition(const struct LevelBackgroundPosition * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->crop_rect) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "cropRect");
                if (NULL != j1) {
                    double * x1 = list_get_head(x->crop_rect);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->crop_rect);
                    }
                }
            }
            if (NULL != x->scale) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "scale");
                if (NULL != j1) {
                    double * x1 = list_get_head(x->scale);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->scale);
                    }
                }
            }
            if (NULL != x->top_left_px) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "topLeftPx");
                if (NULL != j1) {
                    int64_t * x1 = list_get_head(x->top_left_px);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNumber(*x1));
                        x1 = list_get_next(x->top_left_px);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintLevelBackgroundPosition(const struct LevelBackgroundPosition * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLevelBackgroundPosition(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLevelBackgroundPosition(struct LevelBackgroundPosition * x) {
    if (NULL != x) {
        if (NULL != x->crop_rect) {
            double * x1 = list_get_head(x->crop_rect);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->crop_rect);
            }
            list_release(x->crop_rect);
        }
        if (NULL != x->scale) {
            double * x1 = list_get_head(x->scale);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->scale);
            }
            list_release(x->scale);
        }
        if (NULL != x->top_left_px) {
            int64_t * x1 = list_get_head(x->top_left_px);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->top_left_px);
            }
            list_release(x->top_left_px);
        }
        cJSON_free(x);
    }
}

struct NeighbourLevel * cJSON_ParseNeighbourLevel(const char * s) {
    struct NeighbourLevel * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetNeighbourLevelValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct NeighbourLevel * cJSON_GetNeighbourLevelValue(const cJSON * j) {
    struct NeighbourLevel * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct NeighbourLevel)))) {
            memset(x, 0, sizeof(struct NeighbourLevel));
            if (cJSON_HasObjectItem(j, "dir")) {
                x->dir = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "dir")));
            }
            else {
                if (NULL != (x->dir = cJSON_malloc(sizeof(char)))) {
                    x->dir[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "levelIid")) {
                x->level_iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "levelIid")));
            }
            else {
                if (NULL != (x->level_iid = cJSON_malloc(sizeof(char)))) {
                    x->level_iid[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "levelUid")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "levelUid")))) {
                if (NULL != (x->level_uid = cJSON_malloc(sizeof(int64_t)))) {
                    *x->level_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "levelUid"));
                }
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateNeighbourLevel(const struct NeighbourLevel * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->dir) {
                cJSON_AddStringToObject(j, "dir", x->dir);
            }
            else {
                cJSON_AddStringToObject(j, "dir", "");
            }
            if (NULL != x->level_iid) {
                cJSON_AddStringToObject(j, "levelIid", x->level_iid);
            }
            else {
                cJSON_AddStringToObject(j, "levelIid", "");
            }
            if (NULL != x->level_uid) {
                cJSON_AddNumberToObject(j, "levelUid", *x->level_uid);
            }
            else {
                cJSON_AddNullToObject(j, "levelUid");
            }
        }
    }
    return j;
}

char * cJSON_PrintNeighbourLevel(const struct NeighbourLevel * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateNeighbourLevel(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteNeighbourLevel(struct NeighbourLevel * x) {
    if (NULL != x) {
        if (NULL != x->dir) {
            cJSON_free(x->dir);
        }
        if (NULL != x->level_iid) {
            cJSON_free(x->level_iid);
        }
        if (NULL != x->level_uid) {
            cJSON_free(x->level_uid);
        }
        cJSON_free(x);
    }
}

struct Level * cJSON_ParseLevel(const char * s) {
    struct Level * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLevelValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct Level * cJSON_GetLevelValue(const cJSON * j) {
    struct Level * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct Level)))) {
            memset(x, 0, sizeof(struct Level));
            if (cJSON_HasObjectItem(j, "__bgColor")) {
                x->bg_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__bgColor")));
            }
            else {
                if (NULL != (x->bg_color = cJSON_malloc(sizeof(char)))) {
                    x->bg_color[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "__bgPos")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "__bgPos")))) {
                x->bg_pos = cJSON_GetLevelBackgroundPositionValue(cJSON_GetObjectItemCaseSensitive(j, "__bgPos"));
            }
            if (cJSON_HasObjectItem(j, "__neighbours")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "__neighbours");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetNeighbourLevelValue(e1), sizeof(struct NeighbourLevel *));
                    }
                    x->neighbours = x1;
                }
            }
            else {
                x->neighbours = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "__smartColor")) {
                x->smart_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "__smartColor")));
            }
            else {
                if (NULL != (x->smart_color = cJSON_malloc(sizeof(char)))) {
                    x->smart_color[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "bgColor")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "bgColor")))) {
                x->level_bg_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "bgColor")));
            }
            if (cJSON_HasObjectItem(j, "bgPivotX")) {
                x->bg_pivot_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "bgPivotX"));
            }
            if (cJSON_HasObjectItem(j, "bgPivotY")) {
                x->bg_pivot_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "bgPivotY"));
            }
            if ((cJSON_HasObjectItem(j, "bgPos")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "bgPos")))) {
                if (NULL != (x->level_bg_pos = cJSON_malloc(sizeof(enum BgPos)))) {
                    *x->level_bg_pos = cJSON_GetBgPosValue(cJSON_GetObjectItemCaseSensitive(j, "bgPos"));
                }
            }
            if ((cJSON_HasObjectItem(j, "bgRelPath")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "bgRelPath")))) {
                x->bg_rel_path = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "bgRelPath")));
            }
            if ((cJSON_HasObjectItem(j, "externalRelPath")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "externalRelPath")))) {
                x->external_rel_path = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "externalRelPath")));
            }
            if (cJSON_HasObjectItem(j, "fieldInstances")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "fieldInstances");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetFieldInstanceValue(e1), sizeof(struct FieldInstance *));
                    }
                    x->field_instances = x1;
                }
            }
            else {
                x->field_instances = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "iid")) {
                x->iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "iid")));
            }
            else {
                if (NULL != (x->iid = cJSON_malloc(sizeof(char)))) {
                    x->iid[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "layerInstances")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "layerInstances")))) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "layerInstances");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetLayerInstanceValue(e1), sizeof(struct LayerInstance *));
                    }
                    x->layer_instances = x1;
                }
            }
            if (cJSON_HasObjectItem(j, "pxHei")) {
                x->px_hei = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxHei"));
            }
            if (cJSON_HasObjectItem(j, "pxWid")) {
                x->px_wid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "pxWid"));
            }
            if (cJSON_HasObjectItem(j, "uid")) {
                x->uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "uid"));
            }
            if (cJSON_HasObjectItem(j, "useAutoIdentifier")) {
                x->use_auto_identifier = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "useAutoIdentifier"));
            }
            if (cJSON_HasObjectItem(j, "worldDepth")) {
                x->world_depth = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldDepth"));
            }
            if (cJSON_HasObjectItem(j, "worldX")) {
                x->world_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldX"));
            }
            if (cJSON_HasObjectItem(j, "worldY")) {
                x->world_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldY"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLevel(const struct Level * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->bg_color) {
                cJSON_AddStringToObject(j, "__bgColor", x->bg_color);
            }
            else {
                cJSON_AddStringToObject(j, "__bgColor", "");
            }
            if (NULL != x->bg_pos) {
                cJSON_AddItemToObject(j, "__bgPos", cJSON_CreateLevelBackgroundPosition(x->bg_pos));
            }
            else {
                cJSON_AddNullToObject(j, "__bgPos");
            }
            if (NULL != x->neighbours) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "__neighbours");
                if (NULL != j1) {
                    struct NeighbourLevel * x1 = list_get_head(x->neighbours);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateNeighbourLevel(x1));
                        x1 = list_get_next(x->neighbours);
                    }
                }
            }
            if (NULL != x->smart_color) {
                cJSON_AddStringToObject(j, "__smartColor", x->smart_color);
            }
            else {
                cJSON_AddStringToObject(j, "__smartColor", "");
            }
            if (NULL != x->level_bg_color) {
                cJSON_AddStringToObject(j, "bgColor", x->level_bg_color);
            }
            else {
                cJSON_AddNullToObject(j, "bgColor");
            }
            cJSON_AddNumberToObject(j, "bgPivotX", x->bg_pivot_x);
            cJSON_AddNumberToObject(j, "bgPivotY", x->bg_pivot_y);
            if (NULL != x->level_bg_pos) {
                cJSON_AddItemToObject(j, "bgPos", cJSON_CreateBgPos(*x->level_bg_pos));
            }
            else {
                cJSON_AddNullToObject(j, "bgPos");
            }
            if (NULL != x->bg_rel_path) {
                cJSON_AddStringToObject(j, "bgRelPath", x->bg_rel_path);
            }
            else {
                cJSON_AddNullToObject(j, "bgRelPath");
            }
            if (NULL != x->external_rel_path) {
                cJSON_AddStringToObject(j, "externalRelPath", x->external_rel_path);
            }
            else {
                cJSON_AddNullToObject(j, "externalRelPath");
            }
            if (NULL != x->field_instances) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "fieldInstances");
                if (NULL != j1) {
                    struct FieldInstance * x1 = list_get_head(x->field_instances);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateFieldInstance(x1));
                        x1 = list_get_next(x->field_instances);
                    }
                }
            }
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            if (NULL != x->iid) {
                cJSON_AddStringToObject(j, "iid", x->iid);
            }
            else {
                cJSON_AddStringToObject(j, "iid", "");
            }
            if (NULL != x->layer_instances) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "layerInstances");
                if (NULL != j1) {
                    struct LayerInstance * x1 = list_get_head(x->layer_instances);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateLayerInstance(x1));
                        x1 = list_get_next(x->layer_instances);
                    }
                }
            }
            else {
                cJSON_AddNullToObject(j, "layerInstances");
            }
            cJSON_AddNumberToObject(j, "pxHei", x->px_hei);
            cJSON_AddNumberToObject(j, "pxWid", x->px_wid);
            cJSON_AddNumberToObject(j, "uid", x->uid);
            cJSON_AddBoolToObject(j, "useAutoIdentifier", x->use_auto_identifier);
            cJSON_AddNumberToObject(j, "worldDepth", x->world_depth);
            cJSON_AddNumberToObject(j, "worldX", x->world_x);
            cJSON_AddNumberToObject(j, "worldY", x->world_y);
        }
    }
    return j;
}

char * cJSON_PrintLevel(const struct Level * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLevel(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLevel(struct Level * x) {
    if (NULL != x) {
        if (NULL != x->bg_color) {
            cJSON_free(x->bg_color);
        }
        if (NULL != x->bg_pos) {
            cJSON_DeleteLevelBackgroundPosition(x->bg_pos);
        }
        if (NULL != x->neighbours) {
            struct NeighbourLevel * x1 = list_get_head(x->neighbours);
            while (NULL != x1) {
                cJSON_DeleteNeighbourLevel(x1);
                x1 = list_get_next(x->neighbours);
            }
            list_release(x->neighbours);
        }
        if (NULL != x->smart_color) {
            cJSON_free(x->smart_color);
        }
        if (NULL != x->level_bg_color) {
            cJSON_free(x->level_bg_color);
        }
        if (NULL != x->level_bg_pos) {
            cJSON_free(x->level_bg_pos);
        }
        if (NULL != x->bg_rel_path) {
            cJSON_free(x->bg_rel_path);
        }
        if (NULL != x->external_rel_path) {
            cJSON_free(x->external_rel_path);
        }
        if (NULL != x->field_instances) {
            struct FieldInstance * x1 = list_get_head(x->field_instances);
            while (NULL != x1) {
                cJSON_DeleteFieldInstance(x1);
                x1 = list_get_next(x->field_instances);
            }
            list_release(x->field_instances);
        }
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->iid) {
            cJSON_free(x->iid);
        }
        if (NULL != x->layer_instances) {
            struct LayerInstance * x1 = list_get_head(x->layer_instances);
            while (NULL != x1) {
                cJSON_DeleteLayerInstance(x1);
                x1 = list_get_next(x->layer_instances);
            }
            list_release(x->layer_instances);
        }
        cJSON_free(x);
    }
}

struct LdtkTableOfContentEntry * cJSON_ParseLdtkTableOfContentEntry(const char * s) {
    struct LdtkTableOfContentEntry * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLdtkTableOfContentEntryValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct LdtkTableOfContentEntry * cJSON_GetLdtkTableOfContentEntryValue(const cJSON * j) {
    struct LdtkTableOfContentEntry * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct LdtkTableOfContentEntry)))) {
            memset(x, 0, sizeof(struct LdtkTableOfContentEntry));
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "instances")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "instances");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetReferenceToAnEntityInstanceValue(e1), sizeof(struct ReferenceToAnEntityInstance *));
                    }
                    x->instances = x1;
                }
            }
            else {
                x->instances = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLdtkTableOfContentEntry(const struct LdtkTableOfContentEntry * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            if (NULL != x->instances) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "instances");
                if (NULL != j1) {
                    struct ReferenceToAnEntityInstance * x1 = list_get_head(x->instances);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateReferenceToAnEntityInstance(x1));
                        x1 = list_get_next(x->instances);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintLdtkTableOfContentEntry(const struct LdtkTableOfContentEntry * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLdtkTableOfContentEntry(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLdtkTableOfContentEntry(struct LdtkTableOfContentEntry * x) {
    if (NULL != x) {
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->instances) {
            struct ReferenceToAnEntityInstance * x1 = list_get_head(x->instances);
            while (NULL != x1) {
                cJSON_DeleteReferenceToAnEntityInstance(x1);
                x1 = list_get_next(x->instances);
            }
            list_release(x->instances);
        }
        cJSON_free(x);
    }
}

struct World * cJSON_ParseWorld(const char * s) {
    struct World * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetWorldValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct World * cJSON_GetWorldValue(const cJSON * j) {
    struct World * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct World)))) {
            memset(x, 0, sizeof(struct World));
            if (cJSON_HasObjectItem(j, "defaultLevelHeight")) {
                x->default_level_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelHeight"));
            }
            if (cJSON_HasObjectItem(j, "defaultLevelWidth")) {
                x->default_level_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelWidth"));
            }
            if (cJSON_HasObjectItem(j, "identifier")) {
                x->identifier = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "identifier")));
            }
            else {
                if (NULL != (x->identifier = cJSON_malloc(sizeof(char)))) {
                    x->identifier[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "iid")) {
                x->iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "iid")));
            }
            else {
                if (NULL != (x->iid = cJSON_malloc(sizeof(char)))) {
                    x->iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "levels")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "levels");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetLevelValue(e1), sizeof(struct Level *));
                    }
                    x->levels = x1;
                }
            }
            else {
                x->levels = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "worldGridHeight")) {
                x->world_grid_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldGridHeight"));
            }
            if (cJSON_HasObjectItem(j, "worldGridWidth")) {
                x->world_grid_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldGridWidth"));
            }
            if ((cJSON_HasObjectItem(j, "worldLayout")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "worldLayout")))) {
                if (NULL != (x->world_layout = cJSON_malloc(sizeof(enum WorldLayout)))) {
                    *x->world_layout = cJSON_GetWorldLayoutValue(cJSON_GetObjectItemCaseSensitive(j, "worldLayout"));
                }
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateWorld(const struct World * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            cJSON_AddNumberToObject(j, "defaultLevelHeight", x->default_level_height);
            cJSON_AddNumberToObject(j, "defaultLevelWidth", x->default_level_width);
            if (NULL != x->identifier) {
                cJSON_AddStringToObject(j, "identifier", x->identifier);
            }
            else {
                cJSON_AddStringToObject(j, "identifier", "");
            }
            if (NULL != x->iid) {
                cJSON_AddStringToObject(j, "iid", x->iid);
            }
            else {
                cJSON_AddStringToObject(j, "iid", "");
            }
            if (NULL != x->levels) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "levels");
                if (NULL != j1) {
                    struct Level * x1 = list_get_head(x->levels);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateLevel(x1));
                        x1 = list_get_next(x->levels);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "worldGridHeight", x->world_grid_height);
            cJSON_AddNumberToObject(j, "worldGridWidth", x->world_grid_width);
            if (NULL != x->world_layout) {
                cJSON_AddItemToObject(j, "worldLayout", cJSON_CreateWorldLayout(*x->world_layout));
            }
            else {
                cJSON_AddNullToObject(j, "worldLayout");
            }
        }
    }
    return j;
}

char * cJSON_PrintWorld(const struct World * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateWorld(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteWorld(struct World * x) {
    if (NULL != x) {
        if (NULL != x->identifier) {
            cJSON_free(x->identifier);
        }
        if (NULL != x->iid) {
            cJSON_free(x->iid);
        }
        if (NULL != x->levels) {
            struct Level * x1 = list_get_head(x->levels);
            while (NULL != x1) {
                cJSON_DeleteLevel(x1);
                x1 = list_get_next(x->levels);
            }
            list_release(x->levels);
        }
        if (NULL != x->world_layout) {
            cJSON_free(x->world_layout);
        }
        cJSON_free(x);
    }
}

struct ForcedRefs * cJSON_ParseForcedRefs(const char * s) {
    struct ForcedRefs * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetForcedRefsValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct ForcedRefs * cJSON_GetForcedRefsValue(const cJSON * j) {
    struct ForcedRefs * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct ForcedRefs)))) {
            memset(x, 0, sizeof(struct ForcedRefs));
            if (cJSON_HasObjectItem(j, "AutoLayerRuleGroup")) {
                x->auto_layer_rule_group = cJSON_GetAutoLayerRuleGroupValue(cJSON_GetObjectItemCaseSensitive(j, "AutoLayerRuleGroup"));
            }
            if (cJSON_HasObjectItem(j, "AutoRuleDef")) {
                x->auto_rule_def = cJSON_GetAutoLayerRuleDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "AutoRuleDef"));
            }
            if (cJSON_HasObjectItem(j, "CustomCommand")) {
                x->custom_command = cJSON_GetLdtkCustomCommandValue(cJSON_GetObjectItemCaseSensitive(j, "CustomCommand"));
            }
            if (cJSON_HasObjectItem(j, "Definitions")) {
                x->definitions = cJSON_GetDefinitionsValue(cJSON_GetObjectItemCaseSensitive(j, "Definitions"));
            }
            if (cJSON_HasObjectItem(j, "EntityDef")) {
                x->entity_def = cJSON_GetEntityDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "EntityDef"));
            }
            if (cJSON_HasObjectItem(j, "EntityInstance")) {
                x->entity_instance = cJSON_GetEntityInstanceValue(cJSON_GetObjectItemCaseSensitive(j, "EntityInstance"));
            }
            if (cJSON_HasObjectItem(j, "EntityReferenceInfos")) {
                x->entity_reference_infos = cJSON_GetReferenceToAnEntityInstanceValue(cJSON_GetObjectItemCaseSensitive(j, "EntityReferenceInfos"));
            }
            if (cJSON_HasObjectItem(j, "EnumDef")) {
                x->enum_def = cJSON_GetEnumDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "EnumDef"));
            }
            if (cJSON_HasObjectItem(j, "EnumDefValues")) {
                x->enum_def_values = cJSON_GetEnumValueDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "EnumDefValues"));
            }
            if (cJSON_HasObjectItem(j, "EnumTagValue")) {
                x->enum_tag_value = cJSON_GetEnumTagValueValue(cJSON_GetObjectItemCaseSensitive(j, "EnumTagValue"));
            }
            if (cJSON_HasObjectItem(j, "FieldDef")) {
                x->field_def = cJSON_GetFieldDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "FieldDef"));
            }
            if (cJSON_HasObjectItem(j, "FieldInstance")) {
                x->field_instance = cJSON_GetFieldInstanceValue(cJSON_GetObjectItemCaseSensitive(j, "FieldInstance"));
            }
            if (cJSON_HasObjectItem(j, "GridPoint")) {
                x->grid_point = cJSON_GetGridPointValue(cJSON_GetObjectItemCaseSensitive(j, "GridPoint"));
            }
            if (cJSON_HasObjectItem(j, "IntGridValueDef")) {
                x->int_grid_value_def = cJSON_GetIntGridValueDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "IntGridValueDef"));
            }
            if (cJSON_HasObjectItem(j, "IntGridValueGroupDef")) {
                x->int_grid_value_group_def = cJSON_GetIntGridValueGroupDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "IntGridValueGroupDef"));
            }
            if (cJSON_HasObjectItem(j, "IntGridValueInstance")) {
                x->int_grid_value_instance = cJSON_GetIntGridValueInstanceValue(cJSON_GetObjectItemCaseSensitive(j, "IntGridValueInstance"));
            }
            if (cJSON_HasObjectItem(j, "LayerDef")) {
                x->layer_def = cJSON_GetLayerDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "LayerDef"));
            }
            if (cJSON_HasObjectItem(j, "LayerInstance")) {
                x->layer_instance = cJSON_GetLayerInstanceValue(cJSON_GetObjectItemCaseSensitive(j, "LayerInstance"));
            }
            if (cJSON_HasObjectItem(j, "Level")) {
                x->level = cJSON_GetLevelValue(cJSON_GetObjectItemCaseSensitive(j, "Level"));
            }
            if (cJSON_HasObjectItem(j, "LevelBgPosInfos")) {
                x->level_bg_pos_infos = cJSON_GetLevelBackgroundPositionValue(cJSON_GetObjectItemCaseSensitive(j, "LevelBgPosInfos"));
            }
            if (cJSON_HasObjectItem(j, "NeighbourLevel")) {
                x->neighbour_level = cJSON_GetNeighbourLevelValue(cJSON_GetObjectItemCaseSensitive(j, "NeighbourLevel"));
            }
            if (cJSON_HasObjectItem(j, "TableOfContentEntry")) {
                x->table_of_content_entry = cJSON_GetLdtkTableOfContentEntryValue(cJSON_GetObjectItemCaseSensitive(j, "TableOfContentEntry"));
            }
            if (cJSON_HasObjectItem(j, "Tile")) {
                x->tile = cJSON_GetTileInstanceValue(cJSON_GetObjectItemCaseSensitive(j, "Tile"));
            }
            if (cJSON_HasObjectItem(j, "TileCustomMetadata")) {
                x->tile_custom_metadata = cJSON_GetTileCustomMetadataValue(cJSON_GetObjectItemCaseSensitive(j, "TileCustomMetadata"));
            }
            if (cJSON_HasObjectItem(j, "TilesetDef")) {
                x->tileset_def = cJSON_GetTilesetDefinitionValue(cJSON_GetObjectItemCaseSensitive(j, "TilesetDef"));
            }
            if (cJSON_HasObjectItem(j, "TilesetRect")) {
                x->tileset_rect = cJSON_GetTilesetRectangleValue(cJSON_GetObjectItemCaseSensitive(j, "TilesetRect"));
            }
            if (cJSON_HasObjectItem(j, "World")) {
                x->world = cJSON_GetWorldValue(cJSON_GetObjectItemCaseSensitive(j, "World"));
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateForcedRefs(const struct ForcedRefs * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->auto_layer_rule_group) {
                cJSON_AddItemToObject(j, "AutoLayerRuleGroup", cJSON_CreateAutoLayerRuleGroup(x->auto_layer_rule_group));
            }
            if (NULL != x->auto_rule_def) {
                cJSON_AddItemToObject(j, "AutoRuleDef", cJSON_CreateAutoLayerRuleDefinition(x->auto_rule_def));
            }
            if (NULL != x->custom_command) {
                cJSON_AddItemToObject(j, "CustomCommand", cJSON_CreateLdtkCustomCommand(x->custom_command));
            }
            if (NULL != x->definitions) {
                cJSON_AddItemToObject(j, "Definitions", cJSON_CreateDefinitions(x->definitions));
            }
            if (NULL != x->entity_def) {
                cJSON_AddItemToObject(j, "EntityDef", cJSON_CreateEntityDefinition(x->entity_def));
            }
            if (NULL != x->entity_instance) {
                cJSON_AddItemToObject(j, "EntityInstance", cJSON_CreateEntityInstance(x->entity_instance));
            }
            if (NULL != x->entity_reference_infos) {
                cJSON_AddItemToObject(j, "EntityReferenceInfos", cJSON_CreateReferenceToAnEntityInstance(x->entity_reference_infos));
            }
            if (NULL != x->enum_def) {
                cJSON_AddItemToObject(j, "EnumDef", cJSON_CreateEnumDefinition(x->enum_def));
            }
            if (NULL != x->enum_def_values) {
                cJSON_AddItemToObject(j, "EnumDefValues", cJSON_CreateEnumValueDefinition(x->enum_def_values));
            }
            if (NULL != x->enum_tag_value) {
                cJSON_AddItemToObject(j, "EnumTagValue", cJSON_CreateEnumTagValue(x->enum_tag_value));
            }
            if (NULL != x->field_def) {
                cJSON_AddItemToObject(j, "FieldDef", cJSON_CreateFieldDefinition(x->field_def));
            }
            if (NULL != x->field_instance) {
                cJSON_AddItemToObject(j, "FieldInstance", cJSON_CreateFieldInstance(x->field_instance));
            }
            if (NULL != x->grid_point) {
                cJSON_AddItemToObject(j, "GridPoint", cJSON_CreateGridPoint(x->grid_point));
            }
            if (NULL != x->int_grid_value_def) {
                cJSON_AddItemToObject(j, "IntGridValueDef", cJSON_CreateIntGridValueDefinition(x->int_grid_value_def));
            }
            if (NULL != x->int_grid_value_group_def) {
                cJSON_AddItemToObject(j, "IntGridValueGroupDef", cJSON_CreateIntGridValueGroupDefinition(x->int_grid_value_group_def));
            }
            if (NULL != x->int_grid_value_instance) {
                cJSON_AddItemToObject(j, "IntGridValueInstance", cJSON_CreateIntGridValueInstance(x->int_grid_value_instance));
            }
            if (NULL != x->layer_def) {
                cJSON_AddItemToObject(j, "LayerDef", cJSON_CreateLayerDefinition(x->layer_def));
            }
            if (NULL != x->layer_instance) {
                cJSON_AddItemToObject(j, "LayerInstance", cJSON_CreateLayerInstance(x->layer_instance));
            }
            if (NULL != x->level) {
                cJSON_AddItemToObject(j, "Level", cJSON_CreateLevel(x->level));
            }
            if (NULL != x->level_bg_pos_infos) {
                cJSON_AddItemToObject(j, "LevelBgPosInfos", cJSON_CreateLevelBackgroundPosition(x->level_bg_pos_infos));
            }
            if (NULL != x->neighbour_level) {
                cJSON_AddItemToObject(j, "NeighbourLevel", cJSON_CreateNeighbourLevel(x->neighbour_level));
            }
            if (NULL != x->table_of_content_entry) {
                cJSON_AddItemToObject(j, "TableOfContentEntry", cJSON_CreateLdtkTableOfContentEntry(x->table_of_content_entry));
            }
            if (NULL != x->tile) {
                cJSON_AddItemToObject(j, "Tile", cJSON_CreateTileInstance(x->tile));
            }
            if (NULL != x->tile_custom_metadata) {
                cJSON_AddItemToObject(j, "TileCustomMetadata", cJSON_CreateTileCustomMetadata(x->tile_custom_metadata));
            }
            if (NULL != x->tileset_def) {
                cJSON_AddItemToObject(j, "TilesetDef", cJSON_CreateTilesetDefinition(x->tileset_def));
            }
            if (NULL != x->tileset_rect) {
                cJSON_AddItemToObject(j, "TilesetRect", cJSON_CreateTilesetRectangle(x->tileset_rect));
            }
            if (NULL != x->world) {
                cJSON_AddItemToObject(j, "World", cJSON_CreateWorld(x->world));
            }
        }
    }
    return j;
}

char * cJSON_PrintForcedRefs(const struct ForcedRefs * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateForcedRefs(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteForcedRefs(struct ForcedRefs * x) {
    if (NULL != x) {
        if (NULL != x->auto_layer_rule_group) {
            cJSON_DeleteAutoLayerRuleGroup(x->auto_layer_rule_group);
        }
        if (NULL != x->auto_rule_def) {
            cJSON_DeleteAutoLayerRuleDefinition(x->auto_rule_def);
        }
        if (NULL != x->custom_command) {
            cJSON_DeleteLdtkCustomCommand(x->custom_command);
        }
        if (NULL != x->definitions) {
            cJSON_DeleteDefinitions(x->definitions);
        }
        if (NULL != x->entity_def) {
            cJSON_DeleteEntityDefinition(x->entity_def);
        }
        if (NULL != x->entity_instance) {
            cJSON_DeleteEntityInstance(x->entity_instance);
        }
        if (NULL != x->entity_reference_infos) {
            cJSON_DeleteReferenceToAnEntityInstance(x->entity_reference_infos);
        }
        if (NULL != x->enum_def) {
            cJSON_DeleteEnumDefinition(x->enum_def);
        }
        if (NULL != x->enum_def_values) {
            cJSON_DeleteEnumValueDefinition(x->enum_def_values);
        }
        if (NULL != x->enum_tag_value) {
            cJSON_DeleteEnumTagValue(x->enum_tag_value);
        }
        if (NULL != x->field_def) {
            cJSON_DeleteFieldDefinition(x->field_def);
        }
        if (NULL != x->field_instance) {
            cJSON_DeleteFieldInstance(x->field_instance);
        }
        if (NULL != x->grid_point) {
            cJSON_DeleteGridPoint(x->grid_point);
        }
        if (NULL != x->int_grid_value_def) {
            cJSON_DeleteIntGridValueDefinition(x->int_grid_value_def);
        }
        if (NULL != x->int_grid_value_group_def) {
            cJSON_DeleteIntGridValueGroupDefinition(x->int_grid_value_group_def);
        }
        if (NULL != x->int_grid_value_instance) {
            cJSON_DeleteIntGridValueInstance(x->int_grid_value_instance);
        }
        if (NULL != x->layer_def) {
            cJSON_DeleteLayerDefinition(x->layer_def);
        }
        if (NULL != x->layer_instance) {
            cJSON_DeleteLayerInstance(x->layer_instance);
        }
        if (NULL != x->level) {
            cJSON_DeleteLevel(x->level);
        }
        if (NULL != x->level_bg_pos_infos) {
            cJSON_DeleteLevelBackgroundPosition(x->level_bg_pos_infos);
        }
        if (NULL != x->neighbour_level) {
            cJSON_DeleteNeighbourLevel(x->neighbour_level);
        }
        if (NULL != x->table_of_content_entry) {
            cJSON_DeleteLdtkTableOfContentEntry(x->table_of_content_entry);
        }
        if (NULL != x->tile) {
            cJSON_DeleteTileInstance(x->tile);
        }
        if (NULL != x->tile_custom_metadata) {
            cJSON_DeleteTileCustomMetadata(x->tile_custom_metadata);
        }
        if (NULL != x->tileset_def) {
            cJSON_DeleteTilesetDefinition(x->tileset_def);
        }
        if (NULL != x->tileset_rect) {
            cJSON_DeleteTilesetRectangle(x->tileset_rect);
        }
        if (NULL != x->world) {
            cJSON_DeleteWorld(x->world);
        }
        cJSON_free(x);
    }
}

struct LDtk * cJSON_ParseLDtk(const char * s) {
    struct LDtk * x = NULL;
    if (NULL != s) {
        cJSON * j = cJSON_Parse(s);
        if (NULL != j) {
            x = cJSON_GetLDtkValue(j);
            cJSON_Delete(j);
        }
    }
    return x;
}

struct LDtk * cJSON_GetLDtkValue(const cJSON * j) {
    struct LDtk * x = NULL;
    if (NULL != j) {
        if (NULL != (x = cJSON_malloc(sizeof(struct LDtk)))) {
            memset(x, 0, sizeof(struct LDtk));
            if (cJSON_HasObjectItem(j, "__FORCED_REFS")) {
                x->forced_refs = cJSON_GetForcedRefsValue(cJSON_GetObjectItemCaseSensitive(j, "__FORCED_REFS"));
            }
            if (cJSON_HasObjectItem(j, "appBuildId")) {
                x->app_build_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "appBuildId"));
            }
            if (cJSON_HasObjectItem(j, "backupLimit")) {
                x->backup_limit = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "backupLimit"));
            }
            if (cJSON_HasObjectItem(j, "backupOnSave")) {
                x->backup_on_save = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "backupOnSave"));
            }
            if ((cJSON_HasObjectItem(j, "backupRelPath")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "backupRelPath")))) {
                x->backup_rel_path = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "backupRelPath")));
            }
            if (cJSON_HasObjectItem(j, "bgColor")) {
                x->bg_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "bgColor")));
            }
            else {
                if (NULL != (x->bg_color = cJSON_malloc(sizeof(char)))) {
                    x->bg_color[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "customCommands")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "customCommands");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetLdtkCustomCommandValue(e1), sizeof(struct LdtkCustomCommand *));
                    }
                    x->custom_commands = x1;
                }
            }
            else {
                x->custom_commands = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "defaultEntityHeight")) {
                x->default_entity_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultEntityHeight"));
            }
            if (cJSON_HasObjectItem(j, "defaultEntityWidth")) {
                x->default_entity_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultEntityWidth"));
            }
            if (cJSON_HasObjectItem(j, "defaultGridSize")) {
                x->default_grid_size = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultGridSize"));
            }
            if (cJSON_HasObjectItem(j, "defaultLevelBgColor")) {
                x->default_level_bg_color = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelBgColor")));
            }
            else {
                if (NULL != (x->default_level_bg_color = cJSON_malloc(sizeof(char)))) {
                    x->default_level_bg_color[0] = '\0';
                }
            }
            if ((cJSON_HasObjectItem(j, "defaultLevelHeight")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelHeight")))) {
                if (NULL != (x->default_level_height = cJSON_malloc(sizeof(int64_t)))) {
                    *x->default_level_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelHeight"));
                }
            }
            if ((cJSON_HasObjectItem(j, "defaultLevelWidth")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelWidth")))) {
                if (NULL != (x->default_level_width = cJSON_malloc(sizeof(int64_t)))) {
                    *x->default_level_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultLevelWidth"));
                }
            }
            if (cJSON_HasObjectItem(j, "defaultPivotX")) {
                x->default_pivot_x = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultPivotX"));
            }
            if (cJSON_HasObjectItem(j, "defaultPivotY")) {
                x->default_pivot_y = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "defaultPivotY"));
            }
            if (cJSON_HasObjectItem(j, "defs")) {
                x->defs = cJSON_GetDefinitionsValue(cJSON_GetObjectItemCaseSensitive(j, "defs"));
            }
            if (cJSON_HasObjectItem(j, "dummyWorldIid")) {
                x->dummy_world_iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "dummyWorldIid")));
            }
            else {
                if (NULL != (x->dummy_world_iid = cJSON_malloc(sizeof(char)))) {
                    x->dummy_world_iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "exportLevelBg")) {
                x->export_level_bg = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "exportLevelBg"));
            }
            if ((cJSON_HasObjectItem(j, "exportPng")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "exportPng")))) {
                if (NULL != (x->export_png = cJSON_malloc(sizeof(bool)))) {
                    *x->export_png = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "exportPng"));
                }
            }
            if (cJSON_HasObjectItem(j, "exportTiled")) {
                x->export_tiled = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "exportTiled"));
            }
            if (cJSON_HasObjectItem(j, "externalLevels")) {
                x->external_levels = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "externalLevels"));
            }
            if (cJSON_HasObjectItem(j, "flags")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "flags");
                    cJSON_ArrayForEach(e1, j1) {
                        enum Flag * tmp = cJSON_malloc(sizeof(enum Flag));
                        if (NULL != tmp) {
                            * tmp = cJSON_GetFlagValue(e1);
                            list_add_tail(x1, tmp, sizeof(enum Flag *));
                        }
                    }
                    x->flags = x1;
                }
            }
            else {
                x->flags = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "identifierStyle")) {
                x->identifier_style = cJSON_GetIdentifierStyleValue(cJSON_GetObjectItemCaseSensitive(j, "identifierStyle"));
            }
            if (cJSON_HasObjectItem(j, "iid")) {
                x->iid = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "iid")));
            }
            else {
                if (NULL != (x->iid = cJSON_malloc(sizeof(char)))) {
                    x->iid[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "imageExportMode")) {
                x->image_export_mode = cJSON_GetImageExportModeValue(cJSON_GetObjectItemCaseSensitive(j, "imageExportMode"));
            }
            if (cJSON_HasObjectItem(j, "jsonVersion")) {
                x->json_version = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "jsonVersion")));
            }
            else {
                if (NULL != (x->json_version = cJSON_malloc(sizeof(char)))) {
                    x->json_version[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "levelNamePattern")) {
                x->level_name_pattern = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "levelNamePattern")));
            }
            else {
                if (NULL != (x->level_name_pattern = cJSON_malloc(sizeof(char)))) {
                    x->level_name_pattern[0] = '\0';
                }
            }
            if (cJSON_HasObjectItem(j, "levels")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "levels");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetLevelValue(e1), sizeof(struct Level *));
                    }
                    x->levels = x1;
                }
            }
            else {
                x->levels = list_create(false, NULL);
            }
            if (cJSON_HasObjectItem(j, "minifyJson")) {
                x->minify_json = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "minifyJson"));
            }
            if (cJSON_HasObjectItem(j, "nextUid")) {
                x->next_uid = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "nextUid"));
            }
            if ((cJSON_HasObjectItem(j, "pngFilePattern")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "pngFilePattern")))) {
                x->png_file_pattern = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "pngFilePattern")));
            }
            if (cJSON_HasObjectItem(j, "simplifiedExport")) {
                x->simplified_export = cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(j, "simplifiedExport"));
            }
            if (cJSON_HasObjectItem(j, "toc")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "toc");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetLdtkTableOfContentEntryValue(e1), sizeof(struct LdtkTableOfContentEntry *));
                    }
                    x->toc = x1;
                }
            }
            else {
                x->toc = list_create(false, NULL);
            }
            if ((cJSON_HasObjectItem(j, "tutorialDesc")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "tutorialDesc")))) {
                x->tutorial_desc = strdup(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(j, "tutorialDesc")));
            }
            if ((cJSON_HasObjectItem(j, "worldGridHeight")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "worldGridHeight")))) {
                if (NULL != (x->world_grid_height = cJSON_malloc(sizeof(int64_t)))) {
                    *x->world_grid_height = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldGridHeight"));
                }
            }
            if ((cJSON_HasObjectItem(j, "worldGridWidth")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "worldGridWidth")))) {
                if (NULL != (x->world_grid_width = cJSON_malloc(sizeof(int64_t)))) {
                    *x->world_grid_width = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(j, "worldGridWidth"));
                }
            }
            if ((cJSON_HasObjectItem(j, "worldLayout")) && (!cJSON_IsNull(cJSON_GetObjectItemCaseSensitive(j, "worldLayout")))) {
                if (NULL != (x->world_layout = cJSON_malloc(sizeof(enum WorldLayout)))) {
                    *x->world_layout = cJSON_GetWorldLayoutValue(cJSON_GetObjectItemCaseSensitive(j, "worldLayout"));
                }
            }
            if (cJSON_HasObjectItem(j, "worlds")) {
                list_t * x1 = list_create(false, NULL);
                if (NULL != x1) {
                    cJSON * e1 = NULL;
                    cJSON * j1 = cJSON_GetObjectItemCaseSensitive(j, "worlds");
                    cJSON_ArrayForEach(e1, j1) {
                        list_add_tail(x1, cJSON_GetWorldValue(e1), sizeof(struct World *));
                    }
                    x->worlds = x1;
                }
            }
            else {
                x->worlds = list_create(false, NULL);
            }
        }
    }
    return x;
}

cJSON * cJSON_CreateLDtk(const struct LDtk * x) {
    cJSON * j = NULL;
    if (NULL != x) {
        if (NULL != (j = cJSON_CreateObject())) {
            if (NULL != x->forced_refs) {
                cJSON_AddItemToObject(j, "__FORCED_REFS", cJSON_CreateForcedRefs(x->forced_refs));
            }
            cJSON_AddNumberToObject(j, "appBuildId", x->app_build_id);
            cJSON_AddNumberToObject(j, "backupLimit", x->backup_limit);
            cJSON_AddBoolToObject(j, "backupOnSave", x->backup_on_save);
            if (NULL != x->backup_rel_path) {
                cJSON_AddStringToObject(j, "backupRelPath", x->backup_rel_path);
            }
            else {
                cJSON_AddNullToObject(j, "backupRelPath");
            }
            if (NULL != x->bg_color) {
                cJSON_AddStringToObject(j, "bgColor", x->bg_color);
            }
            else {
                cJSON_AddStringToObject(j, "bgColor", "");
            }
            if (NULL != x->custom_commands) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "customCommands");
                if (NULL != j1) {
                    struct LdtkCustomCommand * x1 = list_get_head(x->custom_commands);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateLdtkCustomCommand(x1));
                        x1 = list_get_next(x->custom_commands);
                    }
                }
            }
            cJSON_AddNumberToObject(j, "defaultEntityHeight", x->default_entity_height);
            cJSON_AddNumberToObject(j, "defaultEntityWidth", x->default_entity_width);
            cJSON_AddNumberToObject(j, "defaultGridSize", x->default_grid_size);
            if (NULL != x->default_level_bg_color) {
                cJSON_AddStringToObject(j, "defaultLevelBgColor", x->default_level_bg_color);
            }
            else {
                cJSON_AddStringToObject(j, "defaultLevelBgColor", "");
            }
            if (NULL != x->default_level_height) {
                cJSON_AddNumberToObject(j, "defaultLevelHeight", *x->default_level_height);
            }
            else {
                cJSON_AddNullToObject(j, "defaultLevelHeight");
            }
            if (NULL != x->default_level_width) {
                cJSON_AddNumberToObject(j, "defaultLevelWidth", *x->default_level_width);
            }
            else {
                cJSON_AddNullToObject(j, "defaultLevelWidth");
            }
            cJSON_AddNumberToObject(j, "defaultPivotX", x->default_pivot_x);
            cJSON_AddNumberToObject(j, "defaultPivotY", x->default_pivot_y);
            cJSON_AddItemToObject(j, "defs", cJSON_CreateDefinitions(x->defs));
            if (NULL != x->dummy_world_iid) {
                cJSON_AddStringToObject(j, "dummyWorldIid", x->dummy_world_iid);
            }
            else {
                cJSON_AddStringToObject(j, "dummyWorldIid", "");
            }
            cJSON_AddBoolToObject(j, "exportLevelBg", x->export_level_bg);
            if (NULL != x->export_png) {
                cJSON_AddBoolToObject(j, "exportPng", *x->export_png);
            }
            else {
                cJSON_AddNullToObject(j, "exportPng");
            }
            cJSON_AddBoolToObject(j, "exportTiled", x->export_tiled);
            cJSON_AddBoolToObject(j, "externalLevels", x->external_levels);
            if (NULL != x->flags) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "flags");
                if (NULL != j1) {
                    enum Flag * x1 = list_get_head(x->flags);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateFlag(*x1));
                        x1 = list_get_next(x->flags);
                    }
                }
            }
            cJSON_AddItemToObject(j, "identifierStyle", cJSON_CreateIdentifierStyle(x->identifier_style));
            if (NULL != x->iid) {
                cJSON_AddStringToObject(j, "iid", x->iid);
            }
            else {
                cJSON_AddStringToObject(j, "iid", "");
            }
            cJSON_AddItemToObject(j, "imageExportMode", cJSON_CreateImageExportMode(x->image_export_mode));
            if (NULL != x->json_version) {
                cJSON_AddStringToObject(j, "jsonVersion", x->json_version);
            }
            else {
                cJSON_AddStringToObject(j, "jsonVersion", "");
            }
            if (NULL != x->level_name_pattern) {
                cJSON_AddStringToObject(j, "levelNamePattern", x->level_name_pattern);
            }
            else {
                cJSON_AddStringToObject(j, "levelNamePattern", "");
            }
            if (NULL != x->levels) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "levels");
                if (NULL != j1) {
                    struct Level * x1 = list_get_head(x->levels);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateLevel(x1));
                        x1 = list_get_next(x->levels);
                    }
                }
            }
            cJSON_AddBoolToObject(j, "minifyJson", x->minify_json);
            cJSON_AddNumberToObject(j, "nextUid", x->next_uid);
            if (NULL != x->png_file_pattern) {
                cJSON_AddStringToObject(j, "pngFilePattern", x->png_file_pattern);
            }
            else {
                cJSON_AddNullToObject(j, "pngFilePattern");
            }
            cJSON_AddBoolToObject(j, "simplifiedExport", x->simplified_export);
            if (NULL != x->toc) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "toc");
                if (NULL != j1) {
                    struct LdtkTableOfContentEntry * x1 = list_get_head(x->toc);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateLdtkTableOfContentEntry(x1));
                        x1 = list_get_next(x->toc);
                    }
                }
            }
            if (NULL != x->tutorial_desc) {
                cJSON_AddStringToObject(j, "tutorialDesc", x->tutorial_desc);
            }
            else {
                cJSON_AddNullToObject(j, "tutorialDesc");
            }
            if (NULL != x->world_grid_height) {
                cJSON_AddNumberToObject(j, "worldGridHeight", *x->world_grid_height);
            }
            else {
                cJSON_AddNullToObject(j, "worldGridHeight");
            }
            if (NULL != x->world_grid_width) {
                cJSON_AddNumberToObject(j, "worldGridWidth", *x->world_grid_width);
            }
            else {
                cJSON_AddNullToObject(j, "worldGridWidth");
            }
            if (NULL != x->world_layout) {
                cJSON_AddItemToObject(j, "worldLayout", cJSON_CreateWorldLayout(*x->world_layout));
            }
            else {
                cJSON_AddNullToObject(j, "worldLayout");
            }
            if (NULL != x->worlds) {
                cJSON * j1 = cJSON_AddArrayToObject(j, "worlds");
                if (NULL != j1) {
                    struct World * x1 = list_get_head(x->worlds);
                    while (NULL != x1) {
                        cJSON_AddItemToArray(j1, cJSON_CreateWorld(x1));
                        x1 = list_get_next(x->worlds);
                    }
                }
            }
        }
    }
    return j;
}

char * cJSON_PrintLDtk(const struct LDtk * x) {
    char * s = NULL;
    if (NULL != x) {
        cJSON * j = cJSON_CreateLDtk(x);
        if (NULL != j) {
            s = cJSON_Print(j);
            cJSON_Delete(j);
        }
    }
    return s;
}

void cJSON_DeleteLDtk(struct LDtk * x) {
    if (NULL != x) {
        if (NULL != x->forced_refs) {
            cJSON_DeleteForcedRefs(x->forced_refs);
        }
        if (NULL != x->backup_rel_path) {
            cJSON_free(x->backup_rel_path);
        }
        if (NULL != x->bg_color) {
            cJSON_free(x->bg_color);
        }
        if (NULL != x->custom_commands) {
            struct LdtkCustomCommand * x1 = list_get_head(x->custom_commands);
            while (NULL != x1) {
                cJSON_DeleteLdtkCustomCommand(x1);
                x1 = list_get_next(x->custom_commands);
            }
            list_release(x->custom_commands);
        }
        if (NULL != x->default_level_bg_color) {
            cJSON_free(x->default_level_bg_color);
        }
        if (NULL != x->default_level_height) {
            cJSON_free(x->default_level_height);
        }
        if (NULL != x->default_level_width) {
            cJSON_free(x->default_level_width);
        }
        if (NULL != x->defs) {
            cJSON_DeleteDefinitions(x->defs);
        }
        if (NULL != x->dummy_world_iid) {
            cJSON_free(x->dummy_world_iid);
        }
        if (NULL != x->export_png) {
            cJSON_free(x->export_png);
        }
        if (NULL != x->flags) {
            enum Flag * x1 = list_get_head(x->flags);
            while (NULL != x1) {
                cJSON_free(x1);
                x1 = list_get_next(x->flags);
            }
            list_release(x->flags);
        }
        if (NULL != x->iid) {
            cJSON_free(x->iid);
        }
        if (NULL != x->json_version) {
            cJSON_free(x->json_version);
        }
        if (NULL != x->level_name_pattern) {
            cJSON_free(x->level_name_pattern);
        }
        if (NULL != x->levels) {
            struct Level * x1 = list_get_head(x->levels);
            while (NULL != x1) {
                cJSON_DeleteLevel(x1);
                x1 = list_get_next(x->levels);
            }
            list_release(x->levels);
        }
        if (NULL != x->png_file_pattern) {
            cJSON_free(x->png_file_pattern);
        }
        if (NULL != x->toc) {
            struct LdtkTableOfContentEntry * x1 = list_get_head(x->toc);
            while (NULL != x1) {
                cJSON_DeleteLdtkTableOfContentEntry(x1);
                x1 = list_get_next(x->toc);
            }
            list_release(x->toc);
        }
        if (NULL != x->tutorial_desc) {
            cJSON_free(x->tutorial_desc);
        }
        if (NULL != x->world_grid_height) {
            cJSON_free(x->world_grid_height);
        }
        if (NULL != x->world_grid_width) {
            cJSON_free(x->world_grid_width);
        }
        if (NULL != x->world_layout) {
            cJSON_free(x->world_layout);
        }
        if (NULL != x->worlds) {
            struct World * x1 = list_get_head(x->worlds);
            while (NULL != x1) {
                cJSON_DeleteWorld(x1);
                x1 = list_get_next(x->worlds);
            }
            list_release(x->worlds);
        }
        cJSON_free(x);
    }
}
