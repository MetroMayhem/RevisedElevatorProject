#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main() {

	int floors = 10;

	Elevator elevator = Elevator(floors);
	
	requests r1 = requests(2, 3, 1, 0);
	requests r2 = requests(4, 6, 1, 0);
	requests r3 = requests(5, 6, 1, 0);
	requests r4 = requests(4, 1, 0, 0);
	requests r5 = requests(8, 5, 0, 0);
	
	elevator.Add(r1);
	elevator.Add(r2);
	elevator.Add(r3);
	elevator.Add(r4);
	elevator.Add(r5);

	elevator.getUpQ();
	elevator.getDownQ();

	/*for (int i = 0; i < 10; i++) {
		int curr = rand() % floors + 1;
		int dest = rand() % floors + 1;
		bool direction = (dest > curr);

		requests request = requests(curr, dest, direction, 0);

		elevator.Add(request);



		cout << request;
		
	}
	elevator.findNext();
	*/

	cin.get();
}