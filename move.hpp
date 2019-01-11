#ifndef MOVE
#define MOVE

#include <memory>

template<typename T>
class move{
private:
	T undo_object;
public:
	move(T object):
		undo_object(object)
	{}
	void undo() {
		undo_object->undo();
	}
	bool operator!=(const T & rhs) {
		return undo_object != rhs;
	}
};

#endif