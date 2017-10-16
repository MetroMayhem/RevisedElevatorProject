#pragma once

struct requests {
	int curr;
	int dest;
	bool direction;

	requests() : curr(0), dest(0), direction(0) {}

	requests(int _curr, int _dest, bool _direction, bool _pickedUp) :
		curr(_curr), dest(_dest), direction(_direction) {}

	 friend std::ostream& operator<<(std::ostream& cout, requests _req) {
		cout << "Current floor: " << _req.curr << std::endl;
		cout << "Destination floor: " << _req.dest << std::endl;
		cout << "Direction desired: " << _req.direction << std::endl;
		cout << std::endl;
		return cout;
	}


};