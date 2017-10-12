#include "Elevator.h"



Elevator::Elevator()
{
	list<int> floors;
	list<int>::iterator curr = floors.begin();
	vector<requests> upQ;
	vector<requests> downQ;
	vector<requests>::iterator req;

}


Elevator::~Elevator()
{
}

void Elevator::Add(requests req) {

}

void Elevator::Gtfo()
{
	if (upQ[0].dest == *curr)
		upQ.erase(upQ.begin());
	if (upQ[0].dest == *curr)
		upQ.erase(upQ.begin());

}

int Elevator::findNext()
{
	return 0;
}

void Elevator::move(int floor)
{
}
