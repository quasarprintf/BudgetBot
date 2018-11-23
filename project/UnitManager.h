#pragma once
#include <sc2api/sc2_api.h>
#include "GameState.h"
#include "PUnit.h"

class UnitManager
{
public:
	void executeOrders(sc2::ActionInterface *actions);
	UnitManager();
	~UnitManager();

private:
	void UnitManager::executeOrders(std::unordered_map<sc2::Tag, PUnit*> map, sc2::ActionInterface *actions);
};

