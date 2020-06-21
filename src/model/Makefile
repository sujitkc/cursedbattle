BIN        = ../../bin
MODEL      = .
VIEW       = ../view
CONTROLLER = ../controller
UTIL       = ../utils
INC        = -I$(MODEL) -I$(VIEW) -I$(CONTROLLER) -I$(UTIL)

CPPFLAGS   = -fpermissive
$(BIN)/model.a : $(BIN)/vessel.o $(BIN)/board.o $(BIN)/modelexceptions.o
	ar rcs $@ $(BIN)/vessel.o $(BIN)/board.o $(BIN)/modelexceptions.o

$(BIN)/vessel.o : vessel.cpp vessel.h $(UTIL)/position.h modelexceptions.h
	g++ -c vessel.cpp -o $@ -I$(INC) $(CPPFLAGS)

$(BIN)/board.o : board.cpp board.h modelexceptions.h
	g++ -c board.cpp -o $@ -I$(INC) $(CPPFLAGS)

board.h :  $(UTIL)/position.h vessel.h $(UTIL)/exception.h
	touch board.h

$(BIN)/modelexceptions.o : modelexceptions.cpp modelexceptions.h
	g++ -c modelexceptions.cpp -o $@ $(INC)

modelexceptions.h : $(UTIL)/exception.h
	touch modelexceptions.h

clean:
	rm $(BIN)/model.a
	rm $(BIN)/vessel.o
	rm $(BIN)/board.o
	rm $(BIN)/modelexceptions.o
