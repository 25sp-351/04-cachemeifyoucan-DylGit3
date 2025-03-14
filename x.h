#ifndef POLICY_A_CACHE_H
#define POLICY_A_CACHE_H

#include "cache.h"
#include "cut_list.h"

#define CACHE_SIZE 100

typedef CutList* ValueType;

typedef ValueType (*ProviderFunction)(Vec value_list, PieceLength rod_length);

typedef struct CacheEntry {
    int rod_length;
    ValueType result;
} CacheEntry;

void move_to_front(PieceLength index);
ProviderFunction set_provider(ProviderFunction downstream);
ValueType cache_lookup(Vec value_list, PieceLength rod_length);
void cache_insert(PieceLength rod_length, ValueType result);
void cache_clear();
void cache_load(void);

#endif
