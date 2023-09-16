build:
	gcc -Wall -std=c99 ./src/*.c ./src/snakeGame/*.c -lSDL2 -o snake
run:
	./snake
clean:
	rm snake