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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef GeometryConstruction1_h
#define GeometryConstruction1_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GeometryConstruction : public G4VUserDetectorConstruction
{
  public:
    GeometryConstruction ();
   ~GeometryConstruction ();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();



  private:
    G4VPhysicalVolume* fUniverse_phys;

    G4LogicalVolume*   fLogicDet; 
    G4LogicalVolume*   fLogicVeto1;
    G4LogicalVolume*   fLogicVeto2;
    G4LogicalVolume*   fLogicVeto3;
    //G4LogicalVolume*   fLogicVeto4;
    //G4LogicalVolume*   fLogicVeto5;
    //G4LogicalVolume*   fLogicVeto6;

    G4Material*        fDetMat;
    G4Material*        fVetoMat;



};
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

