#include "button.hpp"
#include <iostream>



button::button(sf::RenderWindow & window, std::pair<float, float> begin, std::pair<float, float> end):
	display_window(window)
{
	noplayer.setSize(sf::Vector2f(end.first - begin.first - 2, end.second - begin.second - 2));
	noplayer.setPosition(sf::Vector2f(begin.first+1, begin.second+1));

	done_square.setSize(sf::Vector2f(end.first - begin.first - 2, end.second - begin.second - 2));
	done_square.setPosition(sf::Vector2f(begin.first + 1, begin.second + 1));
	done_square.setFillColor(sf::Color::Blue);

	player_one.setRadius((end.first-begin.first)/2);
	player_one.setPosition(sf::Vector2f(begin.first + 1, begin.second + 1));

	player_negative1[0].position = sf::Vector2f(begin.first, begin.second);
	player_negative1[1].position = sf::Vector2f(end.first, end.second);
	player_negative2[0].position = sf::Vector2f(end.first, begin.second);
	player_negative2[1].position = sf::Vector2f(begin.first, end.second);
}

void button::draw() {
	if (winning_player == 0) {
		display_window.draw(noplayer);
	}
	else if (winning_player == 1) {
		display_window.draw(player_one);
	}
	else if (winning_player == -1) {
		display_window.draw(player_negative1);
		display_window.draw(player_negative2);
	}
}

void button::set_begin_end(std::pair<float, float> begin, std::pair<float, float> end) {
	noplayer.setSize(sf::Vector2f(end.first - begin.first - 2, end.second - begin.second - 2));
	noplayer.setPosition(sf::Vector2f(begin.first, begin.second));

	player_one.setRadius((end.first - begin.first)/2);
	player_one.setPosition(sf::Vector2f(begin.first + 1, begin.second + 1));

	player_negative1[0].position = sf::Vector2f(begin.first, begin.second);
	player_negative1[1].position = sf::Vector2f(end.first, end.second);
	player_negative2[0].position = sf::Vector2f(end.first, begin.second);
	player_negative2[1].position = sf::Vector2f(begin.first, end.second);
}

void* button::update(const int & player_nmb) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && winning_player == 0) {
		if (noplayer.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(display_window)))) {
			winning_player = player_nmb;
			return (this);
		}
	}
	return NULL;
}
void button::undo() {
	winning_player = 0;
}

int button::get_winner() {
	return winning_player;
}

void* button::set_winner(const int & player_nmb) {
	winning_player = player_nmb;
	return (this);
}