#ifndef GAME
#define GAME

#include <utility>
#include <vector>
#include <iostream>
#include "move.hpp"

template<typename T, typename W>
class game{
private:
	std::pair<float, float> begin;
	std::pair<float, float> end;
	W & display_window;
	T winconditions[3][3] = {	{T(display_window),T(display_window),T(display_window)}, 
								{T(display_window),T(display_window),T(display_window)}, 
								{T(display_window),T(display_window),T(display_window)} };
	int winning_player = 0;
public:
	game(W & window, std::pair<float, float> pos_begin = std::pair<float, float>(0.0,0.0), std::pair<float, float> pos_end = std::pair<float, float>(0.0,0.0)) :
		begin(pos_begin),
		end(pos_end),
		display_window(window)
	{
		recalulate_size();
	}
	//set position of all children
	void recalulate_size() {
		int y_index = 0;
		for (auto & y_axis : winconditions) {
			int x_index = 0;
			for (auto& x_axis : y_axis) {
				x_axis.set_begin_end(std::pair<float, float>(((end.first - begin.first)/3*x_index) + begin.first, ((end.second - begin.second)/3*y_index) + begin.second), 
									std::pair<float, float>(((end.first - begin.first)/3*(x_index + 1)) + begin.first, ((end.second - begin.second)/3*(y_index + 1)) + begin.second));
				x_index++;
			}
			y_index++;
		}
	}
	//set the position of object
	void set_begin_end(std::pair<float, float> pos_begin, std::pair<float, float> pos_end) {
		begin = pos_begin;
		end = pos_end;
		recalulate_size();
	}
	//draw every child
	void draw() {
		for (auto & y_axis : winconditions) {
			for (auto& x_axis : y_axis) {
				x_axis.draw();
			}
		}
	}
	//check if anything is being pressed, disables buttons that are already won
	void* update(const int & player_nmb) {
		for (auto & y_axis : winconditions) {
			for (auto& x_axis : y_axis) {
				if (!x_axis.get_winner()) {
					void* checking = x_axis.update(player_nmb);
					if (checking != NULL) {
						return checking;
					}
				}
			}
		}
		return NULL;
	}
	//get th playernumber of winner of tile, also updates internal winner
	int get_winner() {
		winning_player = get_winner_calc();
		return winning_player;
	}
	int get_winner_calc() { 
		//get scores
		int score[3][3] = { {0,0,0},
							{0,0,0},
							{0,0,0} };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				score[i][j] = winconditions[i][j].get_winner();
			}
		}
		//horizontal check
		for (auto & x_axis : score) {
			int counter_temp = 0;
			for (auto & player_nmb : x_axis) {
				if (player_nmb == 1) {
					counter_temp++;
				}
				else if (player_nmb == -1) {
					counter_temp--;
				}
			}
			if (counter_temp == 3) { return 1; }
			if (counter_temp == -3) { return -1; }
		}
		//vertical check
		for (int i = 0; i < 3; i++) {
			if (score[0][i] == 1 && score[1][i] == 1 && score[2][i] == 1) { return 1; }
			if (score[0][i] == -1 && score[1][i] == -1 && score[2][i] == -1) { return -1; }
		}
		//diagonal checks
		if (score[0][0] == 1 && score[1][1] == 1 && score[2][2] == 1) { return 1; }
		if (score[0][0] == -1 && score[1][1] == -1 && score[2][2] == -1) { return -1; }
		if (score[2][0] == 1 && score[1][1] == 1 && score[0][2] == 1) { return 1; }
		if (score[2][0] == -1 && score[1][1] == -1 && score[0][2] == -1) { return -1; }
		return 0;
	}
	//used for assigning winner in text mode, only works in 3x3
	void* set_winner(const int & player_nmb, std::pair<int, int> location) {
		return winconditions[location.second][location.first].set_winner(player_nmb);
	}
	//used for printing in text mode
	void print(std::ostream & cout) {
		for (auto & x_axis : winconditions) {
			cout << "\n";
			for (auto & y_axis : x_axis) {
				cout << y_axis.get_winner() << ",";
			}
		}
		cout << "\n";
	}
};

#endif