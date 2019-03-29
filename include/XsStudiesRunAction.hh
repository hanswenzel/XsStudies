
#ifndef XsStudiesRunAction_h
#define XsStudiesRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class XsStudiesRun;

class XsStudiesRunAction : public G4UserRunAction {
public: // Without description

    XsStudiesRunAction();
    virtual ~XsStudiesRunAction();
    virtual G4Run* GenerateRun();
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

private:
    
      XsStudiesRun*          fRun;

};

#endif

