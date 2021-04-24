#include "B4aPhotoDiodeParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"



B4aPhotoDioderParameterisation::B4aPhotoDiodeParameterisation(  
        G4int    noChambers, 
        G4double startZ,          //  Z of center of first 
        G4double spacingZ,        //  Z spacing of centers
        G4double widthChamber, 
        G4double lengthInitial, 
        G4double lengthFinal )
 : G4VPVParameterisation()
{
   fNoChambers =  noChambers; 
   fStartZ     =  startZ; 
   fHalfWidth  =  0.5*widthChamber;
   fSpacing    =  spacingZ;
   fRmaxFirst = 0.5 * lengthInitial; 
   if( noChambers > 0 ){
      fRmaxIncr =  0.5 * (lengthFinal-lengthInitial)/(noChambers-1);
      if (spacingZ < widthChamber) {
         G4Exception("B2bChamberParameterisation::B2bChamberParameterisation()",
                     "InvalidSetup", FatalException,
                     "Width>Spacing");
      }
   }
}



B4aPhotoDiodeParameterisation::~B4aPhotoDiodeParameterisation()
{ }



void B4aPhotoDiodeParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  // Note: copyNo will start with zero!
  G4double Zposition = fStartZ + copyNo * fSpacing;
  G4ThreeVector origin(0,0,Zposition);
  physVol->SetTranslation(origin);
  physVol->SetRotation(0);
}



void B4aPhotoDiodeParameterisation::ComputeDimensions
(G4Tubs& trackerChamber, const G4int copyNo, const G4VPhysicalVolume*) const
{
  // Note: copyNo will start with zero!
  G4double rmax = fRmaxFirst + copyNo * fRmaxIncr;
  trackerChamber.SetInnerRadius(0);
  trackerChamber.SetOuterRadius(rmax);
  trackerChamber.SetZHalfLength(fHalfWidth);
  trackerChamber.SetStartPhiAngle(0.*deg);
  trackerChamber.SetDeltaPhiAngle(360.*deg);
}


