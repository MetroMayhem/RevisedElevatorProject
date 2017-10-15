#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "requests.h"

using namespace std;

class Elevator {
private:
	list<int> floors;
	list<int>::iterator curr;
	vector<requests> upQ;
	vector<requests> downQ;
	vector<requests> next;

	bool dir;

public:
	Elevator();
	Elevator(int _floors);
	~Elevator();
	void getUpQ();
	void getDownQ();
	void Add(requests req);
	void Gtfo();
	int findNext();
	void move(int floor);

};
