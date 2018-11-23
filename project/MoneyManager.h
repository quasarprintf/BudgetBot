#pragma once
#include "BuildOrder.h"
#include "GameState.h"
#include <sc2api/sc2_api.h>

class MoneyManager
{
public:
	void followBuild(BuildOrder *build, sc2::ActionInterface *actions);
	MoneyManager();
	~MoneyManager();
};

