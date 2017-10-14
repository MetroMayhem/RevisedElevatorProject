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

Elevator::Elevator(list<int> _floors)
{
	list<int> floors = _floors;
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
	//Function takes into consideration where in the queue the request needs to be based on where the elevator is
	//as well as where the request is coming from
	//O(n) worst case time complexity

	vector<requests>::iterator iter;
	if (dir == 1) {					//If elevator is moving in up direction
		if (req.curr < *curr) {			//If the new request's current floor is less than the elevator's current floor
			for (iter = upQ.end(); iter != upQ.begin(); iter--) {		//Iterate backwards through the up 'queue'
				if (iter->curr > *curr)						//If the request in the queue's current floor is > the elevator's current floor
					upQ.push_back(req);				//Put the new request at the end of the Queue
				else if (iter->curr < req.curr) {			//If the request in the queue's current floor is < the new request's current floor
					upQ.insert(--iter, req);		//Insert the new request after the iterator's request
					break;
				}
			}
		}
		else {			//If the new request's current floor is greater than the elevator's current floor
			for (iter = upQ.begin(); iter != upQ.end(); iter++) {		//Iterate forward through the queue
				if (iter->curr > req.curr) {		//If the request in the queue's current floor is greater than the new request's current floor
					upQ.insert(iter, req);		//Insert the new request before the iterator's request
					break;
				}
			}		//The logic for adding to the down queue is relatively similar, but with different conditions
		}			//Since it considers floors in the oposite manner as the up queue
	}
	else {
		if (req.curr > *curr) {
			for (iter = downQ.end(); iter != downQ.begin(); iter--) {
				if (iter->curr < *curr)
					downQ.push_back(req);
				else if (iter->curr > req.curr) {
					downQ.insert(--iter, req);
					break;
				}
			}
		}
		else {
			for (iter = downQ.begin(); iter != downQ.end(); iter++) {
				if (iter->curr < req.curr) {
					downQ.insert(iter, req);
					break;
				}
			}
		}
	}
	
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
	if (dir == 1) {
		return upQ[0].dest;
	}
	else if (dir == 0) {
		return downQ[0].dest;
	}
}

void Elevator::move(int floor)
{
}
