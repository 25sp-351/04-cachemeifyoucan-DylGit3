#ifndef POLICY_A_CACHE_H
#define POLICY_A_CACHE_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "cut_list.h"

#define CACHE_SIZE 100

typedef int KeyType;

typedef CutList* ValueType;

typedef ValueType (*ProviderFunction)(KeyType key);

typedef struct CacheEntry {
    int rod_length;
    ValueType result;
} CacheEntry;

void move_to_front(int index);
ProviderFunction set_provider(ProviderFunction downstream);
ValueType cache_lookup(int rod_length);
void cache_insert(int rod_length, ValueType result);
void cache_clear();

#endif
