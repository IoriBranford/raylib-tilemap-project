#ifndef A5613A39_7304_4AFC_91F5_5476D15F4288
#define A5613A39_7304_4AFC_91F5_5476D15F4288

#include <stddef.h>
#include <stdlib.h>

#define pool_alloc malloc
#define pool_free free

#define pool_struct(T, PT) struct PT { T* objects; T** pointers; size_t used; size_t size; }
#define pool_typedef(T, PT) typedef pool_struct(T, PT) PT;

#define pool_foreachall(pool, func) \
{ for (size_t n = pool->size, i = 0; n; --n, ++i) { func(pool->pointers[i]); } }

#define pool_foreachused(pool, func) \
{ for (size_t n = pool->used, i = 0; n; --n, ++i) { func(pool->pointers[i]); } }

#define pool_revforeachall(pool, func) \
{ for (size_t n = pool->size; n; --n) { func(pool->pointers[n-1]); } }

#define pool_revforeachused(pool, func) \
{ for (size_t n = pool->used; n; --n) { func(pool->pointers[n-1]); } }

#define init_pool(T, pool, size) { \
    pool->objects = pool_alloc(size*sizeof(T)); \
    pool->pointers = pool_alloc(size*sizeof(T*)); \
    pool->used = 0; \
    pool->size = size; \
}

#define pool_ctor(T, PT, ctor) \
PT* ctor(size_t size) { \
    PT* pool = pool_alloc(sizeof(PT)); \
    init_pool(T, pool, size) \
    return pool; \
}

#define free_pool(pool) { \
    pool_free(pool->pointers); \
    pool_free(pool->objects); \
    pool_free(pool); \
}

#define take_from_pool(pool) (pool->used >= pool->size ? NULL : pool->pointers[pool->used++])

#define prune_pool(pool, objused) { \
    size_t i = pool->used; \
    if (i) do { \
        if (objused(pool->pointers[--i])) continue; \
        --pool->used; \
        void *o = pool->pointers[i]; \
        pool->pointers[i] = pool->pointers[pool->used]; \
        pool->pointers[pool->used] = o; \
    } while (i); \
}

#define trim_pool_end(pool, objused) { \
    size_t i = pool->used; if (i) while (!objused(pool->pointers[--i])) --pool->used; }

#define sort_pool_used(pool, compare) qsort(pool->pointers, pool->used, sizeof(void*), compare)

#endif /* A5613A39_7304_4AFC_91F5_5476D15F4288 */
