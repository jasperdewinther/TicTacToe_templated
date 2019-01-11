/*#include "game.hpp"

template<typename T, typename W>
game<T,W>::game(std::pair<float, float> pos_begin, std::pair<float, float> pos_end, W  & window):
	begin(pos_begin),
	end(pos_end),
	display_window(window)
{
	recalulate_size();
}
template<typename T, typename W>
game<T,W>::game() {
	begin = std::pair<float, float>(0,0);
	end = std::pair<float, float>(0,0);
}

template<typename T, typename W>
void game<T,W>::recalulate_size() {
	int y_index = 0;
	for (auto & y_axis : winconditions) {
		int x_index = 0;
		for (auto& x_axis : y_axis) {
			x_axis.set_size_pos(std::pair<float, float>(((end.first-begin.first)*x_index)+begin.first, ((end.second - begin.second)*y_index) + begin.second), std::pair<float, float>(((end.first - begin.first)*(x_index+1)) + begin.first, ((end.second - begin.second)*(y_index+1)) + begin.second));
			x_index++;
		}
		y_index++;
	}
}

template<typename T, typename W>
void game<T,W>::set_size_pos(std::pair<float, float> pos_begin, std::pair<float, float> pos_end) {
	begin = pos_begin;
	end = pos_end;
	recalulate_size();
}

template<typename T, typename W>
void game<T,W>::draw() {
	for (auto & y_axis : winconditions) {
		for (auto& x_axis : y_axis) {
			x_axis.draw();
		}
	}
}*/