//303 Project 1
//Elevator Simulator
//Kory Overbay, Alec Shern, Joel Knutson
//10-16-2017

#include "Elevator.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

void simulation(int times, vector<Elevator> elevators);
int optimalQ(requests req, vector<Elevator> Elevators);
int backMenu();

int main() {
	//LIGHTLY TESTED UI
	//Outputs how long requests are waiting for the elevator to pick them up
	vector<Elevator> elevators;
	bool simulating = 1;
	while (simulating) {
		elevators.clear();
		int floors = 0;
		int numE = 0;
		int times = 0;
		cout << "Elevator Simulator\n\n";
		while (floors < 1) {
			cout << "How many floors is your building? Please enter a positve integer > 0: ";
			cin >> floors;
		}
		while (numE < 1 || numE > 3) {
			cout << "\nHow many elevators would you like to be running? Please enter a positive integer between 1 and 3: ";
			cin >> numE;
		}
		while (times < 1) {
			cout << "\nHow many iterations would you like the simulation to run? Please enter a positve integer > 0: ";
			cin >> times;
		}
		for (int i = 0; i < numE; i++)
			elevators.push_back(floors);
		simulation(times, elevators);

		simulating = backMenu();
	}
}

void simulation(int times, vector<Elevator> elevators) {
	//The basic simulation function that takes in the number of times to run the simulation
	//and the vector of elevators to run the program on (from 1 to 3 elevators).
	//For each iteration of the simulation, it creates random requests to add to the elevator queues.
	//After the final iteration of the for loop, when the elevator is full of people, it runs through
	//and makes sure it drops off all the passengers.
	//Time complexity in the absolute worst case is infinite, if the two random numbers generated are 
	//ALWAYS the same, which is unlikely.
	//Plausible worst case is O(n^3) because the conditions equal to approcimately T(n) = times * elevator size * n^2
	//Best case is O(n)

	srand((unsigned int)time(NULL));	
	vector<vector<requests>> newRequests(elevators.size());		//A vector that holds vectors of requests that get put in th emove and update functions

	requests temp;
	for (int i = 0; i < times; i++) {
		for (int itr = 0; itr < elevators.size(); itr++)		//Clear out old requests
			newRequests[itr].clear();
		for (int j = 0; j < (rand() % 4); j++) {
			do {		
				temp.curr = (rand() % elevators[0].getSize());		//Create random "requests" to be added
				temp.dest = (rand() % elevators[0].getSize());
			} while (temp.curr == temp.dest);
			if (temp.curr < temp.dest)		//Add the request's direction
				temp.direction = 1;
			else
				temp.direction = 0;
			newRequests[optimalQ(temp, elevators)].push_back(temp);		//Add the request to the optimal queue
		}

		if (i == 0)			//Move the elevator
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
	switch (elevators.size()) {		//Clears out the rest of the passengers and drops them off when the iterations are done
	case 1:		//While the first elevator isn't empty...drop off passengers
		while (!elevators[0].isEmpty())
			elevators[0].move(elevators[0].findNext(), newRequests[0]);
		break;
	case 2:		//While elevator 1 or 2 aren't empty, drop off the passengers
		while (!elevators[0].isEmpty() || !elevators[1].isEmpty()) {
			elevators[0].move(elevators[0].findNext(), newRequests[0]);
			elevators[1].move(elevators[1].findNext(), newRequests[1]);
		}
		break;
	case 3:		//While any elevator isn't empty, drop off the passengers
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
	//FInds which elevator will be closest to the new request when the elevator processes new requests
	//Time complexity O(1) only checks if/else conditions
	switch (Elevators.size()) {
	case 1:		//If there is one elevator push the request to it
		return 0;
	case 2:		//If there are two elevators
		if (Elevators[0].findNext() == -1)	//If the first elevator has no floor to go to, give it the request
			return 0;
		else if (Elevators[1].findNext() == -1)			//If the second floor has no floor to go to, give it the request
			return 1;
		else {				//Find which of the two elevators will be closer to the new request and give it to that one
			if (abs(req.curr - Elevators[0].findNext()) < abs(req.curr - Elevators[1].findNext()))
				return 0;
			else
				return 1;
		}
	case 3:					//If there are three elevators....similar logic to two elevators, checks for 3rd elevators next
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

int backMenu() {            //Asks user if they want to go back to the menu. Takes multiple inputs.
	string input;
	cout << "\nWould you like to simulate again? (Yes/No) ";
	cin >> input;
	while (true) {
		if (input == "yes" || input == "Yes" || input == "YES" || input == "y" || input == "Y")
			return 1;
		else if (input == "no" || input == "No" || input == "NO" || input == "n" || input == "N")
			return 0;
		else {
			cout << "Please answer Yes or No: ";
			cin >> input;
			continue;
		}
	}
}