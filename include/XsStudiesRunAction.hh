#pragma once
#include "G4Accumulable.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

// class G4ParticleDefinition;
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
  const XsStudiesPrimaryGeneratorAction* primary;
  G4Accumulable<G4int> numberElastic{ 0 };
  G4Accumulable<G4int> numberinElastic{ 0 };
};
