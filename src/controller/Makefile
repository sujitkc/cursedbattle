BIN = ../../bin
MODEL = ../model
VIEW = ../view
CONTROLLER = .
UTILS = ../utils

INC = -I$(MODEL) -I$(UTILS) -I$(VIEW)
CPPFLAGS = -fpermissive

$(BIN)/controller.a : $(BIN)/game.o $(BIN)/user.o $(BIN)/cpu.o $(BIN)/basiccpu.o $(BIN)/smartcpu.o $(BIN)/player.o
	ar rcs $@ $(BIN)/game.o $(BIN)/user.o $(BIN)/cpu.o $(BIN)/smartcpu.o $(BIN)/basiccpu.o $(BIN)/player.o

$(BIN)/game.o : game.cpp game.h user.h cpu.h smartcpu.h basiccpu.h player.h $(MODEL)/vessel.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/guiboard.h $(VIEW)/gui.h $(UTILS)/position.h $(VIEW)/listpanel.h
	g++ -c game.cpp -o $@ $(INC) $(CPPFLAGS)

$(BIN)/user.o : user.cpp user.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/gui.h $(VIEW)/guiboard.h $(MODEL)/vessel.h
	g++ -c user.cpp -o $@ $(INC) $(CPPFLAGS)

$(BIN)/cpu.o : cpu.cpp cpu.h user.h $(UTILS)/position.h $(VIEW)/guiboard.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/gui.h $(MODEL)/vessel.h
	g++ -c cpu.cpp -o $@ $(INC) $(CPPFLAGS)

$(BIN)/smartcpu.o : smartcpu.cpp smartcpu.h cpu.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/gui.h $(VIEW)/guiboard.h $(MODEL)/vessel.h $(MODEL)/board.h $(UTILS)/segment.h $(UTILS)/position.h
	g++ -c smartcpu.cpp -o $@ $(INC) $(CPPFLAGS)

$(BIN)/basiccpu.o : basiccpu.cpp basiccpu.h cpu.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/gui.h $(VIEW)/guiboard.h $(MODEL)/vessel.h
	g++ -c basiccpu.cpp -o $@ $(INC) $(CPPFLAGS)

$(BIN)/player.o : player.cpp player.h user.h $(MODEL)/board.h $(VIEW)/keyboard.h $(VIEW)/gui.h $(VIEW)/guiboard.h $(MODEL)/vessel.h
	g++ -c player.cpp -o $@ $(INC) $(CPPFLAGS)

clean:
	rm $(BIN)/game.o
	rm $(BIN)/user.o
	rm $(BIN)/cpu.o
	rm $(BIN)/smartcpu.o
	rm $(BIN)/basiccpu.o
	rm $(BIN)/player.o
	rm $(BIN)/controller.a
