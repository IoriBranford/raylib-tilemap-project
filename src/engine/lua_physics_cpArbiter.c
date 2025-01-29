#include "lua_physics.h"

class_index_and_newindex(cpArbiter)
class_getterf_and_setterf(cpArbiter, *, number, Restitution, cpArbiterGetRestitution, cpArbiterSetRestitution)
class_getterf_and_setterf(cpArbiter, *, number, Friction, cpArbiterGetFriction, cpArbiterSetFriction)
class_getterf_and_setterf_vec2(cpArbiter, *, cpVect, SurfaceVelocity, cpArbiterGetSurfaceVelocity, cpArbiterSetSurfaceVelocity)

/// "This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback."
// class_getterf_vec2(cpArbiter, *, cpVect, TotalImpulse, cpArbiterTotalImpulse)
// class_getterf_vec2(cpArbiter, *, cpVect, KE, cpArbiterTotalKE)

class_func_0_2ud(cpArbiter, *, GetShapes, cpArbiterGetShapes, cpShape, *, cpShape, *)
class_func_0_2ud(cpArbiter, *, GetBodies, cpArbiterGetBodies, cpBody, *, cpBody, *)

// TODO? ContactPoints

class_getterf(cpArbiter, *, boolean, IsFirstContact, cpArbiterIsFirstContact)
class_getterf(cpArbiter, *, boolean, IsRemoval, cpArbiterIsRemoval)
class_getterf(cpArbiter, *, integer, NumContactPoints, cpArbiterGetCount)
class_getterf_vec2(cpArbiter, *, cpVect, Normal, cpArbiterGetNormal)
class_func_1_vec2(cpArbiter, *, GetPointA, cpArbiterGetPointA, integer, cpVect)
class_func_1_vec2(cpArbiter, *, GetPointB, cpArbiterGetPointB, integer, cpVect)
class_func_1_1(cpArbiter, *, GetDepth, cpArbiterGetDepth, integer, number)

class_luaopen(cpArbiter,
    class_method_reg(cpArbiter, __index),
    class_method_reg(cpArbiter, __newindex),
    class_getter_and_setter_reg(cpArbiter, Restitution),
    class_getter_and_setter_reg(cpArbiter, Friction),
    class_getter_and_setter_reg(cpArbiter, SurfaceVelocity),
    class_method_reg(cpArbiter, GetShapes),
    class_method_reg(cpArbiter, GetBodies),
    class_getter_reg(cpArbiter, IsFirstContact),
    class_getter_reg(cpArbiter, IsRemoval),
    class_getter_reg(cpArbiter, NumContactPoints),
    class_getter_reg(cpArbiter, Normal),
    class_method_reg(cpArbiter, GetPointA),
    class_method_reg(cpArbiter, GetPointB),
    class_method_reg(cpArbiter, GetDepth))