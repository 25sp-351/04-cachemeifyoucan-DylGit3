#ifndef POLICY_A_CACHE_H
#define POLICY_A_CACHE_H

#include <stdio.h>
#include <stdlib.h>

#include "cut_list.h"

#define CACHE_SIZE 100

typedef struct CacheEntry{
    int rod_length;
    CutList* result;
} CacheEntry;

CutList* cache_lookup(int rod_length);
void cache_insert(int rod_length, CutList* result);
void cache_clear();

#endif
