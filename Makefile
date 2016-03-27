PROJECT_NAME=vircar
CC=gcc

SOURCES = src/vircar.c

all:
	$(CC) $(SOURCES) -o $(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME) *.o
