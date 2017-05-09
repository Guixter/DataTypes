#pragma once
#include "Queue.h"

/*
 * A machine, which can work on inputs to make an output.
 */
struct Machine {
	int nbInputs;
	Queue<int>** inputs;
	Queue<int>* output;
	bool isWorking;
	bool isBroken;
	int nbBroken;

	int workTime;

	int workingCountdown;
	int brokenCountdown;

	Machine(int countdown, int inputs) :
											isWorking(false), isBroken(false), nbBroken(0),
											workTime(countdown), workingCountdown(0), brokenCountdown(0),
											nbInputs(inputs), output(NULL)
	{
		this->inputs = new Queue<int>*[inputs];
	}

	~Machine() {
		delete[] inputs;
	}
};

/*
 * A factory, which contains some queues and some machines to make pistons.
 */
class Factory
{
public:
	Factory();
	~Factory();

	void launch();
private:

	void SpawnBox();
	void UpdateMachine(Machine* machine);

	// The machines
	Machine *mh, *msk, *msh, *mp;

	// The machining queues
	Queue<int> *machiningHeads, *machiningSkirts, *machiningShafts;
	// The assemblage queues
	Queue<int> *assemblageHeads, *assemblageSkirts, *assemblageShafts;
	// The assembled pistons queue
	Queue<int> *pistons;
};

