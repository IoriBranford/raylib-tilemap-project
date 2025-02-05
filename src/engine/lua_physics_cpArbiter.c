#include "lua_physics.h"

lclass_index_and_newindex(cpArbiter)
lclass_getterf_and_setterf(cpArbiter, *, number, Restitution, cpArbiterGetRestitution, cpArbiterSetRestitution)
lclass_getterf_and_setterf(cpArbiter, *, number, Friction, cpArbiterGetFriction, cpArbiterSetFriction)
lclass_getterf_and_setterf_vec2(cpArbiter, *, cpVect, SurfaceVelocity, cpArbiterGetSurfaceVelocity, cpArbiterSetSurfaceVelocity)

/// "This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback."
// lclass_getterf_vec2(cpArbiter, *, cpVect, TotalImpulse, cpArbiterTotalImpulse)
// lclass_getterf_vec2(cpArbiter, *, cpVect, KE, cpArbiterTotalKE)

lclass_func_0_2ud(cpArbiter, *, GetShapes, cpArbiterGetShapes, cpShape, *, cpShape, *)
lclass_func_0_2ud(cpArbiter, *, GetBodies, cpArbiterGetBodies, cpBody, *, cpBody, *)

// TODO? ContactPoints

lclass_getterf(cpArbiter, *, boolean, IsFirstContact, cpArbiterIsFirstContact)
lclass_getterf(cpArbiter, *, boolean, IsRemoval, cpArbiterIsRemoval)
lclass_getterf(cpArbiter, *, integer, NumContactPoints, cpArbiterGetCount)
lclass_getterf_vec2(cpArbiter, *, cpVect, Normal, cpArbiterGetNormal)
lclass_func_1_vec2(cpArbiter, *, GetPointA, cpArbiterGetPointA, integer, cpVect)
lclass_func_1_vec2(cpArbiter, *, GetPointB, cpArbiterGetPointB, integer, cpVect)
lclass_func_1_1(cpArbiter, *, GetDepth, cpArbiterGetDepth, integer, number)

lclass_luaopen(cpArbiter,
    lclass_method_reg(cpArbiter, __index),
    lclass_method_reg(cpArbiter, __newindex),
    lclass_getter_and_setter_reg(cpArbiter, Restitution),
    lclass_getter_and_setter_reg(cpArbiter, Friction),
    lclass_getter_and_setter_reg(cpArbiter, SurfaceVelocity),
    lclass_method_reg(cpArbiter, GetShapes),
    lclass_method_reg(cpArbiter, GetBodies),
    lclass_getter_reg(cpArbiter, IsFirstContact),
    lclass_getter_reg(cpArbiter, IsRemoval),
    lclass_getter_reg(cpArbiter, NumContactPoints),
    lclass_getter_reg(cpArbiter, Normal),
    lclass_method_reg(cpArbiter, GetPointA),
    lclass_method_reg(cpArbiter, GetPointB),
    lclass_method_reg(cpArbiter, GetDepth))