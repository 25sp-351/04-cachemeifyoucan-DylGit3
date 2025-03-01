#ifndef POLICY_B_CACHE_H
#define POLICY_B_CACHE_H

#include "cut_list.h"

#define CACHE_SIZE 100

typedef struct CacheNode {
    int rod_length;
    CutList* result;
} CacheNode;

CutList* cache_lookup(int rod_length);
void cache_insert(int rod_length, CutList* result);
void cache_clear();

#endif
