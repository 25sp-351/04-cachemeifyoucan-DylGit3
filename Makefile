CC = gcc
CFLAGS = -Wall -Wextra

SRC = rodcut.c cut_list.c piece_values.c vec.c
HDR = cut_list.h piece_values.h vec.h policy_a_cache.h

OBJ = $(SRC:.c=.o) policy_a_cache.o

all: rodcut_a

rodcut_a: $(OBJ)
	$(CC) $(CFLAGS) -o rodcut_a $(OBJ)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

policy_a_cache.o: policy_a_cache.c policy_a_cache.h
	$(CC) $(CFLAGS) -c policy_a_cache.c -o policy_a_cache.o

clean:
	rm -f *.o rodcut_a

run: all
	./rodcut_a input.txt
