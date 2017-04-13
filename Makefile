PROJECT_NAME=virtualcar
CC=gcc

SOURCES = src/virtualcar.c 

all:
	$(CC) $(SOURCES) -o $(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME) *.o
