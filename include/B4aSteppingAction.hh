#ifndef B4aSteppingAction_h
#define B4aSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "G4TrackVector.hh"
#include "globals.hh"

class B4aDetectorConstruction;
class B4aPrimaryGenaratorAction;
class B4aEventAction;
class HistoManager;
class B4aNucleonElasticXS;

class B4aSteppingAction : public G4UserSteppingAction
{
  public:
  B4aSteppingAction(B4aDetectorConstruction*, B4aEventAction*, HistoManager*);
    virtual ~B4aSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
  virtual void DetectorLevel(const G4Step*);
  G4TrackVector GetSecondariesOfCurrentStep(G4SteppingManager*);
  G4double Secondaries[20][20];
  int licznik;
  G4int preveventNum;

  private:
  B4aDetectorConstruction *fDetector;
  B4aEventAction *fEventAction;
  HistoManager *fHistoManager;
  B4aNucleonElasticXS *myXS_test;

  
  G4int EventNo;
  G4int copyNb1,copyNb2,copyNb3;
  G4int IDnow, IDold, IDout;
  G4int NTracks, NSecondaries;
  G4double OutOfWorldTracksData[6000][11];
  //Secondaries[6000][13];
  G4double EdepFCALEm, EdepFCALHad;
  G4double e_dep[40];
  G4String name[10];
  G4int copyno[10];
  G4double energySeco;
  G4double myEventWeight; 



  G4ThreeVector PrimaryVertex, PrimaryDirection;
  G4ThreeVector SecondaryVertex, SecondaryDirection;
  G4ThreeVector Distance, VectorProduct, VectorProductNorm;
  G4double VectorProductMagnitude, DistOfClosestApproach;

  public:
  void initialize(G4int);
  G4double GetOutOfWorldTracks(G4int, G4int);
  G4double GetSecondaries(G4int, G4int);
  G4double GetEdepFCAL(G4String);
  
};

#endif

