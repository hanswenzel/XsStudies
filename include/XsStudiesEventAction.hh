
#pragma once
#include "G4UserEventAction.hh"
//#include "globals.hh"
class XsStudiesRunAction;
class XsStudiesEventAction : public G4UserEventAction {
public: // Without description
  XsStudiesEventAction(XsStudiesRunAction *runAction);
  ~XsStudiesEventAction() override;

  void BeginOfEventAction(const G4Event *) override;
  void EndOfEventAction(const G4Event *) override;

private:
  XsStudiesRunAction *fRunAction = nullptr;
};
