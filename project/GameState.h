#pragma once
class GameState : public sc2::Agent
{
public:

    sc2::Race matchup;
    static uint32_t playerId;
    static sc2::UnitTypeData unitTypeData;

    static int minerals, gas;

    static sc2::Tag prism, scout1, scout2;
    static std::unordered_map<sc2::Tag, const sc2::Unit*> nexi, gates, robos, stargates, pylons, cannons, batteries, cyberCores, forges, twilights, darkShrines, templarArchives, fleetBeacons, roboBays, assimilators, probes, army;
    static std::unordered_map<sc2::Tag, const sc2::Unit*> enemyLarvae, enemyWorkers, enemyBaseStructures, enemyStaticDefenses, enemyOtherBuildings, enemyArmy;
    void updateExistingUnits();
    void updateResources();
    void findNewUnits();
	GameState();
	~GameState();

private:
    void updateExistingUnits(std::unordered_map<sc2::Tag, const sc2::Unit*> map)
};

