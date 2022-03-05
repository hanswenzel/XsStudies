#pragma once
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class XsStudiesSD : public G4VSensitiveDetector
{
 private:
  // we don't create any Hits
  unsigned int numberElastic{ 0 };
  unsigned int numberinElastic{ 0 };

 public:
  XsStudiesSD(const G4String& name, const G4String& hitsCollectionName);
  virtual ~XsStudiesSD();

  // methods from base class
  virtual void Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void EndOfEvent(G4HCofThisEvent* hitCollection);
  unsigned int GetNumberinElastic() const;
  unsigned int GetNumberElastic() const;
};
