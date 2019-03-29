#ifndef XsStudiesSD_h
#define XsStudiesSD_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// B2Tracker sensitive detector class

class XsStudiesSD : public G4VSensitiveDetector {
public:
    XsStudiesSD(const G4String& name,
            const G4String& hitsCollectionName);
    virtual ~XsStudiesSD();

    // methods from base class
    virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);
    unsigned int GetNumberinElastic() const;
    unsigned int GetNumberElastic() const;

private:
    // we don't create any Hits
    unsigned int numberElastic;
    unsigned int numberinElastic;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
