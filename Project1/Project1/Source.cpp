#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main() {

	int floors = 12;

	Elevator elevator = Elevator(floors);
	
	
	for (int i = 0; i < 10; i++) {
		int curr = rand() % floors + 1;
		int dest = rand() % floors + 1;
		bool direction = (dest > curr);

		requests request = requests(curr, dest, direction, 0);

		elevator.Add(request);

		//cout << request;
		
	}
	elevator.findNext();


	cin.get();
}