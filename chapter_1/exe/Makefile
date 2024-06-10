# makefile for chapter 1
CC = g++
CFLAGS = -Wall -g -O1
SRC = ../src
OBJECT = $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*.cpp))
# LIB = -lm
LIB = 

.PHONY: all clean
all: app_exe

app_exe: $(OBJECT)
	$(CC) $(CFLAGS) -o app_exe $(OBJECT) $(LIB)

%.o: %.cpp
	$(CC) $(CFLAGS) -c "$<" -o "$@"

clean:
	rm app_exe $(OBJECT)