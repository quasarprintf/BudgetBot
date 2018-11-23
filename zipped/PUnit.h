#pragma once
#include <sc2api/sc2_api.h>

class PUnit
{
public:
	const sc2::Unit *unitSnapshot;
	sc2::Tag unitTag;
	bool newAction;
	sc2::ABILITY_ID actionType;
	const sc2::Point2D *actionTarget;
	bool updateUnit(const sc2::ObservationInterface *observation);
	void performAction(sc2::ActionInterface *actions);
	PUnit(const sc2::Unit *snapshot, sc2::Tag tag);
	~PUnit();
};

