
#ifndef XsStudiesRunAction_h
#define XsStudiesRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
//include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//class XsStudiesRun;
//G4String glob_partName;
//G4double glob_energy;
class G4ParticleDefinition;
class XsStudiesPrimaryGeneratorAction;
class XsStudiesRunAction : public G4UserRunAction {
public: // Without description

    XsStudiesRunAction();
    virtual ~XsStudiesRunAction();
    //    virtual G4Run* GenerateRun();
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

    void CountElastic() {
        numberElastic += 1;
    };

    void CountInElastic() {
        numberinElastic += 1;
    };

private:
    G4double energy;
    G4ParticleDefinition* particle;
    const XsStudiesPrimaryGeneratorAction* primary;
    G4Accumulable<G4int> numberElastic;
    G4Accumulable<G4int> numberinElastic;
    //      XsStudiesRun*          fRun;

};

#endif

