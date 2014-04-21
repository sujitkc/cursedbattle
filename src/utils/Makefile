BIN        = ../../bin
MODEL      = ../model
VIEW       = ../view
CONTROLLER = ../controller
INC        = -I$(MODEL) -I$(VIEW) -I$(CONTROLLER) -I$(UTIL)

CPPFLAGS   = -fpermissive

$(BIN)/utils.a : $(BIN)/position.o
	ar rcs $(BIN)/utils.a $(BIN)/position.o

$(BIN)/position.o : position.cpp position.h
	g++ -c position.cpp -o $@ -I$(INC) $(CPPFLAGS)

clean :
	rm $(BIN)/utils.a
	rm $(BIN)/position.o
