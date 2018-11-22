#include "PUnit.h"
#include "main.cpp"

class PUnit
{
	const sc2::Unit *unitSnapshot;
	sc2::Tag unitTag;

	PUnit::PUnit()
	{

	}

	void updateUnit()
	{
		unitSnapshot = Bot::observation->GetUnit(unitTag);
	}

	PUnit::~PUnit()
	{
	}
};


