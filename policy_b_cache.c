#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "cut_list.h"

#define CACHE_SIZE 100

typedef struct CacheEntry {
    int rod_length;
    CutList* result;
} CacheEntry;

CacheEntry cache[CACHE_SIZE];
static int cache_count = 0;
static ProviderFunction downstream_provider;

void cache_insert(PieceLength rod_length, ValueType result);

void cache_load(void) {
    for (int ix = 0; ix < CACHE_SIZE; ++ix) {
        cache[ix].rod_length = -1;
        cache[ix].result     = NULL;
    }
}

CutList* cache_lookup(Vec value_list, PieceLength rod_length) {
    for (int ix = 0; ix < cache_count; ++ix)
        if (cache[ix].rod_length == rod_length)
            return cache[ix].result;

    ValueType output = (*downstream_provider)(value_list, rod_length);
    cache_insert(rod_length, output);
    return output;
}

void cache_insert(PieceLength rod_length, CutList* result) {
    if (cache_count == CACHE_SIZE) {
        free(cache[cache_count - 1].result);
        cache_count--;
    }

    cache[cache_count].rod_length = rod_length;
    cache[cache_count].result     = copy_cutlist(result);
    cache_count++;
}

void cache_clear() {
    for (int i = 0; i < cache_count; i++)
        free(cache[i].result);
    memset(cache, 0, sizeof(cache));
    cache_count = 0;
}

ProviderFunction set_provider(ProviderFunction downstream) {
    cache_load();
    fprintf(stderr, __FILE__ " set_provider()\n");
    downstream_provider = downstream;
    return cache_lookup;
}
