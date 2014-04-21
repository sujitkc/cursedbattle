BIN = ../../bin
MODEL = ../model
VIEW = ../view
CONTROLLER = .
UTILS = ../utils

INC = -I$(MODEL) -I$(UTILS) -I$(VIEW)
CPPFLAGS = -fpermissive

$(BIN)/controller.a : $(BIN)/game.o $(BIN)/user.o
	ar rcs $@ $(BIN)/game.o $(BIN)/user.o 

$(BIN)/game.o : game.cpp game.h $(MODEL)/vessel.h $(VIEW)/guiboard.h
	g++ -c game.cpp -o $@ $(INC) $(CPPFLAGS)

$(BIN)/user.o : user.cpp user.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/gui.h $(VIEW)/guiboard.h $(MODEL)/vessel.h
	g++ -c user.cpp -o $@ $(INC) $(CPPFLAGS)

clean:
	rm $(BIN)/game.o
	rm $(BIN)/user.o
	rm $(BIN)/controller.a
