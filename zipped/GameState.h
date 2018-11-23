#pragma once
#include <unordered_set>
#include <sc2api/sc2_api.h>
#include "Strategy.h"
#include "PUnit.h"

class GameState
{
public:

    static sc2::Race matchup;
    static uint32_t playerId;
    static sc2::UnitTypes unitTypeData;

    static int32_t minerals, gas;

    static PUnit *prism, *scout1, *scout2;
    static std::unordered_map<sc2::Tag, PUnit*> nexi, gates, robos, stargates, pylons, cannons, batteries, cyberCores, forges, twilights, darkShrines, templarArchives, fleetBeacons, roboBays, assimilators, probes, army;
    static std::unordered_map<sc2::Tag, PUnit*> enemyLarvae, enemyWorkers, enemyBaseStructures, enemyStaticDefenses, enemyOtherBuildings, enemyArmy;
	static std::unordered_set<sc2::Tag> *seenUnits;
    void updateExistingUnits(const sc2::ObservationInterface *observation);
    void updateResources(const sc2::ObservationInterface *observation);
    void findNewUnits(const sc2::ObservationInterface *observation);
	GameState();
	~GameState();

private:
	void updateExistingUnits(std::unordered_map<sc2::Tag, PUnit*> *map, const sc2::ObservationInterface *observation);
};

