#include "BuildOrder.h"


class BuildOrder
{
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
		goal *nextGoal;
	};

	goal *first, *last;

	BuildOrder::BuildOrder()
	{
		first = nullptr;
		last = nullptr;
	}

	void addEndGoal(GOALTYPE type, int probeGoal)
	{
		goal newGoal = {type, probeGoal, nullptr };
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

	void addStartGoal(GOALTYPE type, int probeGoal)
	{
		goal newGoal = { type, probeGoal, nullptr };
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

	void completeGoal()
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
};

