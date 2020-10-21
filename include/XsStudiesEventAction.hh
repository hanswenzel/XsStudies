
#ifndef XsStudiesEventAction_h
#define XsStudiesEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//class G4Event;
class XsStudiesRunAction;

class XsStudiesEventAction : public G4UserEventAction {
public: // Without description

    XsStudiesEventAction(XsStudiesRunAction* runAction);
    virtual ~XsStudiesEventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

private:
    XsStudiesRunAction* fRunAction;

};

#endif


