#pragma once
#include "G4Accumulable.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"
// include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
// class XsStudiesRun;
// G4String glob_partName;
// G4double glob_energy;
class G4ParticleDefinition;
class XsStudiesPrimaryGeneratorAction;
class XsStudiesRunAction : public G4UserRunAction
{
 public:
  XsStudiesRunAction();
  virtual ~XsStudiesRunAction() override;
  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;
  void CountElastic() { numberElastic += 1; };
  void CountInElastic() { numberinElastic += 1; };

 private:
  //  G4double energy;
  //  G4ParticleDefinition* particle;
  const XsStudiesPrimaryGeneratorAction* primary;
  G4Accumulable<G4int> numberElastic{ 0 };
  G4Accumulable<G4int> numberinElastic{ 0 };
  //      XsStudiesRun*          fRun;
};
