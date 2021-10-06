CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: tsp

tsp: tsp.o 
	$(CC) -o tsp tsp.o set.o path.o stack.o graph.o dfs.o

tsp.o: 
	$(CC) $(CFLAGS) -c tsp.c set.c path.c stack.c graph.c dfs.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f tsp tsp.o set.o path.o stack.o graph.o dfs.o

scan-build: clean
	scan-build make
