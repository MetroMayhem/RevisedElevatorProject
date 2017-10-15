#include "Elevator.h"



Elevator::Elevator() { 
	floors.push_back(0);
	curr = floors.begin();
	dir = 1;
}

Elevator::Elevator(int _floors) {
	for (int i = 0; i < _floors; i++)
		floors.push_back(i);
	curr = floors.begin();
	dir = 1;
}

Elevator::~Elevator()
{
}

void Elevator::getUpQ()
{
	for (vector<requests>::iterator itr = upQ.begin(); itr != upQ.end(); itr++)
		cout << *itr;
}

void Elevator::getDownQ()
{
	for (vector<requests>::iterator itr = downQ.begin(); itr != downQ.end(); itr++)
		cout << *itr;
}

void Elevator::Add(requests req) {
	//Function takes into consideration where in the queue the request needs to be based on where the elevator is
	//as well as where the request is coming from
	//O(n) worst case time complexity

	vector<requests>::iterator iter;
	if (req.direction == 1) {					//If the request is for the up direction
		if (upQ.empty())						//If Queue is empty push in request
			upQ.push_back(req);
		else {
			for (iter = upQ.begin(); iter != upQ.end(); iter++) {				//Iterate through the up 'queue'
				if ( abs(iter->curr - *curr) > abs(req.curr - *curr) ) {		//If the difference between the iter request and the elevator is > than the new request and the elevator
					upQ.insert(iter, req);										//Put the new request before the iter request
					break;
				}
				else if (abs(iter->curr - *curr) == abs(req.curr - *curr)) {	//If the two requests are the same distance away from the elevator
					if (req.curr > *curr) {										//If the new request is above the elevator insert the new request before the iter request
						upQ.insert(iter, req);									//Otherwise gets put behind iter request
						break;
					}
				}
				else if (++iter == upQ.end()) {					//If the current iter is the last request in the queue, push the new request to the back
					upQ.push_back(req);
					break;
				}
				iter--;
			}
		}			//The logic for up and down requests are relatively the same, but with slightly different conditions for if the
	}				//distance between the requests and elevator is the same
	else {
		if (downQ.empty())
			downQ.push_back(req);
		else {
			for (iter = downQ.begin(); iter != downQ.end(); iter++) {
				if (abs(iter->curr - *curr) > abs(req.curr - *curr)) {
					downQ.insert(iter, req);
					break;
				}
				else if (abs(iter->curr - *curr) == abs(req.curr - *curr)) {
					if (req.curr < *curr) {
						downQ.insert(iter, req);
						break;
					}
				}
				else if (++iter == downQ.end()) {
					downQ.push_back(req);
					break;
				}
				iter--;
			}
		}
	}

	//OLD ADD FUNCTION. MAY REVERT BACK LATER
	/*if (req.direction == 1) {					//If the request is for the up direction
		if (upQ.empty())						//If the 'queue' is empty
			upQ.push_back(req);

		else if (req.curr < *curr && dir == 1) {			//If the new request's current floor is less than the elevator's current floor (if elevator is moving up)
			for (iter = upQ.end(); iter != upQ.begin(); iter--) {		//Iterate backwards through the up 'queue'
				if (iter->curr > *curr)						//If the request in the queue's current floor is > the elevator's current floor
					upQ.push_back(req);				//Put the new request at the end of the Queue
				else if (iter->curr < req.curr) {			//If the request in the queue's current floor is < the new request's current floor
					upQ.insert(--iter, req);		//Insert the new request after the iterator's request
					break;
				}
			}
		}
		else {			//If the new request's current floor is greater than the elevator's current floor ************* check up until the "turning point"
			for (iter = upQ.begin(); iter != upQ.end(); iter++) {		//Iterate forward through the queue
				if (iter->curr > req.curr) {		//If the request in the queue's current floor is greater than the new request's current floor
					upQ.insert(iter, req);		//Insert the new request before the iterator's request
					break;
				}
				else if (++iter == upQ.end()) {		//If you've checked every part of the queue, push the new request to the back
					upQ.push_back(req);
					break;
				}
				else if (iter->curr < req.curr && iter->curr < upQ[0].curr) {		//LOGIC FOR IF YOU REACH THE 'NEXT UP' VALUES      NOT TESTED YET
					upQ.insert(iter, req);
					break;
				}
				iter--;
			}		//The logic for adding to the down queue is relatively similar, but with different conditions
		}			//Since it considers floors in the oposite manner as the up queue
	}
	else {
		if (downQ.empty())
			downQ.push_back(req);

		else if (req.curr > *curr && dir == 0) {
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
				else if (++iter == downQ.end()) {
					downQ.push_back(req);
					break;
				}
				else if (iter->curr > req.curr && iter->curr > downQ[0].curr) {		//LOGIC FOR IF YOU REACH THE 'NEXT UP' VALUES      NOT TESTED YET
					upQ.insert(iter, req);
					break;
				}
				iter--;
			}
		}
	}
*/	
}

void Elevator::Gtfo() {
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
	vector<requests>::iterator iter;

	if (upQ[0] < downQ[0]) {
		next.push_back(upQ[0]);

	}
	
}

void Elevator::move(int floor)
{

}

void Elevator::update(vector<requests> reqs) {

}