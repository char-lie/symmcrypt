SRC=main.cpp
BIN=main
CPP_FLAGS=-O3 -mtune=native -m64 -Wall
NTL_FLAGS=-I$(HOME)/sw/include -L$(HOME)/sw/lib -lntl -lm -L$(HOME)/sw/lib -lgf2x

all:
	g++  $(SRC) -o $(BIN) $(NTL_FLAGS) $(CPP_FLAGS)
