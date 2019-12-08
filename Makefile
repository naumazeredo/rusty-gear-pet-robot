EXE=gear
SRC=gear.c

all: gear.c
	gcc $(SRC) -o $(EXE) -lbcm2835

run: all
	sudo ./$(EXE)
