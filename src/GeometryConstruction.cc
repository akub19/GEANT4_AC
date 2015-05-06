//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: GeometryConstruction.cc 67272 2013-02-13 12:05:47Z ihrivnac $
//
/// \file eventgenerator/exgps/src/GeometryConstruction.cc
/// \brief Implementation of the GeometryConstruction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "GeometryConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "ACZipSD.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "G4GeometryManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeometryConstruction::GeometryConstruction()
: G4VUserDetectorConstruction(),
  fUniverse_phys(0)
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeometryConstruction::~GeometryConstruction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeometryConstruction::ConstructSDandField()
{ 

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  // Sensitive detectors

  // central zip-like Si or Ge Crystal  
  G4String detSDname = "/AntiCompton/Zip";
  G4String hitsName = "ACZipHitsCollection";
  ACZipSD* aZipSD = new ACZipSD(detSDname, hitsName);
  SDman->AddNewDetector(aZipSD);
  SetSensitiveDetector("Zip_log", aZipSD, true);
  

  // anti-compton setup
  G4String vetoSDname = "/AntiCompton/Veto";
  G4String hitsNameVeto = "ACVetoHitsCollection";
  // should probably write a separate class for the SD/hits for this guy in case we
  // want to store different info in the hits or change the physics behavior in the volume
  ACZipSD* aVeto1SD = new ACZipSD(vetoSDname+"1", hitsNameVeto+"1");
  SDman->AddNewDetector(aVeto1SD);
  SetSensitiveDetector("Veto1_log", aVeto1SD, true);

  ACZipSD* aVeto2SD = new ACZipSD(vetoSDname+"2", hitsNameVeto+"2");
  SDman->AddNewDetector(aVeto2SD);
  SetSensitiveDetector("Veto2_log", aVeto2SD, true);

  ACZipSD* aVeto3SD = new ACZipSD(vetoSDname+"3", hitsNameVeto+"3");
  SDman->AddNewDetector(aVeto3SD);
  SetSensitiveDetector("Veto3_log", aVeto3SD, true);

  ACZipSD* aVeto4SD = new ACZipSD(vetoSDname+"4", hitsNameVeto+"4");
  SDman->AddNewDetector(aVeto4SD);
  SetSensitiveDetector("Veto4_log", aVeto4SD, true);

  ACZipSD* aVeto5SD = new ACZipSD(vetoSDname+"5", hitsNameVeto+"5");
  SDman->AddNewDetector(aVeto5SD);
  SetSensitiveDetector("Veto5_log", aVeto5SD, true);

  ACZipSD* aVeto6SD = new ACZipSD(vetoSDname+"6", hitsNameVeto+"6");
  SDman->AddNewDetector(aVeto6SD);
  SetSensitiveDetector("Veto6_log", aVeto6SD, true);


}


