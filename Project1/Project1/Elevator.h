#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "requests.h"
#include <ctime>

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

	//Default constructor
	Elevator();

	//Constructor that creates an elevator with 'n' floors
	Elevator(int _floors);

	//void getUpQ();
	//void getDownQ();

	
	void Add(requests req);


	int findNext();
	void move(int floor, vector<requests> newR);

	//Takes in a vector of the new requests and calls the add function to add them to their respective direction's queue
	//Calls sort on all the queues to make sure they are in order of shortest distance
	void update(vector<requests> reqs);

	
	void sortR(vector<requests>& v1);
	void sortOB(vector<requests>& v1);

	void simulation(int times);
};
