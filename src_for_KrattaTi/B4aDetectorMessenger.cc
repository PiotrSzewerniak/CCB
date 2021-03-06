#include "B4aDetectorMessenger.hh"
#include "B4aDetectorConstruction.hh"

#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"

using namespace std;


B4aDetectorMessenger::B4aDetectorMessenger(B4aDetectorConstruction *myDet)
  :G4UImessenger(),myDetector(myDet)
{


//////////////////////////////
// Directory
//////////////////////////////

  paramDir = new G4UIdirectory("/param/");
  paramDir->SetGuidance("Detector control.");
  
  generationDir=new G4UIdirectory("/generator/");
  generationDir->SetGuidance("Generator settings");

  TargetDir =new G4UIdirectory("/param/target/");
  TargetDir->SetGuidance("Target sizes for generator");

//////////////////////////////
// Generation Parameters
//////////////////////////////

  //NpdChoiceCmd = new G4UIcmdWithAnInteger("/param/npd_choice",this);
  //NpdChoiceCmd->SetGuidance("Choice of process: 1 - elast. dp, 2 - break-up, 0 - elast uniform., -1 - p.");

  // IfNeumannCmd = new G4UIcmdWithAnInteger("/param/neumann",this);
  //IfNeumannCmd->SetGuidance("Only for npd_choice==2, Sets the method of generation \n 0-uniform, 1-using cross section tables");

  BfwhmX_Cmd = new G4UIcmdWithADouble("/param/bfwhmx",this);
  BfwhmX_Cmd->SetGuidance("Beam FWHMs x.");

  BfwhmY_Cmd = new G4UIcmdWithADouble("/param/bfwhmy",this);
  BfwhmY_Cmd->SetGuidance("Beam FWHMs y.");

  BtEnergyCmd = new G4UIcmdWithADoubleAndUnit("/param/bt",this);
  BtEnergyCmd->SetGuidance("Beam energy in MeV.");
  BtEnergyCmd->SetDefaultUnit("MeV");

  Pz_Cmd = new G4UIcmdWithADouble("/param/pz",this);
  Pz_Cmd->SetGuidance("Polarization Pz.");

  Pzz_Cmd = new G4UIcmdWithADouble("/param/pzz",this);
  Pzz_Cmd->SetGuidance("Polarization Pzz.");

  ThetaMinCmd = new G4UIcmdWithADoubleAndUnit("/param/themin",this);
  ThetaMinCmd->SetGuidance("Theta generation min.");
  ThetaMinCmd->SetDefaultUnit("deg");

  ThetaMaxCmd = new G4UIcmdWithADoubleAndUnit("/param/themax",this);
  ThetaMaxCmd->SetGuidance("Theta generation max.");
  ThetaMaxCmd->SetDefaultUnit("deg");

  Theta2MinCmd = new G4UIcmdWithADoubleAndUnit("/param/the2min",this);
  Theta2MinCmd->SetGuidance("Theta 2 generation min.");
  Theta2MinCmd->SetDefaultUnit("deg");

  Theta2MaxCmd = new G4UIcmdWithADoubleAndUnit("/param/the2max",this);
  Theta2MaxCmd->SetGuidance("Theta 2 generation max.");
  Theta2MaxCmd->SetDefaultUnit("deg");

  PhiMinCmd = new G4UIcmdWithADoubleAndUnit("/param/phimin",this);
  PhiMinCmd->SetGuidance("Phi generation min.");
  PhiMinCmd->SetDefaultUnit("deg");

  PhiMaxCmd = new G4UIcmdWithADoubleAndUnit("/param/phimax",this);
  PhiMaxCmd->SetGuidance("Phi generation max.");
  PhiMaxCmd->SetDefaultUnit("deg");
  
  ParamUpdate = new G4UIcmdWithoutParameter("/param/update",this);

//////////////////////////////
// Target
//////////////////////////////

  //TargetIsCmd = new G4UIcmdWithAnInteger("/geom/target/is",this);
  //TargetIsCmd->SetGuidance("If  Target is =1 , if not =0");
  //TargetIsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TargetOutRadiusCmd = new G4UIcmdWithADoubleAndUnit("/param/target/radius",this);
  TargetOutRadiusCmd->SetGuidance("Set Half-dimensions radius of the Target");
  TargetOutRadiusCmd->SetDefaultUnit("mm");

  
  TargetHighCmd = new G4UIcmdWithADoubleAndUnit("/param/target/high",this);
  TargetHighCmd->SetGuidance("Set Half-dimensions Z-high of the Target");
  TargetHighCmd->SetDefaultUnit("mm");


// Target placement
  TargetXplaceCmd = new G4UIcmdWithADoubleAndUnit("/param/target/place_x",this);
  TargetXplaceCmd->SetGuidance("Target X axis");
  TargetXplaceCmd->SetDefaultUnit("mm");


  TargetYplaceCmd = new G4UIcmdWithADoubleAndUnit("/param/target/place_y",this);
  TargetYplaceCmd->SetGuidance("Target  Y axis");
  TargetYplaceCmd->SetDefaultUnit("mm");


  TargetZplaceCmd = new G4UIcmdWithADoubleAndUnit("/param/target/place_z",this);
  TargetZplaceCmd->SetGuidance("Target Z axis");
  TargetZplaceCmd->SetDefaultUnit("mm");


///////////////////////////
//generator
///////////////////////////

  GenMinCmd=new G4UIcmdWithADouble("/generator/min",this);
  GenMinCmd->SetGuidance("Use to set the lowest S to be generated");

  GenMaxCmd=new G4UIcmdWithADouble("/generator/max",this);
  GenMaxCmd->SetGuidance("Use to set the highest S to be generated");
}

