PROJECT_NAME=virtualcar
CC=gcc

SOURCES = src/include/lib.h src/include/lib.c src/include/colors.h src/virtualcar.c

all:
	$(CC) -pthread $(SOURCES) -o $(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME) *.o
