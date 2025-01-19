#include <engine/physics.h>
#include <tmx.h>
#include <stdio.h>
#include <raylib.h>
#include <rlgl.h>

const cpFloat SHAPE_BEVEL = 1;
const cpFloat POINT_RADIUS = .5;

cpBody* GiveBodyTMXShape(cpBody *body, tmx_object *obj, tmx_tile **maptiles, cpVect offset) {
    tmx_property *collidable = tmx_get_property(obj->properties, "collidable");
    if (!collidable || !collidable->value.boolean)
        return body;

    cpShape *shape = NULL;
    cpSpace *space = cpBodyGetSpace(body);
    switch (obj->obj_type) {
        case OT_POINT: {
            shape = cpCircleShapeNew(body, POINT_RADIUS, offset);
            if (space) cpSpaceAddShape(space, shape);
        } break;
        case OT_ELLIPSE: {
            double radius = (obj->width + obj->height)/4;
            shape = cpCircleShapeNew(body, radius, cpv(offset.x + radius, offset.y + radius));
            if (space) cpSpaceAddShape(space, shape);
        } break;
        case OT_SQUARE: {
            shape = cpBoxShapeNew2(body, (cpBB) {
                .l = offset.x,
                .t = offset.y,
                .r = offset.x + obj->width,
                .b = offset.y + obj->height
            }, SHAPE_BEVEL);
            if (space) cpSpaceAddShape(space, shape);
        } break;
        case OT_POLYGON: {
            int nPoints = obj->content.shape->points_len;
            double **points = obj->content.shape->points;
            cpVect *verts = calloc(nPoints, sizeof(cpVect));
            for (int i = 0; i < nPoints; ++i) {
                verts[i].x = offset.x + points[i][0];
                verts[i].y = offset.y + points[i][1];
            }
            shape = cpPolyShapeNew(body, nPoints, verts, cpTransformIdentity, SHAPE_BEVEL);
            if (space) cpSpaceAddShape(space, shape);
            free(verts);
        } break;
        case OT_POLYLINE: {
            int nPoints = obj->content.shape->points_len;
            double **points = obj->content.shape->points;
            cpVect a = {
                offset.x + points[0][0],
                offset.y + points[0][1]
            };
            for (int i = 1; i < nPoints; ++i) {
                cpVect b = {
                    offset.x + points[i][0],
                    offset.y + points[i][1]
                };
                shape = cpSegmentShapeNew(body, a, b, SHAPE_BEVEL);
                if (space) cpSpaceAddShape(space, shape);
                a = b;
            }
        } break;
        case OT_TILE: {
            tmx_tile *tile = maptiles[obj->content.gid];
            if (!tile) {
                fprintf(stderr, "no tile with gid %d", obj->content.gid);
                break;
            }

            Vector2 origin = {0,0};
            GetTileOrigin(&origin, tile, VECTOR2(0, 0));

            for (tmx_object *col = tile->collision; col; col = col->next) {
                cpVect offset = {col->x-origin.x, col->y-origin.y};
                GiveBodyTMXShape(body, col, maptiles, offset);
            }
        } break;
    }

    return body;
}

void DrawTMXTileCollisionShape(tmx_object *obj, Vector2 offset, Color color) {
    tmx_property *collidable = tmx_get_property(obj->properties, "collidable");
    if (!collidable || !collidable->value.boolean)
        return;

    switch (obj->obj_type) {
        case OT_POINT: {
            DrawCircleLinesV(offset, POINT_RADIUS, color);
        } break;
        case OT_ELLIPSE: {
            double radius = (obj->width + obj->height)/4;
            DrawCircleLinesV(VECTOR2(offset.x + radius, offset.y + radius),
                (obj->width + obj->height)/4, color);
        } break;
        case OT_SQUARE: {
            DrawRectangleLines(offset.x,offset.y,obj->width,obj->height,color);
        } break;
        case OT_POLYGON: {
            int nPoints = obj->content.shape->points_len;
            double **points = obj->content.shape->points;
            Vector2 a = {
                offset.x + points[nPoints-1][0],
                offset.y + points[nPoints-1][1]
            };
            for (int i = 0; i < nPoints; ++i) {
                Vector2 b = {
                    offset.x + points[i][0],
                    offset.y + points[i][1]
                };
                DrawLineV(a, b, color);
                a = b;
            }
        } break;
        case OT_POLYLINE: {
            int nPoints = obj->content.shape->points_len;
            double **points = obj->content.shape->points;
            Vector2 a = {
                offset.x + points[0][0],
                offset.y + points[0][1]
            };
            for (int i = 1; i < nPoints; ++i) {
                Vector2 b = {
                    offset.x + points[i][0],
                    offset.y + points[i][1]
                };
                DrawLineV(a, b, color);
                a = b;
            }
        } break;
    }

    return;
}

void DrawTMXTileCollisionShapes(tmx_tile *tile, Vector2 position, float rotationDeg, Color color) {
    Vector2 origin = {0, 0};
    GetTileOrigin(&origin, tile, VECTOR2(0, 0));
    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0);
    rlRotatef(rotationDeg, 0, 0, 1);
    for (tmx_object *col = tile->collision; col; col = col->next) {
        Vector2 offset = {col->x-origin.x, col->y-origin.y};
        DrawTMXTileCollisionShape(col, offset, color);
    }
    rlPopMatrix();
}