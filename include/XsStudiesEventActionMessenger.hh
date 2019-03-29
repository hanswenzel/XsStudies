
#ifndef XsStudiesEventActionMessenger_h
#define XsStudiesEventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class XsStudiesEventAction;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XsStudiesEventActionMessenger: public G4UImessenger
{
public:

  XsStudiesEventActionMessenger(XsStudiesEventAction*);
  virtual ~XsStudiesEventActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:

  XsStudiesEventAction*          eventAction;   
  G4UIcmdWithAString*   drawCmd;
  G4UIcmdWithAnInteger* printCmd;    
  G4UIcmdWithAnInteger* dCmd;    

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
