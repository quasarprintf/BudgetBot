#pragma once
#include <unordered_set>
#include <sc2api/sc2_api.h>
#include "Strategy.h"
#include "PUnit.h"

class GameState
{

public:

	enum unitGroup
	{
		NEXI,
		GATES,
		ROBOS,
		STARGATES,
		PYLONS,
		CANNONS,
		BATTERIES,
		CYBERCORES,
		FORGES,
		TWILIGHTS,
		DARKSHRINES,
		TEMPLARARCHIVES,
		FLEETBEACONS,
		ROBOBAYS,
		ASSIMILATORS,
		PROBES,
		ARMY,
		ENEMY_LARVAE,
		ENEMY_WORKERS,
		ENEMY_BASESTRUCTURES,
		ENEMY_STATICDEFENSES,
		ENEMY_OTHERBUILDINGS,
		ENEMY_ARMY,
		NEUTRAL_MINERALS,
		NEUTRAL_GASES,
		NEUTRAL_ROCKS,
		NUMBER_OF_UNIT_GROUPS
	};

	static sc2::Race matchup;
	static sc2::UnitTypes unitTypeData;

	static int32_t minerals, gas;

	static PUnit *prism, *scout1, *scout2;
	static std::unordered_map<sc2::Tag, PUnit*> unitGroups[NUMBER_OF_UNIT_GROUPS];
	static std::unordered_set<sc2::Tag> *seenUnits;
	void updateExistingUnits(const sc2::ObservationInterface *observation);
	void updateResources(const sc2::ObservationInterface *observation);
	void findNewUnits(const sc2::ObservationInterface *observation);
	GameState();
	~GameState();

private:
	void updateExistingUnits(std::unordered_map<sc2::Tag, PUnit*> *map, const sc2::ObservationInterface *observation);
};
