#include "XsStudiesRun.hh"
#include "XsStudiesSD.hh"
#include "XsStudiesDetectorConstruction.hh"
#include "XsStudiesPrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4HadronicProcessStore.hh"
#include "G4NucleiProperties.hh"
#include "G4StableIsotopes.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4PhysicalConstants.hh"
#include "Analysis.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesRun::XsStudiesRun()
: energy(0),
particle(0),
primary(0),
NrEvents(0),
numberElastic(0),
numberinElastic(0),
G4Run() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesRun::~XsStudiesRun() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesRun::RecordEvent(const G4Event* event) {
    NrEvents++;
    G4int evtNb = event->GetEventID();
    G4Run::RecordEvent(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesRun::Merge(const G4Run* aRun) {
    const XsStudiesRun* localRun = static_cast<const XsStudiesRun*> (aRun);
    primary = dynamic_cast<const XsStudiesPrimaryGeneratorAction*> (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    particle = primary->GetParticleGun()->GetParticleDefinition();
    energy = primary->GetParticleGun()->GetParticleEnergy();
    XsStudiesSD* hadSD = (XsStudiesSD*) G4SDManager::GetSDMpointer()->FindSensitiveDetector("TargetSD");
    hadSD->GetNumberElastic();
    numberElastic += hadSD->GetNumberElastic();
    numberinElastic += hadSD->GetNumberinElastic();
}

void XsStudiesRun::EndOfRun() {
    XsStudiesDetectorConstruction* DetConst = (XsStudiesDetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    G4Material* mat = DetConst->GetTargetMaterial();
    const double rho = mat->GetDensity() / (g / cm3);
    std::string material = mat->GetName();
    int pos = material.find("_");
    G4String elemName = material.substr(pos + 1);
    std::cout << elemName << std::endl;
    const G4Element* element = G4NistManager::Instance()->FindOrBuildElement(elemName);
    const double thickness = DetConst->GetTargetLength();
//    std::cout << element << std::endl;
//    std::cout << "Avogadro * rho * thickness:  " << Avogadro << "  " << "  " << rho << "  " << thickness * mm << std::endl;
    const double aweight = element->GetAtomicMassAmu();
    double convert = aweight / (Avogadro * rho * thickness * 0.1);
    unsigned int numberEvts = G4RunManager::GetRunManager()->GetNumberOfEventsToBeProcessed();
    std::cout << "numberEvts:  " << numberEvts << std::endl;
    std::cout << "numberElastic:  " << numberElastic << std::endl;
    std::cout << "numberinElastic:  " << numberinElastic << std::endl;
    G4HadronicProcessStore* store = G4HadronicProcessStore::Instance();
    double totXs = (1e27 * convert * (numberElastic + numberinElastic)) / numberEvts;
    double elXs = (1e27 * convert * numberElastic) / numberEvts;
    double inelXs = (1e27 * convert * numberinElastic) / numberEvts;
    double errtotXs = totXs * sqrt(numberElastic + numberinElastic) / (numberElastic + numberinElastic);
    double errelXs = elXs * sqrt(numberElastic) / numberElastic;
    double errinelXs = inelXs * sqrt(numberinElastic) / numberinElastic;
    double inelasticXS = 1.e25 * (store->GetInelasticCrossSectionPerAtom(particle, energy, element, mat));
    double elasticXS = 1.e25 * (store->GetElasticCrossSectionPerAtom(particle, energy, element, mat));
    double totalXs = inelasticXS + elasticXS;
    //
    std::cout << "totXs store/calc.:  " << totalXs << " / " << totXs << " +/- " << errtotXs << std::endl;
    std::cout << "elXs store/calc.:  " << elasticXS << " / " << elXs << "+/- " << errelXs << std::endl;
    std::cout << "inelXs store/calc.:  " << inelasticXS << " / " << inelXs << " +/- " << errinelXs << std::endl;
    G4String fParticleName = particle->GetParticleName();
    std::string filename = "XS_" + fParticleName + "_" + material + ".out";
    std::ofstream myfile;
    myfile.open(filename);
    myfile << "-------------------------------" << material << std::endl;
    myfile << "-------------------------------" << fParticleName << std::endl;
    G4String fElementName = material;
    G4double fMinKinEnergy;
    G4double fMaxKinEnergy;
    G4int fBinsE;
    fMinKinEnergy = 0.1 * MeV;
    fMaxKinEnergy = 10 * TeV;
    fBinsE = 800;
    myfile << "### Fill Cross Sections for " << fParticleName
            << " off " << fElementName
            << std::endl;
    myfile << "-------------------------------------------------------------"
            << std::endl;
    myfile << "    N     E(MeV)   Elastic(b)   Inelastic(b)  chargeexc.(b)";
    myfile << "   Total(b)" << std::endl;
    myfile << "-------------------------------------------------------------"
            << std::endl;
    G4cout.precision(4);
    G4double e1 = std::log10(fMinKinEnergy / MeV);
    G4double e2 = std::log10(fMaxKinEnergy / MeV);
    G4double de = (e2 - e1) / G4double(fBinsE);
    G4double x = e1 - de * 0.5;
    G4double e, xs, xtot, xscx;
    G4int i;
    G4double coeff = 1.0;
    if (mat) {
        coeff = mat->GetDensity() * cm2 / g;
    }
    for (i = 0; i < fBinsE; i++) {
        x += de;
        e = std::pow(10., x) * MeV;
        myfile << std::setprecision(5) << std::setw(5) << i << std::scientific << std::setw(12) << e;
        xs = store->GetElasticCrossSectionPerAtom(particle, e, element, mat);
        xtot = xs;
        myfile << std::fixed << std::setprecision(5) << std::setw(12) << xs / barn;
        xs = store->GetInelasticCrossSectionPerAtom(particle, e, element, mat);
        myfile << std::fixed << std::setprecision(5) << std::setw(12) << xs / barn;
        xscx = store->GetChargeExchangeCrossSectionPerAtom(particle, e, element, mat);
        myfile << std::fixed << std::setprecision(5) << std::setw(12) << xscx / barn;
        xtot += xs;
        myfile << " " << std::setw(12) << xtot / barn << std::endl;
    }
    myfile << "-------------------------------------------------------------" << std::endl;
    myfile.close();
    std::string Energy = std::to_string((int) energy) + "MeV";
    std::string filename1 = "XS_" + fParticleName + "_" + material + "_" + Energy + ".root";
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile(filename1);
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
    G4int XsID = analysisManager->CreateNtuple("Cross sections", "Total elastic and inelastic Cross section");
    analysisManager->CreateNtupleDColumn(XsID, "inelasticXS");
    analysisManager->CreateNtupleDColumn(XsID, "elasticXS");
    analysisManager->CreateNtupleDColumn(XsID, "thickness");
    analysisManager->CreateNtupleDColumn(XsID, "radius");
    analysisManager->CreateNtupleDColumn(XsID, "density");
    analysisManager->CreateNtupleDColumn(XsID, "aweight");
    analysisManager->CreateNtupleSColumn(XsID, "material");
    analysisManager->CreateNtupleDColumn(XsID, "enerPrimGen");
    analysisManager->CreateNtupleSColumn(XsID, "PartName");
    analysisManager->CreateNtupleIColumn(XsID, "numberEvts");
    analysisManager->CreateNtupleIColumn(XsID, "numberElastic");
    analysisManager->CreateNtupleIColumn(XsID, "numberinElastic");
    analysisManager->CreateNtupleDColumn(XsID, "totXs");
    analysisManager->CreateNtupleDColumn(XsID, "elXs");
    analysisManager->CreateNtupleDColumn(XsID, "inelXs");
    analysisManager->CreateNtupleDColumn(XsID, "errtotXs");
    analysisManager->CreateNtupleDColumn(XsID, "errelXs");
    analysisManager->CreateNtupleDColumn(XsID, "errinelXs");
    analysisManager->FinishNtuple(XsID);
    //
    analysisManager->FillNtupleDColumn(XsID, 0, inelasticXS);
    analysisManager->FillNtupleDColumn(XsID, 1, elasticXS);
    analysisManager->FillNtupleDColumn(XsID, 2, thickness);
    analysisManager->FillNtupleDColumn(XsID, 3, DetConst->GetRadius());
    analysisManager->FillNtupleDColumn(XsID, 4, rho);
    analysisManager->FillNtupleDColumn(XsID, 5, aweight);
    analysisManager->FillNtupleSColumn(XsID, 6, material);
    analysisManager->FillNtupleDColumn(XsID, 7, energy);
    analysisManager->FillNtupleSColumn(XsID, 8, fParticleName);
    analysisManager->FillNtupleIColumn(XsID, 9, numberEvts);
    analysisManager->FillNtupleIColumn(XsID, 10, numberElastic);
    analysisManager->FillNtupleIColumn(XsID, 11, numberinElastic);
    analysisManager->FillNtupleDColumn(XsID, 12, totXs);
    analysisManager->FillNtupleDColumn(XsID, 13, elXs);
    analysisManager->FillNtupleDColumn(XsID, 14, inelXs);
    analysisManager->FillNtupleDColumn(XsID, 15, errtotXs);
    analysisManager->FillNtupleDColumn(XsID, 16, errelXs);
    analysisManager->FillNtupleDColumn(XsID, 17, errinelXs);
    analysisManager->AddNtupleRow(XsID);
    analysisManager->Write();
    analysisManager->CloseFile();
}

/*
void XsStudiesRun::SetNumberinElastic(unsigned int numberinElastic) {
    this->numberinElastic = numberinElastic;
}

unsigned int XsStudiesRun::GetNumberinElastic() const {
    return numberinElastic;
}

void XsStudiesRun::SetNumberElastic(unsigned int numberElastic) {
    this->numberElastic = numberElastic;
}

unsigned int XsStudiesRun::GetNumberElastic() const {
    return numberElastic;
}

void XsStudiesRun::SetNrEvents(unsigned int NrEvents) {
    this->NrEvents = NrEvents;
}

unsigned int XsStudiesRun::GetNrEvents() const {
    return NrEvents;
}
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
