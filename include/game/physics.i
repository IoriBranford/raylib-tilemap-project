%module physics
%{
#include <game/physics.h>
%}

%nodefaultctor;
%nodefaultdtor;

struct b2BodyId {};
%rename(Body) L_NewBody;

%inline %{
    b2BodyId L_NewBody(float x, float y, float rotationRad) {
        return NewBody((Vector2){x, y}, rotationRad);
    }
%}
%extend b2BodyId {
    void SetLinearVelocity(float velX, float velY) {
        b2Body_SetLinearVelocity(*$self, (b2Vec2){velX, velY});
    }
    void Destroy() {
        if (b2Body_IsValid(*$self)) {
            b2DestroyBody(*$self);
        }
        *$self = b2_nullBodyId;
    }
    ~b2BodyId() {
        if (b2Body_IsValid(*$self)) {
            b2DestroyBody(*$self);
        }
        *$self = b2_nullBodyId;
    }
}
