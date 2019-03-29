
#ifndef XsStudiesEventAction_h
#define XsStudiesEventAction_h 1
 
#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Event;
class G4Track;
class XsStudiesEventActionMessenger;
class G4UImanager;

class XsStudiesEventAction : public G4UserEventAction
{
public: // Without description

  XsStudiesEventAction();
  virtual ~XsStudiesEventAction();

  void BeginOfXsStudiesEventAction(const G4Event*);
  void   EndOfXsStudiesEventAction(const G4Event*);

  void SetPrintModulo(G4int val)   {printModulo = val;};
  void SetDrawFlag(G4String val)   {drawFlag = val;};
  void AddEventToDebug(G4int val)  {selectedEvents.push_back(val);
                                    nSelected++;};

private:

  XsStudiesEventActionMessenger* eventMessenger;
  G4UImanager*          UI;
  std::vector<G4int>    selectedEvents;

  G4int        printModulo;
  G4int        nSelected;

  // drawFlags = all, charged, neutral, charged+n
  G4String     drawFlag;
  G4bool       debugStarted;
  //  std::vector<TrackInfo_t> TrackInfoVec;
  
};

#endif


