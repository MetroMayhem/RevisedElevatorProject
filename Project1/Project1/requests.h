#pragma once

struct requests {
	int curr;
	int dest;
	bool direction;
	bool pickedUp;

	requests(int _curr, int _dest, bool _direction, bool _pickedUp) :
		curr(_curr), dest(_dest), direction(_direction), pickedUp(_pickedUp) {}


};