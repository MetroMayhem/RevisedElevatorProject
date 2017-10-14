#pragma once

struct requests {
	int curr;
	int dest;
	bool direction;
	bool pickedUp;

	requests(int _curr, int _dest, bool _direction, bool _pickedUp) :
		curr(_curr), dest(_dest), direction(_direction), pickedUp(_pickedUp) {}

	 friend std::ostream& operator<<(std::ostream& cout, requests _req) {
		cout << "Current floor: " << _req.curr << std::endl;
		cout << "Destination floor: " << _req.dest << std::endl;
		cout << "Direction desired: " << _req.direction << std::endl;
		cout << "Picked up status: " << _req.pickedUp << std::endl;
		cout << std::endl;
		return cout;
	}


};