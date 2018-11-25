#include "BuildOrder.h"
#include <sc2api/sc2_api.h>
#include "PUnit.h"
#include <iostream>

BuildOrder::BuildOrder()
{
	first = nullptr;
	last = nullptr;
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal)
{
	goal *newGoal = new goal {type, probeGoal, nullptr, 0, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		last->nextGoal = newGoal;
		last = newGoal;
	}
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal, PUnit *target)
{
	goal *newGoal = new goal { type, probeGoal, target, 0, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		last->nextGoal = newGoal;
		last = newGoal;
	}
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal, int specification)
{
	goal *newGoal = new goal { type, probeGoal, nullptr, specification, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		last->nextGoal = newGoal;
		last = newGoal;
	}
}

void BuildOrder::addEndGoal(GOALTYPE type, int probeGoal, PUnit *target, int specification)
{
	goal *newGoal = new goal { type, probeGoal, target, specification, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		last->nextGoal = newGoal;
		last = newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal)
{
	goal *newGoal = new goal { type, probeGoal, nullptr, 0, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		newGoal->nextGoal = first;
		first = newGoal;
	}
	int temp = first->goalType;
	int temp2 = first->probeGoal;
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal, PUnit *target)
{
	goal *newGoal = new goal { type, probeGoal, target, 0, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		newGoal->nextGoal = first;
		first = newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal, int specification)
{
	goal *newGoal = new goal { type, probeGoal, nullptr, specification, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		newGoal->nextGoal = first;
		first = newGoal;
	}
}

void BuildOrder::addStartGoal(GOALTYPE type, int probeGoal, PUnit *target, int specification)
{
	goal *newGoal = new goal { type, probeGoal, target, specification, nullptr };
	if (first == nullptr)
	{
		first = newGoal;
		last = newGoal;
	}
	else
	{
		newGoal->nextGoal = first;
		first = newGoal;
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

