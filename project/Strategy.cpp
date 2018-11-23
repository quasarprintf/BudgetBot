#include "Strategy.h"
#include "BuildOrder.h"
#include <sc2api/sc2_api.h>
#include <iostream>


BuildOrder *Strategy::currentBuild = new BuildOrder();
Strategy::Strategy()
{
}


Strategy::~Strategy()
{
}
