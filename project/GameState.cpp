#include "GameState.h"
#include <unordered_set>
#include <sc2api/sc2_api.h>
#include "Strategy.h"
#include "PUnit.h"
#include <iostream>



	sc2::Race GameState::matchup = sc2::Race::Protoss;
	sc2::UnitTypes GameState::unitTypeData = {};

	int32_t GameState::minerals = 0;
	int32_t GameState::gas = 0;

	PUnit *GameState::prism = nullptr;
	PUnit *GameState::scout1 = nullptr;
	PUnit *GameState::scout2 = nullptr;

	std::unordered_map<sc2::Tag, PUnit*> GameState::unitGroups[NUMBER_OF_UNIT_GROUPS] = { std::unordered_map<sc2::Tag, PUnit*>(3),//nexi
																							std::unordered_map<sc2::Tag, PUnit*>(8),//gates
																							std::unordered_map<sc2::Tag, PUnit*>(2),//robos
																							std::unordered_map<sc2::Tag, PUnit*>(2),//stargates
																							std::unordered_map<sc2::Tag, PUnit*>(2),//forges
																							std::unordered_map<sc2::Tag, PUnit*>(1),//twilights
																							std::unordered_map<sc2::Tag, PUnit*>(1),//dark shrines
																							std::unordered_map<sc2::Tag, PUnit*>(1),//templar archives
																							std::unordered_map<sc2::Tag, PUnit*>(1),//fleet beacons
																							std::unordered_map<sc2::Tag, PUnit*>(2),//robo bays
																							std::unordered_map<sc2::Tag, PUnit*>(6),//assimilators
																							std::unordered_map<sc2::Tag, PUnit*>(1),//cyber cores
																							std::unordered_map<sc2::Tag, PUnit*>(10),//pylons
																							std::unordered_map<sc2::Tag, PUnit*>(6),//cannons
																							std::unordered_map<sc2::Tag, PUnit*>(8),//batteries
																							std::unordered_map<sc2::Tag, PUnit*>(40),//probes
																							std::unordered_map<sc2::Tag, PUnit*>(40),//army

																							std::unordered_map<sc2::Tag, PUnit*>(20),//enemy larvae
																							std::unordered_map<sc2::Tag, PUnit*>(40),//enemy workers
																							std::unordered_map<sc2::Tag, PUnit*>(3),//enemy base structures
																							std::unordered_map<sc2::Tag, PUnit*>(3),//enemy static defenses
																							std::unordered_map<sc2::Tag, PUnit*>(15),//enemy other buildings
																							std::unordered_map<sc2::Tag, PUnit*>(40),//enemy army

																							std::unordered_map<sc2::Tag, PUnit*>(100),//minerals
																							std::unordered_map<sc2::Tag, PUnit*>(25),//gases
																							std::unordered_map<sc2::Tag, PUnit*>(6) };//rocks, towers, and plates

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
		}
	}

	void GameState::updateExistingUnits(const sc2::ObservationInterface *observation)
	{
		for (int index = 0; index < GameState::NUMBER_OF_UNIT_GROUPS; ++index)
		{
			updateExistingUnits(&unitGroups[index], observation);
		}
	}

	void GameState::findNewUnits(const sc2::ObservationInterface *observation)
	{
		sc2::Units allUnits = observation->GetUnits();
		for (int index = 0; index < allUnits.size(); ++index)
		{
			if (seenUnits->find(allUnits[index]->tag) == seenUnits->end())
			{
				seenUnits->insert(allUnits[index]->tag);
				if (allUnits[index]->alliance == sc2::Unit::Alliance::Self)
				{
					switch (allUnits[index]->unit_type.ToType())
					{
					case sc2::UNIT_TYPEID::PROTOSS_PROBE:
						unitGroups[GameState::PROBES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
						unitGroups[GameState::NEXI][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_WARPPRISM:
						unitGroups[GameState::ARMY][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						prism = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:
					case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:
						unitGroups[GameState::GATES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY:
						unitGroups[GameState::ROBOS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:
						unitGroups[GameState::ROBOBAYS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_STARGATE:
						unitGroups[GameState::STARGATES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:
						unitGroups[GameState::FLEETBEACONS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE:
						unitGroups[GameState::CYBERCORES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL:
						unitGroups[GameState::TWILIGHTS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:
						unitGroups[GameState::DARKSHRINES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:
						unitGroups[GameState::TEMPLARARCHIVES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_FORGE:
						unitGroups[GameState::FORGES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_PYLON:
						unitGroups[GameState::PYLONS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
						unitGroups[GameState::CANNONS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
						unitGroups[GameState::BATTERIES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:
						unitGroups[GameState::ASSIMILATORS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					default:
						unitGroups[GameState::ARMY][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						break;
					}
				}
				else
				{
					if (allUnits[index]->alliance == sc2::Unit::Alliance::Enemy)
					{
						PUnit *unit;
						switch (allUnits[index]->unit_type.ToType())
						{
						case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS:
							unit = new PUnit(allUnits[index], allUnits[index]->tag);
							unitGroups[GameState::ENEMY_BASESTRUCTURES][allUnits[index]->tag] = unit;
							unitGroups[GameState::ENEMY_STATICDEFENSES][allUnits[index]->tag] = unit;
							break;
						case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER:
						case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING:
						case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND:
						case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING:
						case sc2::UNIT_TYPEID::ZERG_HATCHERY:
						case sc2::UNIT_TYPEID::ZERG_LAIR:
						case sc2::UNIT_TYPEID::ZERG_HIVE:
						case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
							unitGroups[GameState::ENEMY_BASESTRUCTURES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
							break;
						case sc2::UNIT_TYPEID::ZERG_SPINECRAWLER:
						case sc2::UNIT_TYPEID::ZERG_SPORECRAWLER:
						case sc2::UNIT_TYPEID::TERRAN_MISSILETURRET:
						case sc2::UNIT_TYPEID::TERRAN_BUNKER:
						case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
						case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
							unitGroups[GameState::ENEMY_STATICDEFENSES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
							break;
						case sc2::UNIT_TYPEID::TERRAN_SCV:
						case sc2::UNIT_TYPEID::TERRAN_MULE:
						case sc2::UNIT_TYPEID::PROTOSS_PROBE:
						case sc2::UNIT_TYPEID::ZERG_DRONE:
							unitGroups[GameState::ENEMY_WORKERS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
							break;
						case sc2::UNIT_TYPEID::ZERG_LARVA:
							unitGroups[GameState::ENEMY_LARVAE][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
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
								unitGroups[GameState::ENEMY_OTHERBUILDINGS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
							}
							else
							{
								unitGroups[GameState::ENEMY_ARMY][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
							}
							break;
						}
					}
					else if (allUnits[index]->alliance == sc2::Unit::Alliance::Neutral)
					{
						if (unitTypeData[static_cast<int>(allUnits[index]->unit_type.ToType())].has_minerals)
						{
							unitGroups[GameState::NEUTRAL_MINERALS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
						}
						else
						{
							if (unitTypeData[static_cast<int>(allUnits[index]->unit_type.ToType())].has_vespene)
							{
								unitGroups[GameState::NEUTRAL_GASES][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
							}
							else
							{
								std::vector<sc2::Attribute> unitAttributes = unitTypeData[static_cast<int>(allUnits[index]->unit_type.ToType())].attributes;
								for (std::vector<sc2::Attribute>::iterator AttrIterator = unitAttributes.begin(); AttrIterator != unitAttributes.end(); ++AttrIterator)
								{
									if (*AttrIterator == sc2::Attribute::Structure)
									{
										unitGroups[GameState::NEUTRAL_ROCKS][allUnits[index]->tag] = new PUnit(allUnits[index], allUnits[index]->tag);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}


	GameState::~GameState()
	{
	}
