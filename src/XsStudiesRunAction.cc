#include "XsStudiesRunAction.hh"
#include "Randomize.hh"
#include "XsStudiesDetectorConstruction.hh"
#include "XsStudiesPrimaryGeneratorAction.hh"
#include "XsStudiesSD.hh"
//
#include "G4Element.hh"
#include "G4Neutron.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "globals.hh"

#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Element.hh"
#include "G4HadronicProcessStore.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4NucleiProperties.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4StableIsotopes.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

XsStudiesRunAction::XsStudiesRunAction()
{
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(numberElastic);
  accumulableManager->RegisterAccumulable(numberinElastic);
  // Create the analysis manager using a new factory method.
  // The choice of analysis technology is done via the function argument.
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  // Default settings
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetFileName("B5");
  //
  // Book histograms, ntuple
  //
  // Creating 1D histograms
  analysisManager->CreateH1("diff", "differental cross section scattering angle ", 100, 0.,
                            25);  // h1 Id = 0
  analysisManager->CreateH1("diff2", "differental cross section scattering angle ", 150, 0.,
                            40);  // h1 Id = 1
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XsStudiesRunAction::~XsStudiesRunAction() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start" << endl;
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  // Open an output file
  analysisManager->OpenFile();
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XsStudiesRunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int nofEvents = aRun->GetNumberOfEvent();
  if(nofEvents == 0)
    return;
  //
  // save histograms & ntuple
  //
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile(false);

  G4String partName;
  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();
  primary = dynamic_cast<const XsStudiesPrimaryGeneratorAction*>(
    G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  // Print results
  //
  if(IsMaster())
  {
    G4cout << G4endl << "--------------------End of Global Run-----------------------" << G4endl;
    G4cout << " Nr of Elastic: " << numberElastic.GetValue() << G4endl;
    G4cout << " Nr of Inelastic: " << numberinElastic.GetValue() << G4endl;
    G4cout << "------------------------------------------------------------" << G4endl;
    // G4cout     << "  The run was " << nofEvents << " eventies of "<<
    XsStudiesDetectorConstruction* DetConst =
      (XsStudiesDetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    G4Material* mat      = DetConst->GetTargetMaterial();
    const double rho     = mat->GetDensity() / (g / cm3);
    std::string material = mat->GetName();
    int pos              = material.find("_");
    G4String elemName    = material.substr(pos + 1);
    std::cout << elemName << std::endl;
    const G4Element* element = G4NistManager::Instance()->FindOrBuildElement(elemName);
    const double thickness   = DetConst->GetTargetLength();
    std::cout << element << std::endl;
    std::cout << "Avogadro * rho * thickness:  " << Avogadro << "  "
              << "  " << rho << "  " << thickness * mm << std::endl;
    std::cout << "Avogadro * rho * thickness:  " << Avogadro << "  "
              << "  " << rho << "  " << thickness * mm << std::endl;
    const double aweight    = element->GetAtomicMassAmu();
    double convert          = aweight / (Avogadro * rho * thickness * 0.1);
    unsigned int numberEvts = G4RunManager::GetRunManager()->GetNumberOfEventsToBeProcessed();
    std::cout << "numberEvts:  " << numberEvts << std::endl;
    G4HadronicProcessStore* store = G4HadronicProcessStore::Instance();
    double totXs =
      (1e27 * convert * (numberElastic.GetValue() + numberinElastic.GetValue())) / numberEvts;
    double elXs     = (1e27 * convert * numberElastic.GetValue()) / numberEvts;
    double inelXs   = (1e27 * convert * numberinElastic.GetValue()) / numberEvts;
    double errtotXs = totXs * sqrt(numberElastic.GetValue() + numberinElastic.GetValue()) /
                      (numberElastic.GetValue() + numberinElastic.GetValue());
    double errelXs     = elXs * sqrt(numberElastic.GetValue()) / numberElastic.GetValue();
    double errinelXs   = inelXs * sqrt(numberinElastic.GetValue()) / numberinElastic.GetValue();
    double inelasticXS = 1.e25 * (store->GetInelasticCrossSectionPerAtom(
                                   primary->GetParticleGun()->GetParticleDefinition(),
                                   primary->GetParticleGun()->GetParticleEnergy(), element, mat));
    double elasticXS   = 1.e25 * (store->GetElasticCrossSectionPerAtom(
                                 primary->GetParticleGun()->GetParticleDefinition(),
                                 primary->GetParticleGun()->GetParticleEnergy(), element, mat));
    double totalXs     = inelasticXS + elasticXS;
    std::cout << "elXs store/calc.:  " << elasticXS << " / " << elXs << "+/- " << errelXs
              << std::endl;
    std::cout << "inelXs store/calc.:  " << inelasticXS << " / " << inelXs << " +/- " << errinelXs
              << std::endl;
    std::cout << "totXs store/calc.:  " << totalXs << " / " << totXs << " +/- " << errtotXs
              << std::endl;
  }
  else
  {
    G4cout << G4endl << "--------------------End of Local Run------------------------" << G4endl;
    G4cout << "  The run was " << nofEvents << " " << partName << G4endl;
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
