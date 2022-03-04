#pragma once
#include "G4VUserActionInitialization.hh"

// class XsStudiesDetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
 public:
  ActionInitialization();
  virtual ~ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

 private:
  //  XsStudiesDetectorConstruction *fDetConstruction;
};
