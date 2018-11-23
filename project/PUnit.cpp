#include "PUnit.h"
#include <sc2api/sc2_api.h>


const sc2::Unit *unitSnapshot;
sc2::Tag unitTag;
bool newAction;
sc2::ABILITY_ID actionType;
const sc2::Point2D *actionTarget;

PUnit::PUnit(const sc2::Unit *snapshot, sc2::Tag tag)
{
	unitSnapshot = snapshot;
	unitTag = tag;
}

bool PUnit::updateUnit(const sc2::ObservationInterface *observation)
{
	unitSnapshot = observation->GetUnit(unitTag);
	newAction = false;
	if (unitSnapshot == nullptr)
	{
		return false;	//unit no longer exists
	}
	return true;		//unit still exists
}

void PUnit::performAction(sc2::ActionInterface *actions)
{
	if (!newAction)
	{
		return;
	}
	if (actionTarget == nullptr)
	{
		actions->UnitCommand(unitSnapshot, actionType);
	}
	else
	{
		actions->UnitCommand(unitSnapshot, actionType, actionTarget);
	}
		
}

PUnit::~PUnit()
{
}



