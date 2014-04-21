MODEL = ../model
VIEW = .
CONTROLLER = ../controller
UTIL = ../utils
BIN = ../../bin
INC=-I$(MODEL) -I$(UTIL) -I$(CONTROLLER)
CFLAGS=-g -fpermissive

$(BIN)/view.a : $(BIN)/gui.o $(BIN)/keyboard.o $(BIN)/guiboard.o
	ar rcs $@ $(BIN)/gui.o $(BIN)/keyboard.o $(BIN)/guiboard.o

$(BIN)/gui.o : gui.cpp gui.h $(UTIL)/position.h keyboard.h
	g++ -o $@ $(CFLAGS) -c gui.cpp $(INC)

$(BIN)/guiboard.o : guiboard.cpp guiboard.h $(MODEL)/board.h $(MODEL)/vessel.h $(UTIL)/position.h $(MODEL)/modelexceptions.h
	g++ -o $@ $(CFLAGS) -c guiboard.cpp $(INC)

$(BIN)/keyboard.o : keyboard.cpp keyboard.h
	g++ -o $@ $(CFLAGS) -c keyboard.cpp $(INC)

clean :
	rm $(BIN)/gui.o
	rm $(BIN)/guiboard.o


