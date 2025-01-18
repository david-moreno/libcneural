NAME=testme
OBJ=cneural.o layer.o neuron.o error.o random.o graph.o main.o
CFLAGS=-Wall -DDEBUG
#CFLAGS=-Wall
CC=gcc $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

cneural.o: cneural.c cneural.h error.h
	$(CC) -c $<

layer.o: layer.c layer.h error.h
	$(CC) -c $<

neuron.o: neuron.c neuron.h error.h
	$(CC) -c $<


error.o: error.c error.h
	$(CC) -c $<

random.o: random.c random.h
	$(CC) -c $<

graph.o: graph.c graph.h
	$(CC) -c $<

main.o: main.c
	$(CC) -c $<

clean:
	rm -fv $(NAME) $(OBJ)
