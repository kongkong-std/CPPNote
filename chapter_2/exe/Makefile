# makefile for chapter 2
CXX = g++
CFLAGS = -Wall -g -O3 -std=c++11
SRC = ../src
OBJECT = $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*.cpp))
# LIB = -lm
LIB_PATH =
LIB_FLAG = -lm
LIB = $(LIB_PATH) $(LIB_FLAG)

.PHONY: all clean
all: app_exe

app_exe: $(OBJECT)
	$(CXX) $(CFLAGS) -o app_exe $(OBJECT) $(LIB)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c "$<" -o "$@"

clean:
	rm -f app_exe $(OBJECT)