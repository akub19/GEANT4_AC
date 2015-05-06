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
// $Id: TrackingAction.cc 81501 2014-05-31 13:51:51Z ldesorgh $
//
/// \file eventgenerator/exgps/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TrackingAction::TrackingAction()
:G4UserTrackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  G4int pid               = track->GetDynamicParticle()->GetPDGcode();
  G4double ekin           = track->GetKineticEnergy();
  G4ThreeVector vertex    = track->GetPosition();
  G4ThreeVector direction = track->GetMomentumDirection();
  G4double weight         = track->GetWeight();
   
  G4double x = vertex.x(), y = vertex.y(), z = vertex.z();
  G4double theta = direction.theta(), phi = direction.phi();
  if (phi < 0.) phi += twopi;
  G4double cost = std::cos(theta);
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
  // fill histograms    
  analysisManager->FillH1(1,ekin);
  
  // fill ntuple  
  analysisManager->FillNtupleIColumn(0,pid);
  analysisManager->FillNtupleDColumn(1,ekin);
  analysisManager->FillNtupleDColumn(2,x);
  analysisManager->FillNtupleDColumn(3,y);
  analysisManager->FillNtupleDColumn(4,z);
  analysisManager->FillNtupleDColumn(5,theta);
  analysisManager->FillNtupleDColumn(6,phi);
  analysisManager->AddNtupleRow();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....





