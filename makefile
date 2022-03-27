all: Interpolation.c
		gcc -Wall -o bin $^
clean:
		rm bin