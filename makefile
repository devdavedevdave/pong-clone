# Define the compiler
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -g $(shell sdl2-config --cflags)

# Define any libraries to link into the executable:
LIBS=$(shell sdl2-config --libs) -lSDL2_ttf

# Define any directories containing header files other than /usr/include
INCLUDES=-Iinclude

# Define the C source files
SOURCES=$(wildcard src/*.c)

# Define the C object files 
OBJECTS=$(SOURCES:.c=.o)

# Define the executable file 
MAIN=main

.PHONY: clean

all: $(MAIN)
	@echo Simple compiler named mycc has been compiled

$(MAIN): $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) src/*.o *~ $(MAIN)
