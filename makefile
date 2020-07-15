CC=gcc
CFLAGS= -O3 -Wall
CLIBS=-lm -lgsl -lgslcblas

# -Wall: all warnings
# -w : no warnings

elliptic: elliptic-3.c
	@echo "LD_LIBRARY_PATH=/usr/local/lib"
	@echo "export LD_LIBRARY_PATH"
	$(CC) $(CFLAGS) $^ $(CLIBS)

vectors: vectorization-random.c
	$(CC) $^ -lm
	time -p ./a.out
	@echo ""
	$(CC) -O3 $^ -lm
	time -p ./a.out
	@echo ""
	$(CC) -fopenmp $^ -lm
	time -p ./a.out
	@echo ""
	$(CC) -O3 -fopenmp $^ -lm
	time -p ./a.out
	@echo ""

cholesky: cross-cholesky.c
	$(CC) $(CFLAGS) $^ $(CLIBS)

cross: cross-correlation.c
	$(CC) $(CFLAGS) $^ $(CLIBS)

clean:
	rm *.dat *.out

## random.exe : generates random numbers, test for the GSL RNG
random.exe: random.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

## invert.exe : inverts a matrix, then exponentiates it, with GSL functions
invert.exe: invert.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)	

## exp.exe : GSL matrix exponential
exp.exe: exp.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

## wald.exe : Rejection sampling to generate RNG from Wald distribution
wald.exe: wald.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

.PHONY : help
help : makefile
	@sed -n 's/^##//p' $<
