SOURCES := main.cpp button.cpp
HEADERS := button.hpp game.hpp move.hpp tictactoe.hpp

build : $(SOURCES) $(HEADERS)
	gcc -std=gnu++17 $(SOURCES) -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ -o game

run : game
	./game

clean:
rm main.o button.o game.o tictactoe.o move.o game