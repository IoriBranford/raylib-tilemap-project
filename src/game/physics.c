#include <box2d/box2d.h>
#include <engine.h>

static b2WorldId worldId;

void ClosePhysics();

void InitPhysics(float lengthUnitsPerMeter) {
    if (B2_IS_NON_NULL(worldId))
        ClosePhysics();
    b2SetLengthUnitsPerMeter(lengthUnitsPerMeter);
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = 0;
	worldId = b2CreateWorld(&worldDef);
}

void ClosePhysics() {
    if (B2_IS_NON_NULL(worldId))
        b2DestroyWorld(worldId);
    worldId = (b2WorldId){0};
}

void UpdatePhysics() {
    b2World_Step(worldId, 1, 4);
}

void UpdateSpriteFromBody(b2BodyId body, Sprite *sprite) {
    b2Vec2 position = b2Body_GetPosition(body);
    b2Rot rot = b2Body_GetRotation(body);
    sprite->position = (Vector2){ position.x, position.y };
    sprite->rotationDeg = RAD2DEG * b2Atan2(rot.s, rot.c);
}