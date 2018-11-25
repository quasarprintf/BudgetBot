#include "UnitManager.h"
#include <sc2api/sc2_api.h>
#include "GameState.h"
#include "PUnit.h"

UnitManager::UnitManager()
{
}

void UnitManager::executeOrders(std::unordered_map<sc2::Tag, PUnit*> map, sc2::ActionInterface *actions)
{
	for (std::unordered_map<sc2::Tag, PUnit*>::iterator iterator = map.begin(); iterator != map.end(); ++iterator)
	{
		iterator->second->performAction(actions);
	}
}

void UnitManager::executeOrders(sc2::ActionInterface *actions)
{
	for (int index = 0; index <= GameState::unitGroup::ARMY; ++index)
	{
		executeOrders(GameState::unitGroups[index], actions);
	}
}



UnitManager::~UnitManager()
{
}
