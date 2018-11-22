#include "GameState.h"
#include <sc2api/sc2_api.h>
#include "Strategy.h"
#include "main.cpp"
#include <unordered_set>

class GameState
{
	static sc2::Race matchup;
	static uint32_t playerId;
	static sc2::UnitTypeData unitTypeData;

	static int minerals, gas;

	static sc2::Tag prism, scout1, scout2;
	static std::unordered_map<sc2::Tag, const sc2::Unit*> nexi, gates, robos, stargates, pylons, cannons, batteries, cyberCores, forges, twilights, darkShrines, templarArchives, fleetBeacons, roboBays, assimilators, probes, army;
	static std::unordered_map<sc2::Tag, const sc2::Unit*> enemyLarvae, enemyWorkers, enemyBaseStructures, enemyStaticDefenses, enemyOtherBuildings, enemyArmy;
	static std::unordered_set<sc2::Tag> seenUnits;

	GameState::GameState()
	{
		const std::vector<sc2::PlayerInfo> players = Bot::observation->GetGameInfo().player_info;
		playerId = Bot::observation->GetPlayerID();
		if (players[0].player_id == playerId)
		{
			matchup = players[1].race_actual;
		}
		else
		{
			matchup = players[0].race_actual;
		}
		if (matchup == sc2::Race::Zerg)
		{
			Strategy::workerGoal = 18;
		}
		else
		{
			Strategy::workerGoal = 16;
		}

		unitTypeData = Bot::observation->GetUnitTypeData;

		nexi = std::unordered_map<sc2::Tag, const sc2::Unit*>(3);
		gates = std::unordered_map<sc2::Tag, const sc2::Unit*>(8);
		robos = std::unordered_map<sc2::Tag, const sc2::Unit*>(2);
		stargates = std::unordered_map<sc2::Tag, const sc2::Unit*>(2);
		forges = std::unordered_map<sc2::Tag, const sc2::Unit*>(2);
		twilights = std::unordered_map<sc2::Tag, const sc2::Unit*>(1);
		darkShrines = std::unordered_map<sc2::Tag, const sc2::Unit*>(1);
		templarArchives = std::unordered_map<sc2::Tag, const sc2::Unit*>(1);
		fleetBeacons = std::unordered_map<sc2::Tag, const sc2::Unit*>(1);
		roboBays = std::unordered_map<sc2::Tag, const sc2::Unit*>(2);
		assimilators = std::unordered_map<sc2::Tag, const sc2::Unit*>(6);
		cyberCores = std::unordered_map<sc2::Tag, const sc2::Unit*>(1);
		pylons = std::unordered_map<sc2::Tag, const sc2::Unit*>(10);
		cannons = std::unordered_map<sc2::Tag, const sc2::Unit*>(6);
		batteries = std::unordered_map<sc2::Tag, const sc2::Unit*>(8);
		probes = std::unordered_map<sc2::Tag, const sc2::Unit*>(40);
		army = std::unordered_map<sc2::Tag, const sc2::Unit*>(40);

		enemyLarvae = std::unordered_map<sc2::Tag, const sc2::Unit*>(20);
		enemyWorkers = std::unordered_map<sc2::Tag, const sc2::Unit*>(40);
		enemyBaseStructures = std::unordered_map<sc2::Tag, const sc2::Unit*>(3);
		enemyStaticDefenses = std::unordered_map<sc2::Tag, const sc2::Unit*>(3);
		enemyOtherBuildings = std::unordered_map<sc2::Tag, const sc2::Unit*>(15);
		enemyArmy = std::unordered_map<sc2::Tag, const sc2::Unit*>(40);

		seenUnits = std::unordered_set<sc2::Tag>(200);
	}

	void updateResources()
	{
		minerals = Bot::observation->GetMinerals;
		minerals = Bot::observation->GetVespene;
	}

