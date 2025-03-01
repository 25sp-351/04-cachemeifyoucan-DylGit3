#include "policy_b_cache.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cut_list.h"

static CacheNode cache[CACHE_SIZE];
static int cache_count = 0;

void move_to_front(int index) {
    CacheNode temp = cache[index];
    for (int i = index; i > 0; i--) {
        cache[i] = cache[i - 1];
    }
    cache[0] = temp;
}

CutList* cache_lookup(int rod_length) {
    for (int i = 0; i < cache_count; i++) {
        if (cache[i].rod_length == rod_length) {
            move_to_front(i);
            return cache[0].result;
        }
    }
    return NULL;
}

void cache_insert(int rod_length, CutList* result) {
    if (cache_count == CACHE_SIZE) {
        free(cache[0].result);
        for (int i = 0; i < cache_count - 1; i++) {
            cache[i] = cache[i + 1];
        }
        cache_count--;
    }
    
    cache[cache_count].rod_length = rod_length;
    cache[cache_count].result = copy_cutlist(result);
    cache_count++;
}

void cache_clear() {
    for (int i = 0; i < cache_count; i++) {
        free(cache[i].result);
    }
    memset(cache, 0, sizeof(cache));
    cache_count = 0;
}
