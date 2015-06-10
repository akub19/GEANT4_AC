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
/// \file persistency/P01/src/RootIO.cc
/// \brief Implementation of the RootIO class
//
// $Id: RootIO.cc 82130 2014-06-11 09:26:44Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <sstream>

#include "RootIO.hh"
#include "RootIOMessenger.hh"
#include "ACBaseHit.hh"
#include "ACBaseTrack.hh"
//
#include "Cintex/Cintex.h"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

static RootIO* instance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::RootIO():fileName("hits.root")
{

  fMessenger = new RootIOMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::~RootIO()
{}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Setup()
{

  theFile = new TFile(fileName,"RECREATE");
  theFile->cd();
  theTree  = new TTree("theTree", "go climb one");
  sHits  = new TClonesArray("ACBaseHit");
  theTree->Branch("sHits",&sHits, 6400, 0);
  hitC = 0;
  sTracks  = new TClonesArray("ACBaseTrack");
  theTree->Branch("sTracks",&sTracks, 6400, 0);
  trackC = 0;

  theTree->Branch("hitC",&hitC,"hitC/I");
  theTree->Branch("trackC",&trackC,"trackC/I");
  theTree->Branch("event",&event,"event/I");
  theTree->Branch("eInc",&eInc,"eInc/F");
  theTree->Branch("eVetoTop",&eVetoTop,"eVetoTop/F");
  theTree->Branch("eVetoBot",&eVetoBot,"eVetoBot/F");
  theTree->Branch("eVetoRing",&eVetoRing,"eVetoRing/F");
  theTree->Branch("eDet",&eDet,"eDet/F");
  hitC = 0;
  trackC = 0;
  event = 1;
  eInc = 0.;
  eVetoTop = 0;
  eVetoBot = 0;
  eVetoRing = 0;
  eDet = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void RootIO::SetFileName(G4String file)
{
  fileName = file;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4String RootIO::GetFileName()
{
  return fileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO* RootIO::GetInstance()
{
  if (instance == 0 )
  {
    instance = new RootIO();
  }
  return instance;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::AddHits(ACZipHitsCollection * zipHits, G4int detID)
{
  for (G4int i = 0; i < zipHits->entries(); i++){
    ACBaseHit* hit = new ((*sHits)[hitC]) ACBaseHit;
    G4ThreeVector vec = (*zipHits)[i]->GetPos();
    hit->SetPos(vec.x(),vec.y(),vec.z());
    hit->SetEdep((*zipHits)[i]->GetEdep());
    hit->SetPid((*zipHits)[i]->GetPDGID());
    hit->SetDetID(detID);
    hit->SetTime((*zipHits)[i]->GetTime());
    hit->SetInc(0);
    hitC++;
    if (detID == 0) { eDet += (*zipHits)[i]->GetEdep(); }
    if (detID == 1) { eVetoRing += (*zipHits)[i]->GetEdep(); }
    if (detID == 2) { eVetoTop += (*zipHits)[i]->GetEdep(); }
    if (detID == 3) { eVetoBot += (*zipHits)[i]->GetEdep(); }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::AddTrack(const G4Track*  trk)
{

  G4double ekin           = trk->GetKineticEnergy();
  G4double weight         = trk->GetWeight();

  G4ThreeVector vertex    = trk->GetPosition();
  G4double x = vertex.x(), y = vertex.y(), z = vertex.z();

  G4ThreeVector mom = trk->GetMomentum();
  G4double px = mom.x(), py = mom.y(), pz = mom.z();

  if (trk->GetParentID() == 0) { eInc = trk->GetTotalEnergy(); }

  ACBaseTrack* tr = new ((*sTracks)[trackC]) ACBaseTrack;
  tr->Setp4(px,py,pz,trk->GetTotalEnergy());
  tr->SetPos(x,y,z);
  tr->SetPid(trk->GetDynamicParticle()->GetPDGcode());
  tr->SetTime(trk->GetGlobalTime());
  tr->SetInc(trk->GetParentID());
  trackC++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Write()
{

  event++;
  theTree->Fill();
  sHits->Clear();
  sTracks->Clear();
  hitC = 0;
  trackC = 0;
  eDet = 0;
  eVetoTop = 0;
  eVetoBot = 0;
  eVetoRing = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Close()
{
   theFile->cd();
   theFile->Write();
   theFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
