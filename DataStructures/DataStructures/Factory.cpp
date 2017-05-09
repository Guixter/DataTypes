#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Factory.h"
#include "LinkedQueue.h"

#define CARTONS_SIZE 10		// The number of pieces in every box
#define FRAME_TIME 30		// The time of every frame, in seconds

using namespace std;

// The constructor
Factory::Factory()
{
	srand(time(NULL));
	machiningHeads = new LinkedQueue<int>();
	machiningSkirts = new LinkedQueue<int>();
	machiningShafts = new LinkedQueue<int>();
	assemblageHeads = new LinkedQueue<int>();
	assemblageSkirts = new LinkedQueue<int>();
	assemblageShafts = new LinkedQueue<int>();
	pistons = new LinkedQueue<int>();

	mh = new Machine(120, 1);
	mh->inputs[0] = machiningHeads;
	mh->output = assemblageHeads;
	msk = new Machine(180, 1);
	msk->inputs[0] = machiningSkirts;
	msk->output = assemblageSkirts;
	msh = new Machine(150, 1);
	msh->inputs[0] = machiningShafts;
	msh->output = assemblageShafts;
	mp = new Machine(60, 3);
	mp->inputs[0] = assemblageHeads;
	mp->inputs[1] = assemblageSkirts;
	mp->inputs[2] = assemblageShafts;
	mp->output = pistons;
}

// The destructor
Factory::~Factory()
{
	delete machiningHeads, machiningSkirts, machiningShafts;
	delete assemblageHeads, assemblageSkirts, assemblageShafts;
	delete pistons;
	delete mh, msk, msh, mp;
}

// Launch the process
void Factory::launch() {
	int nbFrames = 0;
	while (pistons->size() < 100) {
		SpawnBox();
		UpdateMachine(mh);
		UpdateMachine(msk);
		UpdateMachine(msh);
		UpdateMachine(mp);
		nbFrames++;
	}

	int tps = nbFrames * FRAME_TIME;
	int heures = tps / 3600;
	tps -= heures * 3600;
	int minutes = tps / 60;
	tps -= minutes * 60;

	cout << "The 100 pistons were assembled within " << heures << "h" << minutes << "m" << tps << "s." << endl;
	cout << "MH broke " << mh->nbBroken << " times." << endl;
	cout << "MSK broke " << msk->nbBroken << " times." << endl;
	cout << "MSH broke " << msh->nbBroken << " times." << endl;
	cout << "MP broke " << mp->nbBroken << " times."<< endl;
}

// Sort the pieces of a box
void Factory::SpawnBox() {
	for (int i = 0; i < CARTONS_SIZE; i++) {
		int random = rand() % 3;

		switch (random) {
		case 0:
			machiningHeads->add(0);
			break;
		case 1:
			machiningSkirts->add(0);
			break;
		case 2:
			machiningShafts->add(0);
			break;
		default:
			break;
		}
	}
}

// Update a machine
void Factory::UpdateMachine(Machine* machine) {
	if (machine->isBroken) {
		// The machine is broken : decrement the countdown until the machine is repaired
		machine->brokenCountdown -= FRAME_TIME;
		if (machine->brokenCountdown <= 0) {
			machine->isBroken = false;
		}
	} else {
		if (machine->isWorking) {
			// The machine is working on a piece
			machine->workingCountdown -= FRAME_TIME;
			if (machine->workingCountdown <= 0) {
				// The machine just ended its work
				machine->output->add(0);
				machine->workingCountdown = machine->workTime;
				machine->isWorking = false;

				// Handle the breakdown
				int random = rand() % 100;
				if (random < 25) {
					machine->isBroken = true;
					machine->brokenCountdown = ((rand() % 6) + 5) * 60;
					machine->nbBroken++;
				}
			}
		} else {
			// If all the inputs are ready, we can start a new work
			bool start = true;
			for (int i = 0; i < machine->nbInputs; i++) {
				if (machine->inputs[i]->empty()) {
					start = false;
					break;
				}
			}

			if (start) {
				// Remove an element in each input
				for (int i = 0; i < machine->nbInputs; i++) {
					machine->inputs[i]->remove();
				}
				machine->isWorking = true;
			}
		}
	}
}
