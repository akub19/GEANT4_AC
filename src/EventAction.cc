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

#include "EventAction.hh"

#include "TClonesArray.h"


#include "ACZipHit.hh"
#include "ACBaseHit.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"

#include "RootIO.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  
  G4SDManager* fSDM = G4SDManager::GetSDMpointer();
  G4HCofThisEvent* HCofEvent = event->GetHCofThisEvent();
  ACZipHitsCollection*  zipHits = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACZipHitsCollection")));
  ACZipHitsCollection*  vetoHits1 = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACVetoHitsCollection1")));
  ACZipHitsCollection*  vetoHits2 = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACVetoHitsCollection2")));
  ACZipHitsCollection*  vetoHits3 = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACVetoHitsCollection3")));
  //ACZipHitsCollection*  vetoHits4 = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACVetoHitsCollection4")));
  //ACZipHitsCollection*  vetoHits5 = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACVetoHitsCollection5")));
  //ACZipHitsCollection*  vetoHits6 = (ACZipHitsCollection*)(HCofEvent->GetHC(fSDM->GetCollectionID("ACVetoHitsCollection6")));

  RootIO::GetInstance()->AddHits(zipHits,0);
  RootIO::GetInstance()->AddHits(vetoHits1,1);
  RootIO::GetInstance()->AddHits(vetoHits2,2);
  RootIO::GetInstance()->AddHits(vetoHits3,3);
  //RootIO::GetInstance()->AddHits(vetoHits4,4);
  //RootIO::GetInstance()->AddHits(vetoHits5,5);
  //RootIO::GetInstance()->AddHits(vetoHits6,6);
  RootIO::GetInstance()->Write();


/*

  // get number of stored trajectories

  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing
  G4int eventID = event->GetEventID();
  if ( eventID < 100 || eventID % 100 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
    if ( trajectoryContainer ) {
      G4cout << "    " << n_trajectories
             << " trajectories stored in this event." << G4endl;
    }
    G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
    G4cout << "    "  
           << hc->GetSize() << " hits stored in this event" << G4endl;
  }
*/
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
