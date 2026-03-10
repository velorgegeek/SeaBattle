#include "Cell.h"
void Cell::upCountBlocked() {

	countBlocked++;
	if (countBlocked) {
		_status = Cell::status::blocked;
	}
}
void Cell::downCountBlocked() {
	if (countBlocked) {
		countBlocked--;
		if (!countBlocked) {
			_status = Cell::status::none;
		}
	}
}