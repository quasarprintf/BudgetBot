#include <sc2api/sc2_api.h>
#include "PUnit.h"
#include "Strategy.h"
#include "GameState.h"
#include <iostream>

using namespace sc2;

class Bot : public Agent {
	Race matchup;
public:
	static GameState gameState;
	static const ObservationInterface *observation;
	static ActionInterface *actions;

	virtual void OnGameStart() final
	{
		gameState = GameState();
	}

    virtual void OnStep() final {
		observation = Observation();
		actions = Actions();
		gameState.updateExistingUnits();
		gameState.findNewUnits();
		gameState.updateResources();
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