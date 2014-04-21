BIN        = ../bin
MODEL      = model
VIEW       = view
CONTROLLER = controller
UTIL       = utils
INC        = -I$(MODEL) -I$(VIEW) -I$(CONTROLLER) -I$(UTIL)
CPPFLAGS=-g -fpermissive

all :
	make -C $(MODEL)
	make -C $(VIEW)
	make -C $(CONTROLLER)
	make -C $(UTIL)
	make $(BIN)/main.o
	make $(BIN)/battleship

$(BIN)/battleship :  $(BIN)/main.o $(BIN)/controller.a $(BIN)/utils.a $(BIN)/model.a $(BIN)/view.a
	g++ -o $(BIN)/battleship $(BIN)/main.o $(BIN)/controller.a $(BIN)/utils.a $(BIN)/model.a $(BIN)/view.a -lcurses

$(BIN)/main.o: main.cpp $(CONTROLLER)/game.h
	g++ -o $@ -c main.cpp $(CPPFLAGS) $(INC)

clean:
	make -C $(MODEL) $@
	make -C $(VIEW) $@
	make -C $(CONTROLLER) $@
	make -C $(UTIL) $@
	rm $(BIN)/main.o
	rm $(BIN)/battleship
