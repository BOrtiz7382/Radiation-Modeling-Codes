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
/// \file DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
//#include "G4GDMLParser.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

G4Element *N = nist->FindOrBuildElement("N");
G4Element *O = nist->FindOrBuildElement("O");
G4Material *vac = new G4Material("VACUUM", 0.0000000000000000001*g/cm3, 2);
vac->AddElement(N, 70*perCent);
vac->AddElement(O, 30*perCent);

  // Envelope parameters
  //
  G4double env_sizeXY = 5*m, env_sizeZ = 5*m;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_O");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World

G4Material* world_mat = nist->FindOrBuildMaterial("G4_O");

  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;


  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Envelope
  //

  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
//element definitions
/*
G4Element *S = nist->FindOrBuildElement("S");
G4Element *C = nist->FindOrBuildElement("C");
G4Element *H = nist->FindOrBuildElement("H");
G4Element *Fe = nist->FindOrBuildElement("Fe");
G4Element *Zn = nist->FindOrBuildElement("Zn");
G4Element *Cu = nist->FindOrBuildElement("Cu");
G4Element *Bi = nist->FindOrBuildElement("Bi");
G4Element *Ba = nist->FindOrBuildElement("Ba");
G4Element *W = nist->FindOrBuildElement("W");
G4Element *Mo = nist->FindOrBuildElement("Mo");
G4Element *B = nist->FindOrBuildElement("B");
G4Element *Si = nist->FindOrBuildElement("Si");
G4Element *Co = nist->FindOrBuildElement("Co");

//Composites with their name, density, and number of components
G4Material *composite = new G4Material("TURHAN", 1.5506*g/cm3, 5);
composite->AddElement(Co, 0.0147*perCent);
composite->AddElement(H, 2.3405*perCent);
composite->AddElement(C, 30.5237*perCent);
composite->AddElement(O, 32.8075*perCent);
composite->AddElement(Fe, 34.3136*perCent);

G4Material *composite = new G4Material("HARRISON", 972*kg/m3, 3);
composite->AddElement(B, 1.56526*perCent);
composite->AddElement(H, 14.08098*perCent);
composite->AddElement(C, 84.350376*perCent);

G4Material *composite = new G4Material("ALMURAYSHID", 0.954*g/cm3, 3);
composite->AddElement(W, 14.08005*perCent);
composite->AddElement(H, 12.21603*perCent);
composite->AddElement(C, 73.70392*perCent);

G4Material *composite = new G4Material("ARAL", 2.35*g/cm3, 5);
composite->AddElement(Bi, 60.0*perCent);
composite->AddElement(H, 3.268167723*perCent);
composite->AddElement(C, 12.95402454*perCent);
composite->AddElement(O, 8.628825671*perCent);
composite->AddElement(Si, 15.14898207*perCent);

G4Material *composite = new G4Material("ALMISNED", 1.3649*g/cm3, 6);
composite->AddElement(Co, 0.0291*perCent);
composite->AddElement(H, 3.8446*perCent);
composite->AddElement(C, 50.2655*perCent);
composite->AddElement(O, 29.6796*perCent);
composite->AddElement(Zn, 6.5839*perCent);
composite->AddElement(Cu, 9.5973*perCent);
*/

//Shape 1
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_WATER"); //Material of shield

  G4ThreeVector pos1 = G4ThreeVector(0, 2*cm, -70*cm);

  G4double shape1_dxa = 500*cm, shape1_dxb = 500*cm;
  G4double shape1_dya = 500*cm, shape1_dyb = 500*cm;
  G4double shape1_dz  = 4*mm;
  G4Trd* solidShape1 =
    new G4Trd("Shape1",                      //its name
              0.5*shape1_dxa, 0.5*shape1_dxb,
              0.5*shape1_dya, 0.5*shape1_dyb, 0.5*shape1_dz); //its size

  G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  //
  // Shape 2

  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4ThreeVector pos2 = G4ThreeVector(0, -10*cm, 70*cm);

  //Rectangular prism shape
  G4double shape2_dxa = 500*cm, shape2_dxb = 500*cm;
  G4double shape2_dya = 500*cm, shape2_dyb = 500*cm;
  G4double shape2_dz  = 21*cm;
  G4Trd* solidShape2 =
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb,
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size

  G4LogicalVolume* logicShape2 =
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Set Shape2 as scoring volume
  fScoringVolume = logicShape2;



  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
