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
	executeOrders(GameState::nexi, actions);
	executeOrders(GameState::gates, actions);
	executeOrders(GameState::robos, actions);
	executeOrders(GameState::stargates, actions);
	executeOrders(GameState::forges, actions);
	executeOrders(GameState::twilights, actions);
	executeOrders(GameState::darkShrines, actions);
	executeOrders(GameState::templarArchives, actions);
	executeOrders(GameState::fleetBeacons, actions);
	executeOrders(GameState::roboBays, actions);
	executeOrders(GameState::assimilators, actions);
	executeOrders(GameState::cyberCores, actions);
	executeOrders(GameState::pylons, actions);
	executeOrders(GameState::cannons, actions);
	executeOrders(GameState::batteries, actions);
	executeOrders(GameState::probes, actions);
	executeOrders(GameState::army, actions);
}



UnitManager::~UnitManager()
{
}
