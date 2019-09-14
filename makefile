CC=gcc
CFLAGS= -O3 -Wall
CLIBS=-lm -lgsl -lgslcblas

## random.exe : generates random numbers, test for the GSL RNG
random.exe: random.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

## invert.exe : inverts a matrix, then exponentiates it, with GSL functions
invert.exe: invert.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)	

## exp.exe : GSL matrix exponential
exp.exe: exp.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

.PHONY : help
help : makefile
	@sed -n 's/^##//p' $<

.PHONY : clean
clean :
	rm *.exe
