#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main() {

	list<int> floors;
	for (int i = 1; i < 101; i++)
		floors.push_back(i);

	Elevator elevator = Elevator(floors);
	
	
	for (int i = 0; i < 10; i++) {
		int curr = rand() % 100 + 1;
		int dest = rand() % 100 + 1;
		bool direction = rand() % 2;

		requests request = requests(curr, dest, direction, 0);

		elevator.Add(request);

		cout << request;
	}
	cin.get();
}