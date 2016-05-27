target : derivative.o matrix.o
	 gcc matrix.c derivative.c -Wall -o matrix -lm -g
parse.o : matrix.c
	 gcc matrix.c header.h -c -g
bayes.o : derivative.c
	 gcc derivative.c header.h -c -lm -g
clean:
	rm -rf *.o target
