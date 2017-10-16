#include "Elevator.h"
#include <algorithm>


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
	if (req.direction)
		upQ.push_back(req);
	else
		downQ.push_back(req);
}

	/*vector<requests>::iterator iter;
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
	if (req.direction == 1) {					//If the request is for the up direction
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

/*void Elevator::Gtfo() {
	if (dir == 1) {
		if (upQ[0].dest == *curr)
			upQ.erase(upQ.begin());
	}
	else if (dir == 0) {
		if (downQ[0].dest == *curr)
			downQ.erase(downQ.begin());
	}

}
*/
int Elevator::findNext() {
	//Function takes into consideration the distance between requests and destinations of people on and off the elevator
	//Finds the next floor that is closest to the elevator with people on board taking slight precedence to new requests
	//O(1) time complexity

	requests req;			//Temporary request

	if (upQ.empty() && downQ.empty() && onBoard.empty())	//If all queues are empty return -1 (don't move)
		return -1;
	else if (upQ.empty() && downQ.empty())				//If the request queues are empty, return the onBoard destination
		return (onBoard[0].dest);
	else if (upQ.empty())						//If upQ is empty make the temp request the next down request
		req = downQ[0];
	else if (downQ.empty())
		req = upQ[0];					//If downQ is empty make temp request the next up request


	if (!upQ.empty() && !downQ.empty()) {				//As long as both queues are not empty, compare requests
		if (abs(upQ[0].curr - *curr) < abs(downQ[0].curr - *curr))		//If the distance from the elevator to the up request is less than the down request
			req = upQ[0];											//temp request is next up request

		else if (abs(upQ[0].curr - *curr) == abs(downQ[0].curr - *curr)) {		//If both requests are the same distance away from the elevator
			if ((upQ[0].curr == downQ[0].curr))				//If the requests are for the same floor, return the floor
				req = upQ[0];
			else if (dir == 1) {					//If the requests are different floors and elevator is moving up
				if (upQ[0].curr > downQ[0].curr)	//Make the temp request the request that is above the elevator
					req = upQ[0];
				else
					req = downQ[0];
			}
			else {									//^^vice versa^^
				if (upQ[0].curr < downQ[0].curr)
					req = upQ[0];
				else
					req = downQ[0];
			}
		}
		else
			req = downQ[0];					//down request is closer than up request
	}

	if (onBoard.empty())			//If onBoard is empty return temp request
		return req.curr;
	else {
		if (abs(req.curr - *curr) < abs(onBoard[0].dest - *curr))		//Same logic for finding temp request
			return req.curr;

		else if (abs(req.curr - *curr) == abs(onBoard[0].dest - *curr)) {
			if (req.curr == onBoard[0].dest)
				return req.curr;
			else
				return onBoard[0].dest;			//If request and destination are not the same floor, person onBoard takes precedence
			/*else if (dir == 1) {
				if (req.curr > onBoard[0].dest)
					return req.curr;
				else
					return onBoard[0].dest;
			}
			else {
				if (req.curr < onBoard[0].dest)
					return req.curr;
				else
					return onBoard[0].dest;
			}
			*/
		}
		else
			return onBoard[0].dest;
	}
}

void Elevator::move(int floor, vector<requests> newR){

	if (floor == -1)
		return;

	curr += (floor - *curr);


	while (!onBoard.empty() && onBoard[0].dest == *curr) {
		onBoard.erase(onBoard.begin());
	}

	while (!upQ.empty() && upQ[0].curr == *curr) {
		onBoard.push_back(upQ[0]);
		upQ.erase(upQ.begin());
	}

	while (!downQ.empty() && downQ[0].curr == *curr) {
		onBoard.push_back(downQ[0]);
		downQ.erase(downQ.begin());
	}

	update(newR);

	return;



}

void Elevator::update(vector<requests> reqs) {
	
	for (vector<requests>::iterator itr = reqs.begin(); itr != reqs.end(); itr++) 
			Add(*itr);
		
	sortR(upQ);
	sortR(downQ);
	sortOB(onBoard);

}

void Elevator::sortR(vector<requests>& v1) {	//Selection sort for request queues
	if (v1.empty())
		return;

	for (vector<requests>::iterator iteri = (v1.begin() + 1); iteri != v1.end(); iteri++)
		for (vector<requests>::iterator iterj = iteri; iterj != v1.begin(); iterj--)
			if (abs(iterj->curr - *curr) < abs((iterj - 1)->curr - *curr))
				iter_swap(iterj, (iterj - 1));
}
void Elevator::sortOB(vector<requests>& v1) {		//Selection sort for onBoard queue
	if (v1.empty())
		return;

	for (vector<requests>::iterator iteri = (v1.begin() + 1); iteri != v1.end(); iteri++)
		for (vector<requests>::iterator iterj = iteri; iterj != v1.begin(); iterj--)
			if (abs(iterj->dest - *curr) < abs((iterj - 1)->dest - *curr))
				iter_swap(iterj, (iterj - 1));
}