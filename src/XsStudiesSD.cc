#include "XsStudiesSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "g4analysis.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4EventManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesSD::XsStudiesSD(const G4String& name,
        const G4String& hitsCollectionName)
: numberElastic(0),
numberinElastic(0),
G4VSensitiveDetector(name) {
}

XsStudiesSD::~XsStudiesSD() {
}

void XsStudiesSD::Initialize(G4HCofThisEvent* hce) {
    (void) hce;
    numberElastic = 0;
    numberinElastic = 0;
}

G4bool XsStudiesSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    //
    // we only care about the first elastic or inelastic interaction of the primary particle
    //
    if (aStep->GetTrack()->GetParentID() == 0) {
        if (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "hadElastic")
	  {
	    G4ThreeVector pa = aStep->GetPostStepPoint()->GetMomentum();
                G4ThreeVector pb = aStep->GetPreStepPoint()->GetMomentum();
                // Get analysis manager
                auto analysisManager = G4AnalysisManager::Instance();
                double angle = pa.angle(pb) / degree;
                analysisManager->FillH1(0, angle);
                numberElastic++;
                aStep->GetTrack()->SetTrackStatus(fStopAndKill);
                return true;
	  }
        if ((aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "pi-Inelastic") ||
                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "pi+Inelastic") ||
                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "protonInelastic") ||
                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "neutronInelastic") ||
                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "kaon-Inelastic") ||
                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "kaon+Inelastic")) {
            numberinElastic++;
            aStep->GetTrack()->SetTrackStatus(fStopAndKill);
            return true;
        }
    }
    return true;
}

void XsStudiesSD::EndOfEvent(G4HCofThisEvent*) {
}

unsigned int XsStudiesSD::GetNumberinElastic() const {
    return numberinElastic;
}

unsigned int XsStudiesSD::GetNumberElastic() const {
    return numberElastic;
}

