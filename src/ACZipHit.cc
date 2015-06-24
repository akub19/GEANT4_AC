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

#include "ACZipHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<ACZipHit>* ACZipHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ACZipHit::ACZipHit()
 : G4VHit(),
   fTrackID(-1),
   fPDGID(0),
   fPreProc(0),
   fPostProc(0),
   fTime(-1),
   fEdep(0.),
   fPos(G4ThreeVector()),
   fEnergy(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ACZipHit::~ACZipHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ACZipHit::ACZipHit(const ACZipHit& right)
  : G4VHit()
{
  fTrackID   = right.fTrackID;
  fPDGID     = right.fPDGID;
  fPreProc   = right.fPreProc;
  fPostProc  = right.fPostProc;
  fTime      = right.fTime;
  fEdep      = right.fEdep;
  fEnergy    = right.fEnergy;
  fPos       = right.fPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ACZipHit& ACZipHit::operator=(const ACZipHit& right)
{
  fTrackID   = right.fTrackID;
  fPDGID     = right.fPDGID;
  fPreProc   = right.fPreProc;
  fPostProc  = right.fPostProc;
  fTime      = right.fTime;
  fEdep      = right.fEdep;
  fEnergy    = right.fEnergy;
  fPos       = right.fPos;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int ACZipHit::operator==(const ACZipHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ACZipHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ACZipHit::Print()
{
  G4cout
     << "  PDG ID: " << fPDGID << " time: " << fTime
     << " Particle Energy: "
     << std::setw(7) << G4BestUnit(fEnergy,"Energy")
     << " Edep: "
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << " Position: "
     << std::setw(7) << G4BestUnit( fPos,"Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
