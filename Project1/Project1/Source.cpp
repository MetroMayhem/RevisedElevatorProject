#include "Elevator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void simulation(int times, vector<Elevator> elevators);
int optimalQ(requests req, vector<Elevator> Elevators);

int main() {

	int floors = 10;

	Elevator elevator = Elevator(floors);

	int test;

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

	//elevator.simulation(3);

	cin.get();

}

void simulation(int times, vector<Elevator> elevators) {
	srand((unsigned int)time(NULL));
	vector<vector<requests>> newRequests(elevators.size());

	requests temp;
	for (int i = 0; i < times; i++) {
		newRequests.clear();
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
		newRequests.clear();

		/*while ((!upQ.empty() || !downQ.empty()) || !onBoard.empty()) {
			move(findNext(), sim);
		}*/
	}
}


int optimalQ(requests req, vector<Elevator> Elevators) {
	switch (Elevators.size()) {
	case 1:
		return 0;
	case 2:
		if (abs(req.curr - Elevators[0].findNext()) < abs(req.curr - Elevators[1].findNext()))
			return 0;
		else
			return 1;
	case 3:
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
