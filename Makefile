CC = gcc

OBJECTS = main.o board.o
PROGRAM = muehle

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROGRAM)

%.o: %.c
	$(CC) -c $<

clean:
	rm $(OBJECTS) $(PROGRAM)
