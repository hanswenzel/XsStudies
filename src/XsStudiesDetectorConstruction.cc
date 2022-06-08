#include "XsStudiesDetectorConstruction.hh"
#include "XsStudiesDetectorConstructionMessenger.hh"
#include "XsStudiesSD.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SDManager.hh"
#include "G4HadronicProcessStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "G4NistManager.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesDetectorConstruction::XsStudiesDetectorConstruction()
{
  logicTarget       = 0;
  logicWorld        = 0;
  detectorMessenger = new XsStudiesDetectorConstructionMessenger(this);

  radius         = 0.3 * cm;
  targetLength   = 4.0 * 0.5 * cm;
  targetMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_C");
  worldMaterial  = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XsStudiesDetectorConstruction::~XsStudiesDetectorConstruction() { delete detectorMessenger; }

G4VPhysicalVolume* XsStudiesDetectorConstruction::Construct()
{
  // Cleanup old geometry

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Sizes
  G4double worldR = radius + 10 * cm;
  G4double worldZ = targetLength + 10. * cm;

  //
  // World
  //
  G4Tubs* solidW = new G4Tubs("World", 0., worldR, worldZ, 0., twopi);
  logicWorld     = new G4LogicalVolume(solidW, worldMaterial, "World");
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);
  //
  // Target volume
  //
  G4Tubs* solidT = new G4Tubs("Target", 0., radius, 0.5 * targetLength, 0., twopi);
  logicTarget    = new G4LogicalVolume(solidT, targetMaterial, "Target");
  new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Target", logicWorld, false, 0);

  // colors
  //    G4VisAttributes zero = G4VisAttributes::Invisible;
  // logicWorld->SetVisAttributes(&zero);

  G4VisAttributes regCcolor(G4Colour(0., 0.3, 0.7));
  logicTarget->SetVisAttributes(&regCcolor);
  density = targetMaterial->GetDensity() / (g / cm3);
  G4cout << " density:  " << density << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  return world;
}

void XsStudiesDetectorConstruction::ConstructSDandField()
{
  G4String SDname         = "TargetSD";
  XsStudiesSD* aTrackerSD = new XsStudiesSD(SDname, "HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Setting aTrackerSD to all logical volumes with the same name
  // of "Target".
  SetSensitiveDetector("Target", aTrackerSD, true);
}  // ConstructSDandFieldScint
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesDetectorConstruction::SetTargetMaterial(const G4String& mat)
{
  // search the material by its name
  G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);
  if(material && material != targetMaterial)
  {
    targetMaterial = material;
    if(logicTarget)
      logicTarget->SetMaterial(targetMaterial);
    density = targetMaterial->GetDensity() / (g / cm3);
    ;
    //      G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4RunManager::GetRunManager()->GeometryHasBeenModified(true);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesDetectorConstruction::SetWorldMaterial(const G4String& mat)
{
  // search the material by its name
  G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);

  if(material && material != worldMaterial)
  {
    worldMaterial = material;
    if(logicWorld)
      logicWorld->SetMaterial(worldMaterial);
    //        G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4RunManager::GetRunManager()->GeometryHasBeenModified(true);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesDetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

void XsStudiesDetectorConstruction::SetWorldMaterial(G4Material* wm) { this->worldMaterial = wm; }

G4Material* XsStudiesDetectorConstruction::GetWorldMaterial() const { return worldMaterial; }

G4Material* XsStudiesDetectorConstruction::GetTargetMaterial() const { return targetMaterial; }

G4double XsStudiesDetectorConstruction::GetTargetLength() const { return targetLength; }

void XsStudiesDetectorConstruction::SetRadius(G4double r) { this->radius = r; }

G4double XsStudiesDetectorConstruction::GetRadius() const { return radius; }

void XsStudiesDetectorConstruction::SetDetectorConstructionMessenger(
  XsStudiesDetectorConstructionMessenger* dm)
{
  this->detectorMessenger = dm;
}

XsStudiesDetectorConstructionMessenger*
XsStudiesDetectorConstruction::GetDetectorConstructionMessenger() const
{
  return detectorMessenger;
}

void XsStudiesDetectorConstruction::SetLogicWorld(G4LogicalVolume* lW) { this->logicWorld = lW; }

G4LogicalVolume* XsStudiesDetectorConstruction::GetLogicWorld() const { return logicWorld; }

void XsStudiesDetectorConstruction::SetLogicTarget(G4LogicalVolume* lT) { this->logicTarget = lT; }

G4LogicalVolume* XsStudiesDetectorConstruction::GetLogicTarget() const { return logicTarget; }

void XsStudiesDetectorConstruction::SetDensity(G4double den)
{
  if(den > 0.0)
    {
      this->density = den;
      G4RunManager::GetRunManager()->GeometryHasBeenModified();
    }
}

G4double XsStudiesDetectorConstruction::GetDensity() const { return density; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesDetectorConstruction::SetTargetRadius(G4double val)
{
  if(val > 0.0)
  {
    radius = val;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XsStudiesDetectorConstruction::SetTargetLength(G4double val)
{
  if(val > 0.0)
  {
    targetLength = val;
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
