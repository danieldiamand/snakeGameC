build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o snake
run:
	./snake
clean:
	rm snake