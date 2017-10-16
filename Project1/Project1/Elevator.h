#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "requests.h"

using namespace std;

class Elevator {
private:
	vector<int> floors;
	vector<int>::iterator curr;
	vector<requests> upQ;
	vector<requests> downQ;
	vector<requests> onBoard;

	bool dir;

public:
	Elevator();
	Elevator(int _floors);
	void getUpQ();
	void getDownQ();
	void Add(requests req);
	int findNext();
	void move(int floor, vector<requests> newR);
	void update(vector<requests> reqs);
	void sortR(vector<requests>& v1);
	void sortOB(vector<requests>& v1);

};
