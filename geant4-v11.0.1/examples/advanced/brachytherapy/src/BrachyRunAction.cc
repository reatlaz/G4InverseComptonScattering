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
//
// --------------------------------------------------------------
//                 GEANT 4 - Brachytherapy example
// --------------------------------------------------------------
//
// Code developed by:
//  S.Guatelli and D. Cutajar
//
//
//    *******************************
//    *                             *
//    *    BrachyRunAction.cc       *
//    *                             *
//    *******************************
//
//

#include "BrachyRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

BrachyRunAction::BrachyRunAction()
{}

BrachyRunAction::~BrachyRunAction()
{}

void BrachyRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
G4cout << "### Run " << aRun -> GetRunID() << " start." << G4endl;

auto analysisManager = G4AnalysisManager::Instance();

G4bool fileOpen = analysisManager -> OpenFile("primary.root");

if (! fileOpen) {
    G4cerr << "\n---> The ROOT output file has not been opened "
           << analysisManager->GetFileName() << G4endl;
  }
  
G4cout << "Using " << analysisManager->GetType() << G4endl;
analysisManager -> SetVerboseLevel(1);

// Create histogram with the energy spectrum of the photons emitted by the
// radionucldie
analysisManager -> CreateH1("h10","energy spectrum", 800, 0., 800.);
}

void BrachyRunAction::EndOfRunAction(const G4Run* aRun)
{ 
G4cout << "number of events = " << aRun->GetNumberOfEvent() << G4endl;
 
// save histograms in primary.root
auto analysisManager = G4AnalysisManager::Instance();
analysisManager -> Write();
analysisManager -> CloseFile();
}




