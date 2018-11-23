#pragma once
#include "BuildOrder.h"
#include <sc2api/sc2_api.h>

class Strategy
{
public:
	static BuildOrder *currentBuild;
	Strategy();
	~Strategy();
};