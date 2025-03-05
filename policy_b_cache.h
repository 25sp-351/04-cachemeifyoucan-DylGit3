#ifndef POLICY_B_CACHE_H
#define POLICY_B_CACHE_H

#include <dlfcn.h>

#include "cut_list.h"

#define CACHE_SIZE 100

typedef CutList* ValueType;

typedef ValueType (*ProviderFunction)(Vec value_list, PieceLength rod_length);

typedef struct CacheEntry {
    int rod_length;
    CutList* result;
} CacheEntry;

ProviderFunction set_provider(ProviderFunction downstream);
void cache_load(void);
CutList* cache_lookup(Vec value_list, PieceLength rod_length);
void cache_insert(PieceLength rod_length, CutList* result);
void cache_clear();

#endif