B4aDetectorMessenger::~B4aDetectorMessenger()
{
//////////////////////////////
// Generation Parameters
//////////////////////////////

  //delete NpdChoiceCmd;
  delete IfNeumannCmd;
  delete BfwhmX_Cmd;
  delete BfwhmY_Cmd;
  delete BtEnergyCmd;
  delete Pz_Cmd;
  delete Pzz_Cmd;
  delete ThetaMinCmd;
  delete ThetaMaxCmd;
  delete Theta2MinCmd;
  delete Theta2MaxCmd;
  delete PhiMinCmd;
  delete PhiMaxCmd;
  delete  ParamUpdate;
  delete GenMinCmd;
  delete GenMaxCmd;
}

void B4aDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{

//////////////////////////////
// Generation Parameters
//////////////////////////////

  //if(command==NpdChoiceCmd)
  //myDetector->SetNpdChoice(NpdChoiceCmd->GetNewIntValue(newValues));
  if(command==IfNeumannCmd)
    myDetector->SetNeumann(IfNeumannCmd->GetNewIntValue(newValues));
  else if(command==BfwhmX_Cmd)
    myDetector->SetBfwhmX(BfwhmX_Cmd->GetNewDoubleValue(newValues));
  else if(command==BfwhmY_Cmd)
    myDetector->SetBfwhmY(BfwhmY_Cmd->GetNewDoubleValue(newValues));
  else if(command==BtEnergyCmd)
    myDetector->SetBtEnergy(BtEnergyCmd->GetNewDoubleValue(newValues));
  else if(command==Pz_Cmd)
    myDetector->SetPz(Pz_Cmd->GetNewDoubleValue(newValues));
  else if(command==Pzz_Cmd)
    myDetector->SetPzz(Pzz_Cmd->GetNewDoubleValue(newValues));
  else if(command==ThetaMinCmd){
    myDetector->SetThetaMin(ThetaMinCmd->GetNewDoubleValue(newValues));
    //cout<<"XXXXXXXXXXXXXXX "<<ThetaMinCmd->GetNewDoubleValue(newValues)<<endl;
  }
  else if(command==ThetaMaxCmd)
    myDetector->SetThetaMax(ThetaMaxCmd->GetNewDoubleValue(newValues));
  else if(command==Theta2MinCmd)
    myDetector->SetTheta2Min(Theta2MinCmd->GetNewDoubleValue(newValues));
  else if(command==Theta2MaxCmd)
    myDetector->SetTheta2Max(Theta2MaxCmd->GetNewDoubleValue(newValues));
  else if(command==PhiMinCmd)
    myDetector->SetPhiMin(PhiMinCmd->GetNewDoubleValue(newValues));
  else if(command==PhiMaxCmd)
    myDetector->SetPhiMax(PhiMaxCmd->GetNewDoubleValue(newValues));
   else if(command==ParamUpdate)
    myDetector->SetParamUpdate();//runManager
//////////////////////////////
// Target
//////////////////////////////
  //else if(command==TargetIsCmd)
  //myDetector->SetTargetIs(TargetIsCmd->GetNewIntValue(newValues));
   if(command==TargetOutRadiusCmd)
    myDetector->SetTargetOutRadius(TargetOutRadiusCmd->GetNewDoubleValue(newValues));

  else if(command==TargetHighCmd)
    myDetector->SetTargetHigh(TargetHighCmd->GetNewDoubleValue(newValues));
// Target placement
  else if(command==TargetXplaceCmd)
    myDetector->SetTargetXplace(TargetXplaceCmd->GetNewDoubleValue(newValues));
  else if(command==TargetYplaceCmd)
    myDetector->SetTargetYplace(TargetYplaceCmd->GetNewDoubleValue(newValues));
  else if(command==TargetZplaceCmd)
    myDetector->SetTargetZplace(TargetZplaceCmd->GetNewDoubleValue(newValues));

}

