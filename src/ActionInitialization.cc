#include "ActionInitialization.hh"
#include "XsStudiesDetectorConstruction.hh"
#include "XsStudiesEventAction.hh"
#include "XsStudiesPrimaryGeneratorAction.hh"
#include "XsStudiesRunAction.hh"

ActionInitialization::ActionInitialization()
  : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const { SetUserAction(new XsStudiesRunAction); }

void ActionInitialization::Build() const
{
  SetUserAction(new XsStudiesPrimaryGeneratorAction);
  XsStudiesRunAction* runAction = new XsStudiesRunAction();
  SetUserAction(runAction);
  SetUserAction(new XsStudiesEventAction(runAction));
}