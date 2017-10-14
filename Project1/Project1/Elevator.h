#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "requests.h"

using namespace std;

class Elevator {
private:
	list<int> floors;
	list<int>::iterator curr = floors.begin();
	vector<requests> upQ;
	vector<requests> downQ;
	vector<requests>::iterator req;

	bool dir;

public:
	Elevator();
	Elevator(list<int> _floors);
	~Elevator();
	void Add(requests req);
	void Gtfo();
	int findNext();
	void move(int floor);

};
