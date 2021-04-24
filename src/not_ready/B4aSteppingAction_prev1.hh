
#ifndef B4aSteppingAction_h
#define B4aSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class B4aDetectorConstruction;
class B4aEventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in B4aEventAction.

class B4aSteppingAction : public G4UserSteppingAction
{
public:
  B4aSteppingAction(const B4aDetectorConstruction* detectorConstruction,
                    B4aEventAction* eventAction);
  virtual ~B4aSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
    
private:
  const B4aDetectorConstruction* myDetector;
  B4aEventAction*  fEventAction;  
};



#endif
