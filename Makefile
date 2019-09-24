CC=gcc
CFLAGS= -Wall -Werror -O0
OTHER_C_FLAGS=-Wall -Werror -O3 
LIBDIRS=-L/usr/lib64/atlas
LIBS=-lsatlas

all: tema2_blas tema2_neopt tema2_opt_m tema2_opt_f

tema2_blas: solver_blas.c main.c
	$(CC) $(CFLAGS) $^ $(LIBDIRS) $(LIBS) -lm -o $@

tema2_neopt: solver_neopt.c main.c
	$(CC) $(CFLAGS) $^ -lm -o $@

tema2_opt_m: solver_opt.c main.c
	$(CC) $(CFLAGS) $^ -lm -o $@

tema2_opt_f: solver_neopt.c main.c
	$(CC) $(OTHER_C_FLAGS) $^ -lm -o $@

clean:
	rm -rf tema2_blas tema2_neopt tema2_opt_m tema2_opt_f
