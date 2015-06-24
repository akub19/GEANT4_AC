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

#ifndef ACZipHit_h
#define ACZipHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"


class ACZipHit : public G4VHit
{
  public:
    ACZipHit();
    ACZipHit(const ACZipHit&);
    virtual ~ACZipHit();

    // operators
    const ACZipHit& operator=(const ACZipHit&);
    G4int operator==(const ACZipHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetTrackID  (G4int track)      { fTrackID = track; };
    void SetPDGID    (G4int pdgid)      { fPDGID = pdgid; };
    void SetTime     (G4double t2)      { fTime = t2; };
    void SetEdep     (G4double de)      { fEdep = de; };
    void SetPos      (G4ThreeVector xyz){ fPos = xyz; };
    void SetParticleEnergy (G4double e1){ fEnergy = e1; };
    void SetPreProcess (G4int pre)      { fPreProc = pre; };
    void SetPostProcess (G4int post)      { fPostProc = post; };


    // Get methods
    G4int GetTrackID() const     { return fTrackID; };
    G4int GetPDGID() const     { return fPDGID; };
    G4double GetTime() const   { return fTime; };
    G4double GetEdep() const     { return fEdep; };
    G4ThreeVector GetPos() const { return fPos; };
    G4double GetParticleEnergy() const { return fEnergy; };
    G4int GetPreProcess() const  {return fPreProc; };
    G4int GetPostProcess() const  {return fPostProc; };


  private:

      G4int         fTrackID;
      G4int         fPDGID;
      G4int         fPreProc;
      G4int         fPostProc;
      G4double         fTime;
      G4double      fEdep;
      G4ThreeVector fPos;
      G4double      fEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<ACZipHit> ACZipHitsCollection;

extern G4ThreadLocal G4Allocator<ACZipHit>* ACZipHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* ACZipHit::operator new(size_t)
{
  if(!ACZipHitAllocator)
      ACZipHitAllocator = new G4Allocator<ACZipHit>;
  return (void *) ACZipHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void ACZipHit::operator delete(void *hit)
{
  ACZipHitAllocator->FreeSingle((ACZipHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