G4VPhysicalVolume* GeometryConstruction::Construct()
{
  //
  //
  // Define materials.
  //
  G4NistManager* nistManager = G4NistManager::Instance();
  
  fDetMat  = nistManager->FindOrBuildMaterial("G4_Si");
  fVetoMat   = nistManager->FindOrBuildMaterial("G4_Si");
  
  G4Material* air  = nistManager->FindOrBuildMaterial("G4_AIR");

  G4bool fCheckOverlaps = true;


  //
  // Define size of world and volumes in it.
  //
  G4double world_r = 25*cm;
  G4double detRad = 56.0*mm; // from chamber center to center!
  G4double detHalfZ = 20.0*mm; // width of the chambers


  // Define bodies, logical volumes and physical volumes.
  // First define the experimental hall.
  //
  G4Sphere * universe_s  = new G4Sphere("universe_s", 0, world_r, 0, twopi, 0, pi);
  G4LogicalVolume * universe_log = new G4LogicalVolume(universe_s,air,"universe_L",0,0,0);
  fUniverse_phys = new G4PVPlacement(0,G4ThreeVector(),"universe_P",universe_log,0,false,0);



  // zip-like detector
  G4ThreeVector positionTarget = G4ThreeVector(0,0,0);

  G4VSolid* zip1 = new G4Tubs("Zip1",0.,detRad,detHalfZ,0,360*deg);


  fLogicDet = new G4LogicalVolume(zip1, fDetMat,"Zip_log");
  new G4PVPlacement(0,               // no rotation
                    positionTarget,  // at (x,y,z)
                    fLogicDet,    // its logical volume
                    "Zip_phys",        // its name
                    universe_log,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    fCheckOverlaps); // checking overlaps 


  // anti-compton veto detector                    
  // box setup, 6 detectors around the zip
  G4VSolid* veto1 = new G4Box("Veto1", 40.*mm, 5*mm, detHalfZ);
  G4VSolid* veto2 = new G4Box("Veto2", 40.*mm, 5*mm, detHalfZ);
  G4VSolid* veto3 = new G4Box("Veto3", 40.*mm, 5*mm, detHalfZ);
  G4VSolid* veto4 = new G4Box("Veto4", 40.*mm, 5*mm, detHalfZ);
  G4VSolid* veto5 = new G4Box("Veto5", 40.*mm, 5*mm, detHalfZ);
  G4VSolid* veto6 = new G4Box("Veto6", 40.*mm, 5*mm, detHalfZ);

  // probably over-complicated way to position the boxes around the zip
  // G4ThreeVector zCent(0, 0, 0);

  G4double rot = (M_PI/3.)*rad;
  G4double rzip = (detRad+20.)*mm;

  G4RotationMatrix* yRot1 = new G4RotationMatrix;  // Rotates X and Z axes only
  yRot1->rotateZ(-1*rot + 0.5*M_PI);
  G4ThreeVector zTrans1(cos(rot)*rzip,sin(rot)*rzip, 0);

  G4RotationMatrix* yRot2 = new G4RotationMatrix;  // Rotates X and Z axes only
  yRot2->rotateZ(-2.*rot + 0.5*M_PI);
  G4ThreeVector zTrans2(cos(2.*rot)*rzip,sin(2.*rot)*rzip, 0);

  G4RotationMatrix* yRot3 = new G4RotationMatrix;  // Rotates X and Z axes only
  yRot3->rotateZ(-3.*rot + 0.5*M_PI);
  G4ThreeVector zTrans3(cos(3.*rot)*rzip,sin(3.*rot)*rzip, 0);

  G4RotationMatrix* yRot4 = new G4RotationMatrix;  // Rotates X and Z axes only
  yRot4->rotateZ(-4.*rot + 0.5*M_PI);
  G4ThreeVector zTrans4(cos(4.*rot)*rzip,sin(4.*rot)*rzip, 0);

  G4RotationMatrix* yRot5 = new G4RotationMatrix;  // Rotates X and Z axes only
  yRot5->rotateZ(-5.*rot + 0.5*M_PI);
  G4ThreeVector zTrans5(cos(5.*rot)*rzip,sin(5.*rot)*rzip, 0);

  G4RotationMatrix* yRot6 = new G4RotationMatrix;  // Rotates X and Z axes only
  yRot6->rotateZ(-6.*rot + 0.5*M_PI);
  G4ThreeVector zTrans6(cos(6.*rot)*rzip,sin(6.*rot)*rzip, 0);


  fLogicVeto1 = new G4LogicalVolume(veto1, fVetoMat,"Veto1_log");
  new G4PVPlacement(yRot1,           // no rotation
                    zTrans1,         // at (x,y,z)
                    fLogicVeto1,     // its logical volume
                    "Veto1_phys",    // its name
                    universe_log,    // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    fCheckOverlaps); // checking overlaps 

  fLogicVeto2 = new G4LogicalVolume(veto2, fVetoMat,"Veto2_log");
  new G4PVPlacement(yRot2,zTrans2,fLogicVeto2,"Veto2_phys",universe_log,false,0,fCheckOverlaps);

  fLogicVeto3 = new G4LogicalVolume(veto3, fVetoMat,"Veto3_log");
  new G4PVPlacement(yRot3,zTrans3,fLogicVeto3,"Veto3_phys",universe_log,false,0,fCheckOverlaps);

  fLogicVeto4 = new G4LogicalVolume(veto4, fVetoMat,"Veto4_log");
  new G4PVPlacement(yRot4,zTrans4,fLogicVeto2,"Veto4_phys",universe_log,false,0,fCheckOverlaps);

  fLogicVeto5 = new G4LogicalVolume(veto5, fVetoMat,"Veto5_log");
  new G4PVPlacement(yRot5,zTrans5,fLogicVeto5,"Veto5_phys",universe_log,false,0,fCheckOverlaps);

  fLogicVeto6 = new G4LogicalVolume(veto6, fVetoMat,"Veto6_log");
  new G4PVPlacement(yRot6,zTrans6,fLogicVeto6,"Veto6_phys",universe_log,false,0,fCheckOverlaps);
    
  
//--------- Visualization attributes -------------------------------
  universe_log->SetVisAttributes(G4VisAttributes::Invisible);
  G4VisAttributes* aVisAttDet= new G4VisAttributes(G4Colour(0,1.0,1.0));
  G4VisAttributes* aVisAttVeto= new G4VisAttributes(G4Colour(1.0,0,1.0));

  //aVisAtt->SetForceSolid(true);
  fLogicDet->SetVisAttributes(aVisAttDet);
  fLogicVeto1->SetVisAttributes(aVisAttVeto);
  fLogicVeto2->SetVisAttributes(aVisAttVeto);
  fLogicVeto3->SetVisAttributes(aVisAttVeto);
  fLogicVeto4->SetVisAttributes(aVisAttVeto);
  fLogicVeto5->SetVisAttributes(aVisAttVeto);
  fLogicVeto6->SetVisAttributes(aVisAttVeto);

  return fUniverse_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
