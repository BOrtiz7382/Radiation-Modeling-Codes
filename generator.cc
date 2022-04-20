#include "generator.hh"
#include "G4Box.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include <iostream>
#include <random>
#include <iomanip>

using std::setprecision;

constexpr double MIN = -0.33333333333333;
constexpr double MAX = 0.33333333333333;

MyPrimaryGenerator::MyPrimaryGenerator()
{
fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
G4String particleName = "gamma";
G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

//Location of particle generator in reference to vest
fParticleGun->SetParticlePosition(G4ThreeVector(0.17*m, 0.25*m, 0.5*m));

//Sets each new  particle generation to a new angle to cover different parts of the vest
std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<double> distr(MIN, MAX);

double F = distr(eng), S = distr(eng);
fParticleGun->SetParticleMomentumDirection(G4ThreeVector(F, S*1.5, -1.0));

fParticleGun->SetParticleMomentum(10. *keV);
fParticleGun->SetParticleDefinition(particle);

fParticleGun->GeneratePrimaryVertex(anEvent);
}
