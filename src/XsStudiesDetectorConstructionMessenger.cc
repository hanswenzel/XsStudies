
#include "XsStudiesDetectorConstructionMessenger.hh"

#include "XsStudiesDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesDetectorConstructionMessenger::XsStudiesDetectorConstructionMessenger(XsStudiesDetectorConstruction * Det)
:Detector(Det)
{
  testDir = new G4UIdirectory("/XsStudies/");
  testDir->SetGuidance("Program for Cross section studies.");

  matCmd = new G4UIcmdWithAString("/XsStudies/TargetMat",this);
  matCmd->SetGuidance("Select Material for the target");
  matCmd->SetParameterName("tMaterial",false);
  matCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  mat1Cmd = new G4UIcmdWithAString("/XsStudies/WorldMat",this);
  mat1Cmd->SetGuidance("Select Material for world");
  mat1Cmd->SetParameterName("wMaterial",false);
  mat1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rCmd = new G4UIcmdWithADoubleAndUnit("/XsStudies/TargetRadius",this);
  rCmd->SetGuidance("Set radius of the target");
  rCmd->SetParameterName("radius",false);
  rCmd->SetUnitCategory("Length");
  rCmd->SetRange("radius>0");
  rCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lCmd = new G4UIcmdWithADoubleAndUnit("/XsStudies/TargetLength",this);
  lCmd->SetGuidance("Set length of the target");
  lCmd->SetParameterName("length",false);
  lCmd->SetUnitCategory("Length");
  lCmd->SetRange("length>0");
  lCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dCmd = new G4UIcmdWithADoubleAndUnit("/XsStudies/density",this);
  dCmd->SetGuidance("Set density of the Target in g/cm3");
  dCmd->SetParameterName("density",false);
  dCmd->SetUnitCategory("Density");
  dCmd->SetRange("density>0");
  dCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  updateCmd = new G4UIcmdWithoutParameter("/XsStudies/Update",this);
  updateCmd->SetGuidance("Update geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s)");
  updateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesDetectorConstructionMessenger::~XsStudiesDetectorConstructionMessenger()
{
  delete matCmd;
  delete mat1Cmd;
  delete rCmd;
  delete lCmd;
  delete dCmd;
  delete updateCmd;
  delete testDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesDetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == matCmd )
   Detector->SetTargetMaterial(newValue);
  else if( command == mat1Cmd )
   Detector->SetWorldMaterial(newValue);
  else if( command == rCmd ) 
    Detector->SetTargetRadius(rCmd->GetNewDoubleValue(newValue));
  else if( command == lCmd ) 
    Detector->SetTargetLength(rCmd->GetNewDoubleValue(newValue));
    else if( command == dCmd ) 
    Detector->SetDensity(dCmd->GetNewDoubleValue(newValue));
  else if( command == updateCmd )
    Detector->UpdateGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

