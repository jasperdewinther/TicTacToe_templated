#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <utility>
#include "move.hpp"

class button{
private:
	//used for drawing shapes
	sf::RectangleShape noplayer = sf::RectangleShape();
	sf::RectangleShape done_square = sf::RectangleShape();
	sf::CircleShape player_one = sf::CircleShape();
	sf::VertexArray player_negative1 = (sf::VertexArray(sf::Lines, 2));
	sf::VertexArray player_negative2 = (sf::VertexArray(sf::Lines, 2));
	//window
	sf::RenderWindow & display_window;
	//state
	int winning_player = 0;

public:
	button(sf::RenderWindow & window, std::pair<float, float> begin = std::pair<float, float>(0, 0), std::pair<float, float> end = std::pair<float, float>(0, 0));
	//draw state according to winning_player
	void draw();
	//set position
	void set_begin_end(std::pair<float, float> begin, std::pair<float, float> end);
	//check if button was pressed and returns a pointer to this object
	void* update(const int & player_nmb);
	//reset player number to 0
	void undo();
	//get for winning_player, named this way to work with the game template
	int get_winner();
	//set winning player, returns pointer to this object
	void* set_winner(const int & player_nmb);
};

#endif