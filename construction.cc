#include "construction.hh"
#include "G4GDMLParser.hh"

using namespace std;

//Variable for parser
G4GDMLParser parser;

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

//Command to read the gdml file to assigned variable
parser.Read("RPL3.gdml");

//Retrieve volumes and properties from the parser
G4VPhysicalVolume* W = parser.GetWorldVolume();
W->GetLogicalVolume();

return W;
}