	void updateExistingUnits()
	{
		updateExistingUnits(nexi);
		updateExistingUnits(gates);
		updateExistingUnits(robos);
		updateExistingUnits(stargates);
		updateExistingUnits(forges);
		updateExistingUnits(twilights);
		updateExistingUnits(darkShrines);
		updateExistingUnits(templarArchives);
		updateExistingUnits(fleetBeacons);
		updateExistingUnits(roboBays);
		updateExistingUnits(assimilators);
		updateExistingUnits(cyberCores);
		updateExistingUnits(pylons);
		updateExistingUnits(cannons);
		updateExistingUnits(batteries);
		updateExistingUnits(probes);
		updateExistingUnits(army);

		updateExistingUnits(enemyLarvae);
		updateExistingUnits(enemyWorkers);
		updateExistingUnits(enemyBaseStructures);
		updateExistingUnits(enemyStaticDefenses);
		updateExistingUnits(enemyOtherBuildings);
		updateExistingUnits(enemyArmy);
	}

	void updateExistingUnits(std::unordered_map<sc2::Tag, const sc2::Unit*> map)
	{
		for (std::unordered_map<sc2::Tag, const sc2::Unit*>::iterator iterator = map.begin(); iterator != map.end(); ++iterator)
		{
			const sc2::Unit* updatedUnit = Bot::observation->GetUnit(iterator->first);
			if (updatedUnit == nullptr)
			{
				seenUnits.erase(iterator->first);
				iterator = map.erase(iterator)--;
			}
			else
			{
				map[iterator->first] = updatedUnit;
			}
			break;
		}
	}

	void findNewUnits()
	{
		sc2::Units allUnits = Bot::observation->GetUnits();
		for (int index = 0; index < allUnits.size; ++index)
		{
			if (seenUnits.find(allUnits[index]->tag) != seenUnits.end)
			{
				seenUnits.insert(allUnits[index]->tag);
				if (allUnits[index]->owner == playerId)
				{
					switch (allUnits[index]->unit_type.ToType)
					{
					case sc2::UNIT_TYPEID::PROTOSS_PROBE:
						probes[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
						nexi[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_WARPPRISM:
						prism = allUnits[index]->tag;
						break;
					case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:
					case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:
						gates[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY:
						robos[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:
						roboBays[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_STARGATE:
						stargates[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:
						fleetBeacons[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE:
						cyberCores[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL:
						twilights[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:
						darkShrines[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:
						templarArchives[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_FORGE:
						forges[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_PYLON:
						pylons[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
						cannons[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
						batteries[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:
						assimilators[allUnits[index]->tag] = allUnits[index];
						break;
					default:
						army[allUnits[index]->tag] = allUnits[index];
						break;
					}
				}
				else
				{
					switch (allUnits[index]->unit_type.ToType)
					{
					case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS:
						enemyBaseStructures[allUnits[index]->tag] = allUnits[index];
						enemyStaticDefenses[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:
					case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING:
					case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:
					case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING:
					case sc2::UNIT_TYPEID::ZERG_HATCHERY:
					case sc2::UNIT_TYPEID::ZERG_LAIR:
					case sc2::UNIT_TYPEID::ZERG_HIVE:
					case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
						enemyBaseStructures[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:
					case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:
					case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:
					case sc2::UNIT_TYPEID::TERRAN_BUNKER:
					case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
					case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
						enemyStaticDefenses[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::TERRAN_SCV:
					case sc2::UNIT_TYPEID::TERRAN_MULE:
					case sc2::UNIT_TYPEID::PROTOSS_PROBE:
					case sc2::UNIT_TYPEID::ZERG_DRONE:
						enemyWorkers[allUnits[index]->tag] = allUnits[index];
						break;
					case sc2::UNIT_TYPEID::ZERG_LARVA:
						enemyLarvae[allUnits[index]->tag] = allUnits[index];
						break;
					default:
						bool structure = false;
						std::vector<sc2::Attribute> unitAttributes = unitTypeData[allUnits[index]->unit_type.ToType].attributes;
						for (std::vector<sc2::Attribute>::iterator AttrIterator = unitAttributes.begin(); AttrIterator != unitAttributes.end(); ++AttrIterator)
						{
							if (*AttrIterator == sc2::Attribute::Structure)
							{
								structure = true;
								break;
							}
						}
						if (structure)
						{
							enemyOtherBuildings[allUnits[index]->tag] = allUnits[index];
						}
						else
						{
							enemyArmy[allUnits[index]->tag] = allUnits[index];
						}
						delete &unitAttributes;
						break;
					}
				}
			}
		}
		delete &allUnits;
	}


	GameState::~GameState()
	{
	}
};