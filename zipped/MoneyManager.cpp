#include "MoneyManager.h"
#include "BuildOrder.h"
#include "GameState.h"
#include <sc2api/sc2_api.h>
#include <iostream>


MoneyManager::MoneyManager()
{
}

void MoneyManager::followBuild(BuildOrder *build, sc2::ActionInterface *actions)
{
	std::cout << "probes: " << GameState::probes.size() << "\n";
	std::cout << "goal: " << build->first->probeGoal << "\n";
	std::cout << "minerals: " << GameState::minerals << "\n";
	

	if (GameState::probes.size() < build->first->probeGoal)
	{
		for (std::unordered_map<sc2::Tag, PUnit*>::iterator iterator = GameState::nexi.begin(); iterator != GameState::nexi.end(); ++iterator)
		{
			std::cout << "orders: " << iterator->second->unitSnapshot->orders.size() << "\n";
			if (iterator->second->unitSnapshot->orders.size() == 0 && GameState::minerals >= 50)
			{
				iterator->second->newAction = true;
				iterator->second->actionType = sc2::ABILITY_ID::TRAIN_PROBE;
				iterator->second->actionTarget = nullptr;
				GameState::minerals -= 50;
			}
		}
	}
}

MoneyManager::~MoneyManager()
{
}




