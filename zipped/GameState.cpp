#include "GameState.h"
#include <unordered_set>
#include <sc2api/sc2_api.h>
#include "Strategy.h"
#include "PUnit.h"
#include <iostream>



	sc2::Race GameState::matchup = sc2::Race::Protoss;
	uint32_t GameState::playerId = 0;
	sc2::UnitTypes GameState::unitTypeData = {};

	int32_t GameState::minerals = 0;
	int32_t GameState::gas = 0;

	PUnit *GameState::prism = nullptr;
	PUnit *GameState::scout1 = nullptr;
	PUnit *GameState::scout2 = nullptr;

	std::unordered_map<sc2::Tag, PUnit*> GameState::nexi = std::unordered_map<sc2::Tag, PUnit*>(3);
	std::unordered_map<sc2::Tag, PUnit*> GameState::gates = std::unordered_map<sc2::Tag, PUnit*>(8);
	std::unordered_map<sc2::Tag, PUnit*> GameState::robos = std::unordered_map<sc2::Tag, PUnit*>(2);
	std::unordered_map<sc2::Tag, PUnit*> GameState::stargates = std::unordered_map<sc2::Tag, PUnit*>(2);
	std::unordered_map<sc2::Tag, PUnit*> GameState::forges = std::unordered_map<sc2::Tag, PUnit*>(2);
	std::unordered_map<sc2::Tag, PUnit*> GameState::twilights = std::unordered_map<sc2::Tag, PUnit*>(1);
	std::unordered_map<sc2::Tag, PUnit*> GameState::darkShrines = std::unordered_map<sc2::Tag, PUnit*>(1);
	std::unordered_map<sc2::Tag, PUnit*> GameState::templarArchives = std::unordered_map<sc2::Tag, PUnit*>(1);
	std::unordered_map<sc2::Tag, PUnit*> GameState::fleetBeacons = std::unordered_map<sc2::Tag, PUnit*>(1);
	std::unordered_map<sc2::Tag, PUnit*> GameState::roboBays = std::unordered_map<sc2::Tag, PUnit*>(2);
	std::unordered_map<sc2::Tag, PUnit*> GameState::assimilators = std::unordered_map<sc2::Tag, PUnit*>(6);
	std::unordered_map<sc2::Tag, PUnit*> GameState::cyberCores = std::unordered_map<sc2::Tag, PUnit*>(1);
	std::unordered_map<sc2::Tag, PUnit*> GameState::pylons = std::unordered_map<sc2::Tag, PUnit*>(10);
	std::unordered_map<sc2::Tag, PUnit*> GameState::cannons = std::unordered_map<sc2::Tag, PUnit*>(6);
	std::unordered_map<sc2::Tag, PUnit*> GameState::batteries = std::unordered_map<sc2::Tag, PUnit*>(8);
	std::unordered_map<sc2::Tag, PUnit*> GameState::probes = std::unordered_map<sc2::Tag, PUnit*>(40);
	std::unordered_map<sc2::Tag, PUnit*> GameState::army = std::unordered_map<sc2::Tag, PUnit*>(40);

	std::unordered_map<sc2::Tag, PUnit*> GameState::enemyLarvae = std::unordered_map<sc2::Tag, PUnit*>(20);
	std::unordered_map<sc2::Tag, PUnit*> GameState::enemyWorkers = std::unordered_map<sc2::Tag, PUnit*>(40);
	std::unordered_map<sc2::Tag, PUnit*> GameState::enemyBaseStructures = std::unordered_map<sc2::Tag, PUnit*>(3);
	std::unordered_map<sc2::Tag, PUnit*> GameState::enemyStaticDefenses = std::unordered_map<sc2::Tag, PUnit*>(3);
	std::unordered_map<sc2::Tag, PUnit*> GameState::enemyOtherBuildings = std::unordered_map<sc2::Tag, PUnit*>(15);
	std::unordered_map<sc2::Tag, PUnit*> GameState::enemyArmy = std::unordered_map<sc2::Tag, PUnit*>(40);

	std::unordered_set<sc2::Tag> *GameState::seenUnits = new std::unordered_set<sc2::Tag>(200);

	GameState::GameState()
	{
	
	}

	void GameState::updateResources(const sc2::ObservationInterface *observation)
	{
		minerals = observation->GetMinerals();
		gas = observation->GetVespene();
	}

	void GameState::updateExistingUnits(std::unordered_map<sc2::Tag, PUnit*> *map, const sc2::ObservationInterface *observation)
	{
		for (std::unordered_map<sc2::Tag, PUnit*>::iterator iterator = map->begin(); iterator != map->end(); ++iterator)
		{
			if (!iterator->second->updateUnit(observation))
			{
				delete iterator->second;
				seenUnits->erase(iterator->first);
				iterator = map->erase(iterator)--;
			}
			break;
		}
	}

	void GameState::updateExistingUnits(const sc2::ObservationInterface *observation)
	{
		updateExistingUnits(&nexi, observation);
		updateExistingUnits(&gates, observation);
		updateExistingUnits(&robos, observation);
		updateExistingUnits(&stargates, observation);
		updateExistingUnits(&forges, observation);
		updateExistingUnits(&twilights, observation);
		updateExistingUnits(&darkShrines, observation);
		updateExistingUnits(&templarArchives, observation);
		updateExistingUnits(&fleetBeacons, observation);
		updateExistingUnits(&roboBays, observation);
		updateExistingUnits(&assimilators, observation);
		updateExistingUnits(&cyberCores, observation);
		updateExistingUnits(&pylons, observation);
		updateExistingUnits(&cannons, observation);
		updateExistingUnits(&batteries, observation);
		updateExistingUnits(&probes, observation);
		updateExistingUnits(&army, observation);

		updateExistingUnits(&enemyLarvae, observation);
		updateExistingUnits(&enemyWorkers, observation);
		updateExistingUnits(&enemyBaseStructures, observation);
		updateExistingUnits(&enemyStaticDefenses, observation);
		updateExistingUnits(&enemyOtherBuildings, observation);
		updateExistingUnits(&enemyArmy, observation);
	}

	void GameState::findNewUnits(const sc2::ObservationInterface *observation)
	{
		sc2::Units allUnits = observation->GetUnits();

		for (int index = 0; index < allUnits.size(); ++index)

		{

			if (seenUnits->find(allUnits[index]->tag) != seenUnits->end())
			{
				seenUnits->insert(allUnits[index]->tag);
				if (allUnits[index]->owner == playerId)
				{
					switch (allUnits[index]->unit_type.ToType())
					{
					case sc2::UNIT_TYPEID::PROTOSS_PROBE:
						probes[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
						nexi[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_WARPPRISM:
						prism = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:
					case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:
						gates[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY:
						robos[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:
						roboBays[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_STARGATE:
						stargates[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:
						fleetBeacons[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE:
						cyberCores[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL:
						twilights[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:
						darkShrines[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:
						templarArchives[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_FORGE:
						forges[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_PYLON:
						pylons[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
						cannons[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
						batteries[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:
						assimilators[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					default:
						army[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					}
				}
				else
				{
					PUnit *unit;
					switch (allUnits[index]->unit_type.ToType())
					{
					case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS:
						unit = new PUnit(allUnits[index], allUnits[index]->tag);
						enemyBaseStructures[allUnits[index]->tag] = unit;
						enemyStaticDefenses[allUnits[index]->tag] = unit;
						break;
					case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:
					case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING:
					case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:
					case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING:
					case sc2::UNIT_TYPEID::ZERG_HATCHERY:
					case sc2::UNIT_TYPEID::ZERG_LAIR:
					case sc2::UNIT_TYPEID::ZERG_HIVE:
					case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
						enemyBaseStructures[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:
					case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:
					case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:
					case sc2::UNIT_TYPEID::TERRAN_BUNKER:
					case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
					case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
						enemyStaticDefenses[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::TERRAN_SCV:
					case sc2::UNIT_TYPEID::TERRAN_MULE:
					case sc2::UNIT_TYPEID::PROTOSS_PROBE:
					case sc2::UNIT_TYPEID::ZERG_DRONE:
						enemyWorkers[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::ZERG_LARVA:
						enemyLarvae[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					default:
						bool structure = false;
						std::vector<sc2::Attribute> unitAttributes = unitTypeData[static_cast<int>(allUnits[index]->unit_type.ToType())].attributes;
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
							enemyOtherBuildings[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						}
						else
						{
							enemyArmy[allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						}
						delete &unitAttributes;
						break;
					}
				}
			}
		}
		//delete &allUnits;
	}


	GameState::~GameState()
	{
	}
