CC = gcc
CFLAGS = -Wall -Wextra

OBJS = cut_list.o piece_values.o rodcut.o vec.o

all: rodcut_a rodcut_b

rodcut_a: $(OBJS) policy_a_cache.o
	$(CC) $(CFLAGS) -o rodcut_a $(OBJS) policy_a_cache.o

rodcut_b: $(OBJS) policy_b_cache.o
	$(CC) $(CFLAGS) -o rodcut_b $(OBJS) policy_b_cache.o

policy_a_cache.o: cut_list.h cache.h

policy_b_cache.o: cut_list.h cache.h

cut_list.o: piece_values.h vec.h

clean:
	rm -f *.o rodcut_a rodcut_b