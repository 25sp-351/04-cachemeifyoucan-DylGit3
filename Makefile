CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = rodcut.c cut_list.c piece_values.c vec.c
HDR = cut_list.h piece_values.h vec.h policy_a_cache.h policy_b_cache.h

OBJ = $(SRC:.c=.o)

OBJ_A = $(OBJ) policy_a_cache.o
OBJ_B = $(OBJ) policy_b_cache.o

# Separate compilation flags for each policy
CFLAGS_A = $(CFLAGS) -DUSE_POLICY_A
CFLAGS_B = $(CFLAGS) -DUSE_POLICY_B

all: rodcut_a rodcut_b

rodcut_a: $(OBJ_A)
	$(CC) $(CFLAGS_A) -o rodcut_a $(OBJ_A)

rodcut_b: $(OBJ_B)
	$(CC) $(CFLAGS_B) -o rodcut_b $(OBJ_B)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

policy_a_cache.o: policy_a_cache.c policy_a_cache.h
	$(CC) $(CFLAGS) -c policy_a_cache.c -o policy_a_cache.o

policy_b_cache.o: policy_b_cache.c policy_b_cache.h
	$(CC) $(CFLAGS) -c policy_b_cache.c -o policy_b_cache.o

clean:
	rm -f *.o rodcut_a rodcut_b
