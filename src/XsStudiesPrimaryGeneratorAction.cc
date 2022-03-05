#include "XsStudiesPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesPrimaryGeneratorAction::XsStudiesPrimaryGeneratorAction()
{
  particleGun = new G4ParticleGun(1);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  particleGun->SetParticlePosition(G4ThreeVector(0., 0., -10. * mm));
  //    G4double ener = particleGun->GetParticleEnergy();
  //    G4ParticleDefinition* part = particleGun->GetParticleDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesPrimaryGeneratorAction::~XsStudiesPrimaryGeneratorAction() { delete particleGun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
