#include <sc2api/sc2_api.h>
#include "PUnit.h"
#include "Strategy.h"
#include "GameState.h"
#include "MoneyManager.h"
#include "BuildOrder.h"
#include "UnitManager.h"
#include <iostream>

#include "windows.h"

using namespace sc2;

class Bot : public Agent 
{
	GameState gameState = GameState();
	MoneyManager moneyManager = MoneyManager();
	UnitManager unitManager = UnitManager();
	Strategy strategy = Strategy();
	const ObservationInterface *observation = nullptr;
	ActionInterface *actions = nullptr;

	virtual void OnGameStart() final
	{
		observation = Observation();

		Strategy::currentBuild->addStartGoal(BuildOrder::GOALTYPE::BUILD_PYLON, 14);

		const std::vector<sc2::PlayerInfo> players = observation->GetGameInfo().player_info;
		if (players[0].player_id == observation->GetPlayerID())
		{
			GameState::matchup = players[1].race_actual;
		}
		else
		{
			GameState::matchup = players[0].race_actual;
		}

		GameState::unitTypeData = observation->GetUnitTypeData();
	}

	virtual void OnStep() final
	{
		observation = Observation();

		actions = Actions();
		gameState.updateExistingUnits(observation);
		gameState.findNewUnits(observation);


		gameState.updateResources(observation);
		moneyManager.followBuild(Strategy::currentBuild, actions);
		unitManager.executeOrders(actions);
		Sleep(40);
	}
};

int main(int argc, char* argv[]) {
    Coordinator coordinator;
    coordinator.LoadSettings(argc, argv);

    Bot bot;
    coordinator.SetParticipants({
        CreateParticipant(Race::Protoss, &bot),
        CreateComputer(Race::Zerg)
    });

    coordinator.LaunchStarcraft();
	coordinator.StartGame("C:\\Users\\pikac\\Documents\\StarCraft II\\Maps\\aiMaps\\AbiogenesisLE.SC2Map");

    while (coordinator.Update()) {
    }

    return 0;
}