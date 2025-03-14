#ifndef CACHE_H
#define CACHE_H

#include "cut_list.h"
#include "vec.h"

typedef CutList* ValueType;

typedef ValueType (*ProviderFunction)(Vec value_list, PieceLength rod_length);

void cache_clear();
ProviderFunction set_provider(ProviderFunction downstream);

#endif
