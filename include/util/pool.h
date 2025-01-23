#ifndef A5613A39_7304_4AFC_91F5_5476D15F4288
#define A5613A39_7304_4AFC_91F5_5476D15F4288

#include <stddef.h>
#include <stdlib.h>

#define pool_alloc malloc
#define pool_free free

#define pool_struct(T, PT) struct PT { T** active; size_t nActive; T* objects; size_t nObjects; }
#define pool_typedef(T, PT) typedef pool_struct(T, PT) PT;

#define pool_foreachall(pool, func) \
{ for (size_t n = pool->nObjects, i = 0; n; --n, ++i) { func(pool->active[i]); } }

#define pool_foreachactive(pool, func) \
{ for (size_t n = pool->nActive, i = 0; n; --n, ++i) { func(pool->active[i]); } }

#define pool_revforeachall(pool, func) \
{ for (size_t n = pool->nObjects; n; --n) { func(pool->active[n-1]); } }

#define pool_revforeachactive(pool, func) \
{ for (size_t n = pool->nActive; n; --n) { func(pool->active[n-1]); } }

#define init_pool(T, pool, size) { \
    pool->objects = pool_alloc(size*sizeof(T)); \
    pool->active = pool_alloc(size*sizeof(T*)); \
    for (size_t i = 0; i < size; ++i) pool->active[i] = &pool->objects[i]; \
    pool->nActive = 0; \
    pool->nObjects = size; \
}

#define count_free_pool_objs(pool) (pool->nObjects - pool->nActive)

#define pool_ctor(T, PT, ctor) \
PT* ctor(size_t size) { \
    PT* pool = pool_alloc(sizeof(PT)); \
    init_pool(T, pool, size) \
    return pool; \
}

#define pool_type(T, PT, ctor) pool_typedef(T, PT) pool_ctor(T, PT, ctor)

#define free_pool(pool) { \
    pool_free(pool->active); \
    pool_free(pool->objects); \
    pool_free(pool); \
}

#define take_from_pool(pool) (pool->nActive >= pool->nObjects ? NULL : pool->active[pool->nActive++])

#define prune_pool(pool, objactive) { \
    size_t i = pool->nActive; \
    if (i) do { \
        if (objactive(pool->active[--i])) continue; \
        --pool->nActive; \
        void *o = pool->active[i]; \
        pool->active[i] = pool->active[pool->nActive]; \
        pool->active[pool->nActive] = o; \
    } while (i); \
}

#define trim_pool_end(pool, objactive) { \
    size_t i = pool->nActive; if (i) while (!objactive(pool->active[--i])) --pool->nActive; }

#define sort_pool_active(pool, compare) qsort(pool->active, pool->nActive, sizeof(void*), compare)

#define is_from_pool(p) (pool->objects <= p && p < pool->objects + pool->nObjects)

#endif /* A5613A39_7304_4AFC_91F5_5476D15F4288 */
