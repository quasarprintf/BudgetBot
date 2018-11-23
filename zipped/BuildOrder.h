#pragma once
#include <sc2api/sc2_api.h>
#include "PUnit.h"

class BuildOrder
{
public:
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
		int specification;
        goal *nextGoal;
    };
    void addEndGoal(GOALTYPE type, int probeGoal);
	void addEndGoal(GOALTYPE type, int probeGoal, PUnit *target);
	void addEndGoal(GOALTYPE type, int probeGoal, int specification);
	void addEndGoal(GOALTYPE type, int probeGoal, PUnit *target, int specification);
    void addStartGoal(GOALTYPE type, int probeGoal);
    void addStartGoal(GOALTYPE type, int probeGoal, PUnit *target);
    void addStartGoal(GOALTYPE type, int probeGoal, int specification);
    void addStartGoal(GOALTYPE type, int probeGoal, PUnit *target, int specification);
    void completeGoal();
    goal *first, *last;

	BuildOrder();
	~BuildOrder();
};

