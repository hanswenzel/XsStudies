#pragma once
#include "G4Material.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class XsStudiesDetectorConstructionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XsStudiesDetectorConstruction : public G4VUserDetectorConstruction {
public:
  XsStudiesDetectorConstruction();
  virtual ~XsStudiesDetectorConstruction();

public:
  virtual G4VPhysicalVolume *Construct();
  virtual void ConstructSDandField();
  void SetWorldMaterial(const G4String &);
  void SetTargetMaterial(const G4String &);
  void SetTargetRadius(G4double val);
  void SetTargetLength(G4double val);
  void UpdateGeometry();
  void SetWorldMaterial(G4Material *worldMaterial);
  G4Material *GetWorldMaterial() const;
  void SetTargetMaterial(G4Material *targetMaterial);
  G4Material *GetTargetMaterial() const;
  G4double GetTargetLength() const;
  void SetRadius(G4double radius);
  G4double GetRadius() const;
  void SetDetectorConstructionMessenger(
      XsStudiesDetectorConstructionMessenger *detectorMessenger);
  XsStudiesDetectorConstructionMessenger *
  GetDetectorConstructionMessenger() const;
  void SetLogicWorld(G4LogicalVolume *logicWorld);
  G4LogicalVolume *GetLogicWorld() const;
  void SetLogicTarget(G4LogicalVolume *logicTarget);
  G4LogicalVolume *GetLogicTarget() const;
  void SetDensity(G4double density);
  G4double GetDensity() const;

private:
  XsStudiesDetectorConstruction &
  operator=(const XsStudiesDetectorConstruction &right);
  XsStudiesDetectorConstruction(const XsStudiesDetectorConstruction &);

  G4double radius;
  G4double targetLength;
  G4double density;

  G4Material *targetMaterial;
  G4Material *worldMaterial;

  G4LogicalVolume *logicTarget;
  G4LogicalVolume *logicWorld;

  XsStudiesDetectorConstructionMessenger *detectorMessenger;
};
