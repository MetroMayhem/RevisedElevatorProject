#include "Elevator.h"



Elevator::Elevator()
{
	list<int> floors;
	list<int>::iterator curr = floors.begin();
	vector<requests> upQ;
	vector<requests> downQ;
	vector<requests>::iterator req;
	bool dir;

}


Elevator::~Elevator()
{
}

void Elevator::Add(requests req) {

}

void Elevator::Gtfo()
{
	if (dir == 1) {
		if (upQ[0].dest == *curr)
			upQ.erase(upQ.begin());
	}
	else if (dir == 0) {
		if (downQ[0].dest == *curr)
			downQ.erase(downQ.begin());
	}

}

int Elevator::findNext()
{
	return 0;
}

void Elevator::move(int floor)
{
}
