#ifndef PIECE_VALUES_H
#define PIECE_VALUES_H

#include <stdbool.h>

#include "vec.h"

typedef int PieceLength;
typedef int PieceValue;

typedef struct pv {
    PieceLength length;
    PieceValue value;
} PieceLengthValue;

Vec read_piece_values();
void print_piece_values(Vec ptr);
bool pvs_equal(PieceLengthValue *pv1, PieceLengthValue *pv2);

#endif
