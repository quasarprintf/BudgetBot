#include "MoneyManager.h"
#include "BuildOrder.h"
#include "GameState.h"
#include "main.cpp"
#include <sc2api/sc2_api.h>

class MoneyManager
{
	MoneyManager::MoneyManager()
	{
	}

	void followBuild(BuildOrder build)
	{
		if (GameState::probes.size < build.first->probeGoal)
		{
			for (std::unordered_map<sc2::Tag, const sc2::Unit*>::iterator iterator = GameState::nexi.begin(); iterator != GameState::nexi.end(); ++iterator)
			{
				if (iterator->second->orders.size() == 0 && GameState::minerals >= 50)
				{
					Bot::actions->UnitCommand(iterator->second, ABILITY_ID::TRAIN_PROBE);
					GameState::minerals -= 50;
				}
			}
		}
	}

	MoneyManager::~MoneyManager()
	{
	}
};


