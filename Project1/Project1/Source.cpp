#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main() {

	int floors = 10;

	Elevator elevator = Elevator(floors);
	
	requests r1 = requests(7, 3, 1, 0);
	requests r2 = requests(4, 6, 1, 0);
	requests r3 = requests(5, 6, 1, 0);
	requests r4 = requests(4, 1, 0, 0);
	requests r5 = requests(8, 5, 0, 0);
	requests r6 = requests(1, 4, 1, 0);
	requests r7 = requests(6, 4, 0, 0);
	
	vector<requests> vec = { r1, r2, r3, r4, r5, r6, r7 };

	elevator.update(vec);

	/*
	elevator.Add(r1);
	elevator.Add(r2);
	elevator.Add(r3);
	elevator.Add(r4);
	elevator.Add(r5);
	elevator.Add(r6);
	*/


	//elevator.getUpQ();
	//elevator.getDownQ();

	/*for (int i = 0; i < 10; i++) {
		int curr = rand() % floors + 1;
		int dest = rand() % floors + 1;
		bool direction = (dest > curr);

		requests request = requests(curr, dest, direction, 0);

		elevator.Add(request);



		cout << request;
		
	}
	*/
	for (int i = 0; i < 10; i++) {
		cout << elevator.findNext();
	}
	
	

	cin.get();
}