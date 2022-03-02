
#pragma once
#include "G4UserEventAction.hh"
#include "globals.hh"
class XsStudiesRunAction;

class XsStudiesEventAction : public G4UserEventAction {
public: // Without description
  XsStudiesEventAction(XsStudiesRunAction *runAction);
  virtual ~XsStudiesEventAction();

  void BeginOfEventAction(const G4Event *);
  void EndOfEventAction(const G4Event *);

private:
  XsStudiesRunAction *fRunAction;
};
