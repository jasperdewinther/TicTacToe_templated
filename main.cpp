#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "button.hpp"
#include "tictactoe.hpp"
#include <iostream>
#include <chrono>
#include <thread>

//shown at the end of the game, press the close button, enter or escape to exit the program
void winning_message(const int & player_nmb, sf::RenderWindow & window) {
	if (player_nmb == 1) {
		std::cout << "\ncircle won!";
	}
	if (player_nmb == -1) {
		std::cout << "\ncross won!";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	while (true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { return; }
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}
//used for 3x3, 9x9 and 27x27(27x27 is not recommended)
template<typename T>
void graphic_gameloop(T & game1, sf::RenderWindow & window) {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (game1.get_winner() != 0) {
			winning_message(game1.get_winner(), window);
			return;
		}

		game1.update();
		window.clear();
		game1.draw();
		window.display();
	}
}
//text based only works for simple 3x3
void text_gameloop(tictactoe<game<button, sf::RenderWindow>, button> & game1, sf::RenderWindow & window) {
	window.setPosition(sf::Vector2i(0, 0));
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (game1.get_winner() != 0) {
			winning_message(game1.get_winner(), window);
			return;
		}
		window.clear();
		game1.draw();
		window.display();
		game1.text_update();
	}
}
//the further i went the more i regretted doing this templated but i couldnt stop at that point
int main(){
	std::cout << "select mode(0, 1 or 2):";
	int mode;
	std::cin >> mode;
	if (mode == 2) {
		std::cout << "Win a miniature game of tictactoe to get the the tile";
	}
	if (mode == 0) {
		std::cout << "Type coordinates between 0 and 2, type z in one of the fields to undo a turn";
	}
	
	const int resolution = 500;
	sf::RenderWindow window(sf::VideoMode(resolution, resolution), "tic-tac-toe");
	//3x3 game
	auto game1 = tictactoe<game<button, sf::RenderWindow>, button>(window, std::pair<float, float>(0.0, 0.0), std::pair<float, float>(resolution, resolution));
	//9x9
	auto game2 = tictactoe<game<game<button, sf::RenderWindow>, sf::RenderWindow>, button>(window, std::pair<float, float>(0.0, 0.0), std::pair<float, float>(resolution, resolution));
	//can make 27x27 but this is not recommended

	if (mode == 1) {
		graphic_gameloop<decltype(game1)>(game1, window);
	}
	else if (mode == 2) {
		graphic_gameloop<decltype(game2)>(game2, window);
	}
	else if (mode == 0) {
		text_gameloop(game1, window);
	}
	window.close();
	return 0;
}