#include "cut_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "piece_values.h"
#include "vec.h"
#include "policy_a_cache.h"
#include "policy_b_cache.h"

CutList* new_cutlist(PieceLength piecelength) {
    CutList* new_cl   = malloc(sizeof(CutList));
    new_cl->groups    = new_vec(sizeof(GroupedPieces));
    new_cl->remainder = piecelength;
    new_cl->value     = 0;
    return new_cl;
}

CutList* copy_cutlist(CutList* cut_list) {
    CutList* new_cl   = malloc(sizeof(CutList));
    new_cl->groups    = vec_copy(cut_list->groups);
    new_cl->remainder = cut_list->remainder;
    new_cl->value     = cut_list->value;
    return new_cl;
}

void cutlist_free(CutList* cut_list) {
    vec_free(cut_list->groups);
    free(cut_list);
}

CutList* add_cutlist_piece(CutList* cut_list, PieceLengthValue plv) {
    GroupedPieces* groups = vec_items(cut_list->groups);
    cut_list->remainder -= plv.length;
    cut_list->value += plv.value;

    for (size_t ix = 0; ix < cut_list->groups->length; ++ix) {
        if (pvs_equal(&groups[ix].plv, &plv)) {
            ++groups[ix].count;
            return cut_list;
        }
    }

    GroupedPieces new_group = {.plv = plv, .count = 1};
    vec_add(cut_list->groups, &new_group);

    return cut_list;
}

CutList* best_cut_list(CutList* starting_cut_list, Vec pieces_vec) {
    CutList* best_option = copy_cutlist(starting_cut_list);

    for (PieceLengthValue* try_length = vec_items(pieces_vec);
         try_length->length != 0; ++try_length) {
        if (!(try_length->length <= starting_cut_list->remainder))
            continue;

        CutList* potential_option = best_cut_list(
            add_cutlist_piece(copy_cutlist(starting_cut_list), *try_length),
            pieces_vec);

        if (potential_option->value > best_option->value) {
            if (best_option)
                cutlist_free(best_option);
            best_option = potential_option;
            continue;
        }
        cutlist_free(potential_option);
    }

    cutlist_free(starting_cut_list);
    return best_option;
}

CutList* optimal_cutlist(Vec value_list, PieceLength rod_length) {
    CutList* cached_result = cache_lookup(rod_length);
    if (cached_result != NULL)
        return cached_result;

    CutList* result = best_cut_list(new_cutlist(rod_length), value_list);

    cache_insert(rod_length, result);

    return result;
}

void cutlist_print(CutList* cut_list, int initial_rod_length) {
    printf("{\n\'input_length\' : %d\n", initial_rod_length);
    printf("\'value\' : %d\n", cut_list->value);
    printf("\'remainder\' : %d\n", cut_list->remainder);
    printf("\'cuts\' : [\n");
    GroupedPieces* groups = vec_items(cut_list->groups);
    for (size_t index = 0; index < cut_list->groups->length; ++index) {
        if (index > 0)
            printf("\n");
        printf(
            "{ \'length\' : %d, \'count\' : %d,\n\'piece_value\' : %d, "
            "\'value\' : %d}",
            groups[index].plv.length, groups[index].count,
            groups[index].plv.value,
            groups[index].count * groups[index].plv.value);
    }
    printf("\n] }\n");
}
