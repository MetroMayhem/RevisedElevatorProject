#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main() {

	int floors = 10;

	Elevator elevator = Elevator(floors);
	
	/*requests r1 = requests(7, 3, 0);
	requests r2 = requests(4, 6, 1);
	requests r3 = requests(5, 6, 1);
	requests r4 = requests(4, 1, 0);
	requests r5 = requests(8, 5, 0);
	requests r6 = requests(1, 4, 1);
	requests r7 = requests(6, 4, 0);
	requests r8 = requests(9, 5, 0);
	requests r9 = requests(2, 8, 1);*/
	
	//
	//vector<requests> vec = { r1, r2, r3, r4, r5, r6, r7 };

	//elevator.move(0, vec);
	//vec.clear();
	//elevator.move(elevator.findNext(), vec);
	//vec = { r8, r9 };
	//elevator.move(elevator.findNext(), vec);
	
	elevator.simulation(3);

	cin.get();

}