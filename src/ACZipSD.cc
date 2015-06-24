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

#include "ACZipSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ACZipSD::ACZipSD(const G4String& name, const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ACZipSD::~ACZipSD() 
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ACZipSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection  = new ACZipHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce

  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool ACZipSD::ProcessHits(G4Step* aStep, 
                                     G4TouchableHistory*)
{  
  // energy deposit
  G4double edep = aStep->GetTotalEnergyDeposit();

  if (edep==0.) return false;

  ACZipHit* newHit = new ACZipHit();


  G4int postproc = 0;
  G4int preproc = 0;
  if (aStep->GetTrack()->GetParentID() == 0){  
    G4String pre = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String post = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

    if (pre ==  "Transportation"){ preproc = 5; }
    if (pre ==  "Rayl"){ preproc = 4; }
    if (pre ==  "compt"){ preproc = 1; }
    if (pre ==  "phot"){ preproc = 2; }
    if (pre ==  "conv"){ preproc = 3; }
     if (post ==  "Transportation"){ postproc = 5; }
    if (post ==  "Rayl"){ postproc = 4; }
    if (post ==  "compt"){ postproc = 1; }
    if (post ==  "phot"){ postproc = 2; }
    if (post ==  "conv"){ postproc = 3; }
    //G4cout << aStep->GetPreStepPoint()->GetKineticEnergy() << "  " << aStep->GetPostStepPoint()->GetKineticEnergy() << G4endl;
    //G4cout << aStep->GetPreStepPoint()->GetKineticEnergy() - aStep->GetPostStepPoint()->GetKineticEnergy() << G4endl;
    //G4cout << aStep->GetDeltaEnergy() << G4endl;
  }


  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetPDGID (aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetTime(aStep->GetPostStepPoint()->GetGlobalTime());
  newHit->SetEdep(aStep->GetTotalEnergyDeposit());
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
  newHit->SetParticleEnergy(aStep->GetPreStepPoint()->GetKineticEnergy()); 
  newHit->SetPreProcess(preproc);
  newHit->SetPostProcess(postproc);

  fHitsCollection->insert( newHit );
  //newHit->Print();

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ACZipSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in the crystal: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
