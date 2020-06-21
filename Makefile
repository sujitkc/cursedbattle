BIN = bin
MODEL = src/model
INC = src/utils
CPPFLAGS = -fpermissive
all :
	make $(BIN)/vessel.o
	make $(BIN)/board.o

$(BIN)/vessel.o : $(MODEL)/vessel.cpp $(MODEL)/vessel.h
	g++ -c $(MODEL)/vessel.cpp -o $@ -I$(INC) $(CPPFLAGS)

$(BIN)/board.o : $(MODEL)/board.cpp $(MODEL)/board.h
	g++ -c $(MODEL)/board.cpp -o $@ -I$(INC) $(CPPFLAGS)
