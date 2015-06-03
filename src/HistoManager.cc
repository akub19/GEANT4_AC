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
/// \file hadronic/Hadr03/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// $Id: HistoManager.cc 83882 2014-09-22 11:09:30Z maire $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("ReverseComptonAnalysis")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  //
  G4AnalysisManager* analysis = G4AnalysisManager::Instance();
  
  analysis->SetFileName(fFileName);
  analysis->SetVerboseLevel(1);
  analysis->SetActivation(true);     //enable inactivation of histos, nTuples
    
  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  //
  analysis->SetHistoDirectoryName("histo");  
  analysis->SetFirstHistoId(1);
    
  G4int id = analysis->CreateH1("h1.1","kinetic energy", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  /*
  analysis->SetNtupleDirectoryName("ntuple");
  analysis->SetFirstNtupleId(1);       
  analysis->CreateNtuple("primaries", "Primary Particle Tuple");
  analysis->CreateNtupleIColumn("particleID");    //column 0
  analysis->CreateNtupleDColumn("Ekin");          //column 1
  analysis->CreateNtupleDColumn("posX");          //column 2
  analysis->CreateNtupleDColumn("posY");          //column 3
  analysis->CreateNtupleDColumn("posZ");          //column 4
  analysis->CreateNtupleDColumn("dirTheta");      //column 5
  analysis->CreateNtupleDColumn("dirPhi");        //column 6
  analysis->FinishNtuple(); 

  analysis->CreateNtuple("ziphits", "Zip Hits Tuple");
  analysis->CreateNtupleIColumn("particleIDzip");    //column 0
  analysis->CreateNtupleDColumn("Edepzip");          //column 1
  analysis->CreateNtupleDColumn("posXzip");          //column 2
  analysis->CreateNtupleDColumn("posYzip");          //column 3
  analysis->CreateNtupleDColumn("posZzip");          //column 4
  analysis->FinishNtuple();

  analysis->CreateNtuple("vetohits", "Veto Hits Tuple");
  analysis->CreateNtupleIColumn("particleIDveto");    //column 0
  analysis->CreateNtupleDColumn("Edepveto");          //column 1
  analysis->CreateNtupleDColumn("posXveto");          //column 2
  analysis->CreateNtupleDColumn("posYveto");          //column 3
  analysis->CreateNtupleDColumn("posZveto");          //column 4
  analysis->FinishNtuple();
  */

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
