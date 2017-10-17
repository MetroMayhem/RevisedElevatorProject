#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void simulation(int times, vector<Elevator> elevators);
int optimalQ(requests req, vector<Elevator> Elevators);

int main() {

	int floors = 10;

	Elevator e1 = Elevator(floors);
	Elevator e2 = Elevator(floors);
	Elevator e3 = Elevator(floors);

	vector<Elevator> elevators = { e1};
	simulation(10, elevators);

	cin.get();

}

//The basic simulation function that takes in the number of times to run the simulation
//and the vector of elevators to run the program on (from 1 to 3 elevators).
//For each iteration of the simulation, it creates random requests to add to the elevator queues.
//After the final iteration of the for loop, when the elevator is full of people, it runs through
//and makes sure it drops off all the passengers.
//Time complexity in the absolute worst case is infinite, if the two random numbers generated are 
//ALWAYS the same, which is unlikely.
//Plausible worst case is O(n^3) because the conditions equal to approcimately T(n) = n^2 * n * size * n^2
//Best case is O(n)


void simulation(int times, vector<Elevator> elevators) {
	srand((unsigned int)time(NULL));
	vector<vector<requests>> newRequests(elevators.size());

	requests temp;
	for (int i = 0; i < times; i++) {
		for (int itr = 0; itr < elevators.size(); itr++)
			newRequests[itr].clear();
		for (int j = 0; j < (rand() % 4); j++) {
			do {
				temp.curr = (rand() % elevators[0].getSize());
				temp.dest = (rand() % elevators[0].getSize());
			} while (temp.curr == temp.dest);
			if (temp.curr < temp.dest)
				temp.direction = 1;
			else
				temp.direction = 0;
			newRequests[optimalQ(temp, elevators)].push_back(temp);
		}

		if (i == 0)
			for (int k = 0; k < elevators.size(); k++) {
				elevators[k].move(0, newRequests[k]);
			}
		else
			for (int k = 0; k < elevators.size(); k++) {
				elevators[k].move(elevators[k].findNext(), newRequests[k]);
			}
		
	}
	for (int itr = 0; itr < elevators.size(); itr++)
		newRequests[itr].clear();
	switch (elevators.size()) {
	case 1:
		while (!elevators[0].isEmpty())
			elevators[0].move(elevators[0].findNext(), newRequests[0]);
		break;
	case 2:
		while (!elevators[0].isEmpty() || !elevators[1].isEmpty()) {
			elevators[0].move(elevators[0].findNext(), newRequests[0]);
			elevators[1].move(elevators[1].findNext(), newRequests[1]);
		}
		break;
	case 3:
		while (!elevators[0].isEmpty() || !elevators[1].isEmpty() || !elevators[2].isEmpty()) {
			elevators[0].move(elevators[0].findNext(), newRequests[0]);
			elevators[1].move(elevators[1].findNext(), newRequests[1]);
			elevators[2].move(elevators[2].findNext(), newRequests[2]);
		}
		break;
	}
	
	return;
}


int optimalQ(requests req, vector<Elevator> Elevators) {
	switch (Elevators.size()) {
	case 1:
		return 0;
	case 2:
		if (Elevators[0].findNext() == -1)
			return 0;
		else if (Elevators[1].findNext() == -1)
			return 1;
		else {
			if (abs(req.curr - Elevators[0].findNext()) < abs(req.curr - Elevators[1].findNext()))
				return 0;
			else
				return 1;
		}
	case 3:
		if (Elevators[0].findNext() == -1)
			return 0;
		else if (Elevators[1].findNext() == -1)
			return 1;
		else if (Elevators[2].findNext() == -1)
			return 2;
		else {
			if ((abs(req.curr - Elevators[0].findNext()) < abs(req.curr - Elevators[1].findNext()))
				&& ((abs(req.curr - Elevators[0].findNext()) < abs(req.curr - Elevators[2].findNext()))))
				return 0;
			else if ((abs(req.curr - Elevators[1].findNext()) < abs(req.curr - Elevators[0].findNext()))
				&& ((abs(req.curr - Elevators[1].findNext()) < abs(req.curr - Elevators[2].findNext()))))
				return 1;
			else
				return 2;
		}
	}

}
