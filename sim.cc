#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "generator.hh"


int main(int argc, char** argv)
{

G4RunManager *runManager = new G4RunManager();
runManager->SetUserInitialization(new MyDetectorConstruction());
runManager->SetUserInitialization(new MyPhysicsList());
runManager->SetUserInitialization(new MyActionInitialization());

runManager->Initialize();

G4UIExecutive *ui = new G4UIExecutive(argc, argv);

G4VisManager *visManager = new G4VisExecutive();
visManager->Initialize();

G4UImanager *UIManager = G4UImanager::GetUIpointer();

UIManager->ApplyCommand("/vis/open OGL");
UIManager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
UIManager->ApplyCommand("/vis/drawVolume");
UIManager->ApplyCommand("/vis/viewer/set/autoRefresh true");
UIManager->ApplyCommand("/vis/scene/add/trajectories smooth");
UIManager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

ui->SessionStart();

    return 0;
}
