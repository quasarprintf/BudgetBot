#include "BuildOrder.h"
#include <sc2api/sc2_api.h>
#include "PUnit.h"
#include <iostream>


enum GOALTYPE
{
	CANNON_RUSH,
	SEND_SCOUT,

	BUILD_PYLON,
	BUILD_FORGE,
	BUILD_GATEWAY,
	BUILD_CYBER,
	BUILD_ROBO,
	BUILD_ROBOBAY,
	BUILD_STARGATE,
	BUILD_FLEETBEACON,
	BUILD_TWILIGHT,
	BUILD_ARCHIVES,
	BUILD_SHRINE,
	BUILD_NEXUS,
	BUILD_ASSIMILATOR,
};

struct goal
{
	GOALTYPE goalType;
	int probeGoal;
	PUnit *targetUnit;
	int specification;	//should be set to enums
	goal *nextGoal;
};

goal *first, *last;

BuildOrder::BuildOrder()
{
	first = nullptr;
	last = nullptr;
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal)
{
	goal newGoal = {type, probeGoal, nullptr, 0, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		last->nextGoal = &newGoal;
		last = &newGoal;
	}
	std::cout << "{" << first->probeGoal << "}\n";
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal, PUnit *target)
{
	goal newGoal = { type, probeGoal, target, 0, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		last->nextGoal = &newGoal;
		last = &newGoal;
	}
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal, int specification)
{
	goal newGoal = { type, probeGoal, nullptr, specification, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		last->nextGoal = &newGoal;
		last = &newGoal;
	}
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal, PUnit *target, int specification)
{
	goal newGoal = { type, probeGoal, target, specification, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		last->nextGoal = &newGoal;
		last = &newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal)
{
	goal newGoal = { type, probeGoal, nullptr, 0, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		newGoal.nextGoal = first;
		first = &newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal, PUnit *target)
{
	goal newGoal = { type, probeGoal, target, 0, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		newGoal.nextGoal = first;
		first = &newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal, int specification)
{
	goal newGoal = { type, probeGoal, nullptr, specification, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		newGoal.nextGoal = first;
		first = &newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal, PUnit *target, int specification)
{
	goal newGoal = { type, probeGoal, target, specification, nullptr };
	if (first == nullptr)
	{
		first = &newGoal;
		last = &newGoal;
	}
	else
	{
		newGoal.nextGoal = first;
		first = &newGoal;
	}
}

void BuildOrder::completeGoal()
{
	goal *newFirst = first->nextGoal;
	delete first;
	first = first->nextGoal;
	if (first == nullptr)
	{
		last = nullptr;
	}
}

BuildOrder::~BuildOrder()
{
}

