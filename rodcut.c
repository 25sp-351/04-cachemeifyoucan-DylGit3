#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "cache.h"
#include "cut_list.h"
#include "piece_values.h"
#include "vec.h"

#define LINE_LENGTH 256

void usage(char *program_name);
Vec read_values_from_file(const char *filename);
int prompt_for_rod_length();

int main(int argc, char *argv[]) {
    int quiet_mode = 0;
    char *filename = NULL;

    if (argc < 2) {
        usage(argv[0]);
    } else if (strcmp(argv[1], "-q") == 0) {
        quiet_mode = 1;
        if (argc < 3)
            usage(argv[0]);
        filename = argv[2];
    } else {
        filename = argv[1];
    }

    Vec value_list = read_values_from_file(filename);

    if (value_list == NULL) {
        fprintf(stderr,
                "Error: Unable to read any valid piece value from file %s.\n",
                filename);
        return 1;
    }

    int rod_length = 0;

    if (!quiet_mode) {
        rod_length = prompt_for_rod_length();
        if (rod_length < 1) {
            fprintf(stderr, "Error: Invalid rod length.\n");
            vec_free(value_list);
            return 1;
        }
    }

    ProviderFunction provider = optimal_cutlist;
    provider                  = set_provider(optimal_cutlist);

    CutList *cl               = provider(value_list, rod_length);
    cutlist_print(cl, rod_length);
    cutlist_free(cl);
    vec_free(value_list);
    cache_clear();

    return 0;
}

noreturn void usage(char *program_name) {
    fprintf(stderr, "Error in %s.\n", program_name);
    exit(1);
}

Vec read_values_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        fprintf(stderr, "Error opening file");
        return NULL;
    }

    Vec value_list = new_vec(sizeof(PieceLengthValue));
    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || isspace(line[0]))
            continue;

        PieceLengthValue item;
        if (sscanf(line, "%d, %d", &item.length, &item.value) != 2 ||
            item.length < 1 || item.value < 1) {
            fprintf(stderr, "Skipping invalid line: %s", line);
            continue;
        }

        vec_add(value_list, &item);
    }

    fclose(file);

    if (vec_length(value_list) == 0) {
        vec_free(value_list);
        return NULL;
    }

    return value_list;
}

int prompt_for_rod_length() {
    int rod_length = 0;
    char input[LINE_LENGTH];

    printf("Enter a rod length (integer > 0):\n");

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                printf("\nEOF detected. Using default rod length 0.\n");
                return 0;
            }
            printf("Input Error\n");
            continue;
        }

        if (sscanf(input, "%d", &rod_length) == 1 && rod_length > 0)
            return rod_length;

        printf("Invalid input. Please enter an integer larger than 0.\n");
    }
}
