#include "Interface.h"

bool Frame::contains(float x, float y) {
	if ((x > _frame.getPosition().x && x < (_frame.getPosition().x + _frame.getSize().x))
		&& (y > _frame.getPosition().y && y < (_frame.getPosition().y + _frame.getSize().y))) {
		return true;
	}
	return false;
}
