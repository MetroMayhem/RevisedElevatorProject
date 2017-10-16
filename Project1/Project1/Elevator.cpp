#include "Elevator.h"


Elevator::Elevator() {
	//Default constructor
	floors.push_back(0);
	curr = floors.begin();
	dir = 1;
}

Elevator::Elevator(int _floors) {
	//Constructor to create 'building' that elevator moves through
	for (int i = 0; i < _floors; i++)
		floors.push_back(i);
	curr = floors.begin();
	dir = 1;
}

//Getters for request queues
//void Elevator::getUpQ() {
//	
//	for (vector<requests>::iterator itr = upQ.begin(); itr != upQ.end(); itr++)
//		cout << *itr;
//}
//
//void Elevator::getDownQ()
//{
//	for (vector<requests>::iterator itr = downQ.begin(); itr != downQ.end(); itr++)
//		cout << *itr;
//}

void Elevator::Add(requests req) {
	//Function takes into consideration which queue the request needs to be in based on where the request is coming from
	//O(1) time complexity
	if (req.direction)
		upQ.push_back(req);
	else
		downQ.push_back(req);
}

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
		}
		else
			return onBoard[0].dest;
	}
}

void Elevator::move(int floor, vector<requests> newR){
	//Function takes in a floor number and moves the elevator to that floor
	//When the elevator moves, each request gets seconds added on to its wait length (ASSUMPTION: Wait time based on elevator traveling 1 floor per 5 seconds)
	//After the elevator moves, each queue is checked to see what requests get on/off and removes them from their respected queues
	//Finally the system is updated (see update function)
	//Time Complexity: Best Case O(1) Average Case O(n) Worst Case O(n^2)
			//Best Case: If all queues are empty or if you do not move floors, then nothing needs to be checked or re sorted
			//Average Case: Usually, the queues will

	if (floor != -1) {			//
		for (vector<requests>::iterator itr = upQ.begin(); itr != upQ.end(); itr++)
			itr->waitTime += abs((floor - *curr)) * 5;
		for (vector<requests>::iterator itr = downQ.begin(); itr != downQ.end(); itr++)
			itr->waitTime += abs((floor - *curr)) * 5;

		curr += (floor - *curr);
		 
	}
	
	while (!onBoard.empty() && onBoard[0].dest == *curr)
		onBoard.erase(onBoard.begin());

	while (!upQ.empty() && upQ[0].curr == *curr) {
		onBoard.push_back(upQ[0]);
		cout << upQ[0].curr << " to " << upQ[0].dest << " waited " << upQ[0].waitTime << " seconds before getting on the elevator\n\n";
		upQ.erase(upQ.begin());
	}

	while (!downQ.empty() && downQ[0].curr == *curr) {
		onBoard.push_back(downQ[0]);
		cout << downQ[0].curr << " to " << downQ[0].dest << " waited " << downQ[0].waitTime << " seconds before getting on the elevator\n\n";
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

void Elevator::simulation(int times) {
	srand( (unsigned int) time(NULL));
	vector<requests> sim;
	requests temp;
	for (int i = 0; i < times; i++) {
		sim.clear();
		for (int j = 0; j < (rand() % 4); j++) {
			do {
				temp.curr = (rand() % floors.size());
				temp.dest = (rand() % floors.size());
			} while (temp.curr == temp.dest);
			if (temp.curr < temp.dest)
				temp.direction = 1;
			else
				temp.direction = 0;
			sim.push_back(temp);
		}
		if (i == 0)
			move(0, sim);
		else
			move(findNext(), sim);
	}
	sim.clear();

	while ((!upQ.empty() || !downQ.empty()) || !onBoard.empty()) {
		move(findNext(), sim);
	}
}
