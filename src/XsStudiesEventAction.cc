#include "XsStudiesEventAction.hh"
#include "XsStudiesRunAction.hh"
#include "G4Event.hh"
#include "XsStudiesSD.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4SDManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesEventAction::XsStudiesEventAction(XsStudiesRunAction* runAction) : G4UserEventAction(),
fRunAction(runAction) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesEventAction::~XsStudiesEventAction() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesEventAction::BeginOfEventAction(const G4Event* evt) {
    (void)evt;
    // New event
    //G4int nEvt = evt->GetEventID();
    //if (nEvt % 10000 == 0)G4cout << "EventID " << nEvt << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesEventAction::EndOfEventAction(const G4Event* evt) {
    XsStudiesSD* hadSD = (XsStudiesSD*) G4SDManager::GetSDMpointer()->FindSensitiveDetector("TargetSD");
    if (hadSD->GetNumberElastic() == 1) {
        fRunAction->CountElastic();
    } else if (hadSD->GetNumberinElastic() == 1) {
        fRunAction->CountInElastic();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
