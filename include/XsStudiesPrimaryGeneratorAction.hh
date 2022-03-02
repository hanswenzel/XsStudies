#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XsStudiesPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:
  XsStudiesPrimaryGeneratorAction &
  operator=(const XsStudiesPrimaryGeneratorAction &right);
  XsStudiesPrimaryGeneratorAction(const XsStudiesPrimaryGeneratorAction &);
  G4ParticleGun *particleGun;

public:
  XsStudiesPrimaryGeneratorAction();
  virtual ~XsStudiesPrimaryGeneratorAction();
  void GeneratePrimaries(G4Event *);

  G4ParticleGun *GetParticleGun() const { return particleGun; }
};
