#ifndef TICTACTOE
#define TICTACTOE

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "move.hpp"
#include "button.hpp"
#include <vector>
#include <utility>
#include <iostream>
#include <time.h>
#include <string>



template<typename T, typename B>
class tictactoe{
private:
	sf::RenderWindow & display;
	T game1;
	int current_player_nmb = 1;
	std::vector<move<B*>> movelist;
	time_t pause = time(0);
	
public:
	tictactoe(sf::RenderWindow & window,  std::pair<float, float> pos_begin = std::pair<float, float>(0,0), std::pair<float, float> pos_end = std::pair<float, float>(100,100)):
		display(window),
		game1(T(display, pos_begin, pos_end))
	{}
	//update the game, save move and check if undo button was pressed
	void update(){
		B* temp = static_cast<B*>(game1.update(current_player_nmb));
		move<B*> new_move = temp;
		if ( new_move != NULL) {
			current_player_nmb *= -1;
			movelist.push_back(new_move);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			undo();
		}
	}
	//check for text input and show current state
	void text_update() {
		update();
		print();
		while (true) {
			try {
				std::string x_loc = "-1";
				std::string y_loc = "-1";
				while (std::stoi(x_loc) < 0 || std::stoi(x_loc) > 3 && std::stoi(y_loc) < 0 || std::stoi(y_loc) > 3) {
					std::cout << "enter x: ";
					std::cin >> x_loc;
					std::cout << "enter y: ";
					std::cin >> y_loc;
					if (y_loc == "z" || x_loc == "z") { undo(); return; }
				}
				B* temp = static_cast<B*>(game1.set_winner(current_player_nmb, std::pair<int, int>(std::stoi(x_loc), std::stoi(y_loc))));
				movelist.push_back(move<B*>(temp));
				current_player_nmb *= -1;
				return;
			}
			catch(std::exception invalid_argument){}
		}
	}
	//shows current state of board in console
	void print() {
		game1.print(std::cout);
	}
	//get winner of entire game
	int get_winner() {
		return game1.get_winner();
	}
	//uses undo on last move, has a delay to prevent a lot of undo's in one click
	void undo() {
		if (!movelist.empty() && time(0)-pause > 0.1) {
			pause = time(0);
			movelist.back().undo();
			movelist.pop_back();
			current_player_nmb *= -1;
		}
	}
	//simple draw for game
	void draw() {
		game1.draw();
	}
};

#endif