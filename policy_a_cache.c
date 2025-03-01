#include "policy_a_cache.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cut_list.h"

static CacheEntry cache[CACHE_SIZE];
static int cache_count = 0;

void move_to_front(int index) {
    CacheEntry temp_cut = cache[index];
    for (int ix = index; ix > 0; ix--)
        cache[ix] = cache[ix - 1];
    cache[0] = temp_cut;
}

CutList* cache_lookup(int rod_length) {
    for (int ix = 0; ix < cache_count; ++ix) {
        if (cache[ix].rod_length == rod_length) {
            move_to_front(ix);
            return cache[0].result;
        }
    }
    return NULL;
}

void cache_insert(int rod_length, CutList* result) {
    if (cache_count == CACHE_SIZE)
        cache_count--;

    for (int ix = cache_count; ix > 0; --ix)
        cache[ix] = cache[ix - 1];

    cache[0].rod_length = rod_length;
    cache[0].result     = copy_cutlist(result);

    ++cache_count;
}

void cache_clear() {
    for (int ix = 0; ix < cache_count; ++ix)
        free(cache[ix].result);
    memset(cache, 0, sizeof(cache));
    cache_count = 0;
}
