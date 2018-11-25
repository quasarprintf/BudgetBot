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
	if (GameState::unitGroups[GameState::unitGroup::PROBES].size() < build->first->probeGoal)
	{
		for (std::unordered_map<sc2::Tag, PUnit*>::iterator iterator = GameState::unitGroups[GameState::unitGroup::NEXI].begin(); iterator != GameState::unitGroups[GameState::unitGroup::NEXI].end(); ++iterator)
		{
			//std::cout << "minerals: " << GameState::minerals << "\n";
			//std::cout << "goal: " << build->first->probeGoal << "\n";
			//std::cout << "orders: " << iterator->second->unitSnapshot->orders.size() << "\n";
			if (iterator->second->unitSnapshot->orders.size() == 0 && GameState::minerals >= 50)
			{
				std::cout << "training probe\n";
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




