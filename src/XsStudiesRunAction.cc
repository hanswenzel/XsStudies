#include "XsStudiesRunAction.hh"
#include "XsStudiesRun.hh"

#include "XsStudiesSD.hh"
#include "XsStudiesDetectorConstruction.hh"
#include "XsStudiesPrimaryGeneratorAction.hh"

#include "Randomize.hh"
//
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4Element.hh"
#include "G4UnitsTable.hh"
#include "G4Neutron.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4HadronicProcessStore.hh"
#include "G4NucleiProperties.hh"
#include "G4StableIsotopes.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesRunAction::XsStudiesRunAction() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesRunAction::~XsStudiesRunAction() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesRunAction::BeginOfRunAction(const G4Run* aRun) {
    G4int id = aRun->GetRunID();
    G4cout << "### Run " << id << " start" << endl;

#ifdef G4VIS_USE
    G4UImanager* UI = G4UImanager::GetUIpointer();

    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if (pVVisManager) {
        UI->ApplyCommand("/vis/scene/notifyHandlers");
    }
#endif
}
  G4Run* XsStudiesRunAction::GenerateRun()
  {
    fRun = new XsStudiesRun();
    return fRun;
  }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesRunAction::EndOfRunAction(const G4Run* aRun) {
    const XsStudiesRun* masterRun = static_cast<const XsStudiesRun*> (aRun);
    if (isMaster) fRun->EndOfRun();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
