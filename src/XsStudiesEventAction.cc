#include "XsStudiesEventAction.hh"
#include "G4Event.hh"
#include "XsStudiesEventActionMessenger.hh"

#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4Track.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesEventAction::XsStudiesEventAction():
  printModulo(100),
  nSelected(0),
  drawFlag("all"),
  debugStarted(false)
{
  eventMessenger = new XsStudiesEventActionMessenger(this);
  UI = G4UImanager::GetUIpointer();
  selectedEvents.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesEventAction::~XsStudiesEventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesEventAction::BeginOfXsStudiesEventAction(const G4Event* evt)
{
  // New event
  G4int nEvt = evt->GetEventID();
  if(nEvt%100000==0)G4cout<<"EventID " <<nEvt<<G4endl;
 if(nSelected>0) {
    for(G4int i=0; i<nSelected; i++) {
      if(nEvt == selectedEvents[i]) {
        UI->ApplyCommand("/random/saveThisEvent");
        UI->ApplyCommand("/tracking/verbose  2");
        debugStarted = true;
        break;
      }
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void XsStudiesEventAction::EndOfXsStudiesEventAction(const G4Event* evt)
{
  
  if(debugStarted) {
    G4cout<<"End of debug: eventID: "<<(evt->GetEventID())<<G4endl;
    UI->ApplyCommand("/tracking/verbose  0");
    debugStarted = false;
  }

  //HadAnalysis* analysis = HadAnalysis::getInstance();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
