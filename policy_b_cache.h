#ifndef POLICY_B_CACHE_H
#define POLICY_B_CACHE_H

#include <dlfcn.h>

#include "cut_list.h"

#define CACHE_SIZE 100

typedef int KeyType;

typedef CutList* ValueType;

typedef ValueType (*ProviderFunction)(KeyType key);

typedef struct CacheEntry {
    int rod_length;
    CutList* result;
} CacheEntry;

ProviderFunction set_provider(ProviderFunction downstream);
void cache_load(void);
CutList* cache_lookup(int rod_length);
void cache_insert(int rod_length, CutList* result);
void cache_clear();

#endif
