#ifndef CUT_LIST_H
#define CUT_LIST_H

#include "piece_values.h"
#include "vec.h"

typedef struct group {
    PieceLengthValue plv;
    int count;
} GroupedPieces;

typedef struct cut_list {
    Vec groups;
    PieceLength remainder;
    PieceValue value;
} CutList;

CutList* new_cutlist(PieceLength piecelength);
CutList* best_cut_list(CutList* cut_list, Vec value_list);
CutList* optimal_cutlist(Vec value_list, PieceLength rod_length);
CutList* add_cutlist_piece(CutList* cut_list, PieceLengthValue plv);
void cutlist_print(CutList* cut_list, int initial_rod_length);
void cutlist_free(CutList* cut_list);

#endif
