#include <iostream>

#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4aDetectorConstruction.hh"
#include "B4aHistoManager.hh"
#include "G4TrackVector.hh"
#include "G4SteppingManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4DynamicParticle.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "B4aNucleonElasticXS.hh"
#include "G4Material.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4RunManager.hh"

#include "G4Event.hh"

#include "G4ThreeVector.hh"

#include "G4ios.hh"
using namespace std;


B4aSteppingAction::B4aSteppingAction(B4aDetectorConstruction* myDet, B4aEventAction *myEvt, HistoManager *histo):IDold(-1),IDout(-1),fDetector(myDet),fEventAction(myEvt), fHistoManager(histo)
{licznik=0;
preveventNum=0;
}

B4aSteppingAction::~B4aSteppingAction()
{;}



void B4aSteppingAction::UserSteppingAction(const G4Step* astep)
{ 

G4int eventNum = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
if(eventNum>preveventNum)
{
	preveventNum=eventNum;
	licznik=0;
}

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance(); 
    //analysisManager->SetNtupleDirectoryName("stepNtuple");
    G4StepPoint *PreStep = astep->GetPreStepPoint();
    G4StepPoint *PostStep = astep->GetPostStepPoint();
    

    G4TouchableHandle touchPreStep=PreStep->GetTouchableHandle();
    G4TouchableHandle touchPostStep=PostStep->GetTouchableHandle();
    
    G4VPhysicalVolume *volPre1 = touchPreStep->GetVolume();
    G4VPhysicalVolume *volPost1 = touchPostStep->GetVolume();
  
    G4String namePre=volPre1->GetName();
    G4String namePost;
    
    if(volPost1) namePost=volPost1->GetName();
 
    G4int boundFl1=0;
    G4int boundFl2=0;

  // Get Edep
   //G4double Edep = astep->GetTotalEnergyDeposit();
   //G4double Edep = PreStep->GetKineticEnergy()-PostStep->GetKineticEnergy();
   //G4double Edep = astep->GetTotalEnergyDeposit()+(astep->GetTotalEnergyDeposit()-astep->GetNonIonizingEnergyDeposit());
   
   //G4double Edep = fabs(astep->GetDeltaEnergy())+(fabs(astep->GetDeltaEnergy())-astep->GetTotalEnergyDeposit());
   //G4double Edep = astep->GetTotalEnergyDeposit()+(fabs(astep->GetDeltaEnergy())-astep->GetTotalEnergyDeposit());
    //G4double Sec = fabs(astep->GetDeltaEnergy())-astep->GetTotalEnergyDeposit();
    G4double Edep = fabs(astep->GetDeltaEnergy());
    G4double Stepl= astep->GetStepLength();

   // Get Track
    G4Track* aTrack = astep->GetTrack();
    G4VPhysicalVolume* physVol; 
    G4int StNum=aTrack->GetCurrentStepNumber();
    G4int TrackID = aTrack->GetTrackID();
    G4int ParentID = aTrack->GetParentID();
    G4double keCsI1a=-1., keCsI1b=-1.;
    G4double keCsI2a=-1., keCsI2b=-1.;
    //G4double test=0;
  // Get Associated particle
  const G4DynamicParticle * aDynamicParticle = aTrack->GetDynamicParticle();
  G4ParticleDefinition * aParticle = aTrack->GetDefinition();
  G4String ParticleName = aParticle->GetParticleName();

   // Get Touchable History
  //G4TouchableHistory* theTouchable =  (G4TouchableHistory*)(aTrack->GetTouchable());
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)( astep->GetPreStepPoint()->GetTouchable() );

 G4int d = theTouchable->GetHistoryDepth();
 physVol = theTouchable->GetVolume();

 copyNb1=-1;
 copyNb2=-1;
 copyNb3=-1;

 //for (int i=0;i<3;i++) copyNb2[i]=0;
 
 G4int copynb=-1;
 //DetectorLevel(astep);      

 for (int i=d;i>=0;i--){
   //cout<<d<<" "<<i<<" "<<name[d]<<endl;
   //copynb=theTouchable->GetCopyNumber(i);
   //for (int j=0;j<=copynb;j++){
   //G4int nn=theTouchable->GetVolume(i)->GetCopyNo();

   G4String name=theTouchable->GetVolume(i)->GetName();
   G4int copynb=theTouchable->GetCopyNumber(i);
  // cout<<d<<" "<<i<<" "<<name<<" "<<copynb<<" "<<endl;
   
   	
 }
G4String name=theTouchable->GetVolume(0)->GetName();  
 

 // Energy deposit 
 //if(Edep != 0. && aTrack->GetTrackStatus()==fAlive && TrackID<=2 && ParentID==0){
 if(Edep != 0. && aTrack->GetTrackStatus()==fAlive && TrackID<=1 && ParentID==0){

//1-szy krok w danym volumenie
      if (PreStep->GetStepStatus() == fGeomBoundary) boundFl1++;
      //ostatni krok 
      if (PostStep->GetStepStatus() == fGeomBoundary) boundFl2++;

      copyNb1 = theTouchable->GetCopyNumber();

      
      //cout<<"---- "<<namePre<<" "<<namePost<<" "<<Edep<<" "<< boundFl<<endl;	
           
     
      if(strcmp(namePre,"tarTi2PV")==0 && strcmp(namePost,"tarTi2PV")==0)
      //if(strcmp(name,"targ_volPV0")==0 )
	    {
	      //cout<<"********* "<<StNum<<" "<<Edep<<endl;
	      fEventAction->AddHe3(Edep,Stepl);
	      //cout<<"target "<<Edep<<endl;

	      /*
		//secondaties test
	      G4TrackVector trackV = GetSecondariesOfCurrentStep(fpSteppingManager );
	      energySeco=0;
	      for( G4TrackVector::const_iterator ite = trackV.begin(); ite != trackV.end(); ite++ ){
		energySeco += (*ite)->GetKineticEnergy()/MeV;
	      }
	      cout<<"sec: "<<energySeco<<endl;
	      cout<<Edep-astep->GetTotalEnergyDeposit()<<" "<<endl;		 
	      */

	    }

        //cout<<namePre<<" "<<namePost<<endl;
   //    if((strcmp(namePre,"World")==0 && strcmp(namePost,"targetGraPV")==0 && boundFl2) 
   //      ||(strcmp(namePre,"targetGraPV")==0 && strcmp(namePost,"targetGraPV")==0) )
	  //   {
	  //     //cout<<namePre<<" "<<namePost<<" "<<boundFl<<endl;
	  // fEventAction->AddTg2(Edep,Stepl);
	  // //cout<<"target: "<<Edep<<endl;
	  //   };

    if((strcmp(namePre,"tarTi2PV")==0 && strcmp(namePost,"World")==0 && boundFl2) 
        //||(strcmp(namePre,"targetGraPV")==0 && strcmp(namePost,"World")==0 && boundFl2) 
        ||(strcmp(namePre,"World")==0 && strcmp(namePost,"World")==0) )
	    {
	      //cout<<namePre<<" "<<namePost<<" "<<boundFl<<endl;
	  fEventAction->AddAir(Edep,Stepl);
	  //cout<<"target: "<<Edep<<endl;
	    };

	if((strcmp(namePre,"World")==0 && strcmp(namePost,"kr_coatingPV")==0 && boundFl2)
	|| (strcmp(namePre,"kr_coatingPV")==0 && strcmp(namePost,"kr_coatingPV")==0)
	|| (strcmp(namePre,"kr_coatingPV")==0 && strcmp(namePost,"kr_obstaclePV")==0 && boundFl2)
	|| (strcmp(namePre,"kr_obstaclePV")==0 && strcmp(namePost,"kr_obstaclePV")==0)
	|| (strcmp(namePre,"World")==0 && strcmp(namePost,"kr_obstaclePV")==0 && boundFl2)
	|| (strcmp(namePre,"kr_obstaclePV")==0 && strcmp(namePost,"kr_coatingPV")==0 && boundFl2) )
	{
		copyNb1=theTouchable->GetCopyNumber(0);
		fEventAction->AddPlastic(Edep,Stepl,copyNb1);
		// cout<<"energia: "<<Edep<<" "<<"modul = "<<copyNb1<<endl;
	}


      
      if((strcmp(namePre,"krMainPV")==0 && strcmp(namePost,"kr_winAirPV")==0 && boundFl2) 
        ||(strcmp(namePre,"krMainPV")==0 && strcmp(namePost,"kr_housingPV")==0 && boundFl2) 
        ||(strcmp(namePre,"krMainPV")==0 && strcmp(namePost,"krMainPV")==0) )
    	{

	  fEventAction->AddAir(Edep,Stepl);
	  //cout<<"air: "<<Edep<<endl;
	}


      //KRATTA


      //for hadronic reactions inside scintillator - module 14

 // if((strcmp(namePre,"kr_BoxPV")==0 && strcmp(namePost,"krMainPV")==0 && boundFl2) 
    // || (strcmp(namePre,"kr_BoxPV")==0 && strcmp(namePost,"kr_BoxPV")==0)) 


  //   	{
  // 	  //copyNb1 = theTouchable->GetCopyNumber();
	 //  copyNb3=theTouchable->GetCopyNumber(0);
	 //  fEventAction->AddKrCsIs(Edep,Stepl, copyNb3);
	 //  //fEventAction->AddKrHous(Edep,Stepl, copyNb1);
  //       //copyNb3=copyNb1;
	 //  //cout<<"---------- "<<Edep<<" "<<copyNb3<<endl;

		// }




//leci wzdluz obudowy
  if((strcmp(namePre,"kr_housingPV")==0 && strcmp(namePost,"krMainPV")==0 && boundFl2) 
    || (strcmp(namePre,"kr_housingPV")==0 && strcmp(namePost,"kr_housingPV")==0)) 
    	{
  	  //copyNb1 = theTouchable->GetCopyNumber();
        fEventAction->AddKrHous(Edep,Stepl, copyNb1);
        //copyNb3=copyNb1;
	    //cout<<"---------- "<<Edep<<" "<<copyNb1<<endl;
		}


 
   if((strcmp(namePre,"kr_winAirPV")==0 && strcmp(namePost,"kr_winPV")==0 && boundFl2)||
    (strcmp(namePre,"kr_winAirPV")==0 && strcmp(namePost,"kr_winAirPV")==0))     
	{
	  fEventAction->AddAir(Edep,Stepl);

	  //cout<<"air window: "<<Edep<<" "<<namePost<<endl;
  
  if(PreStep->GetStepStatus() == fGeomBoundary||PostStep->GetStepStatus() == fGeomBoundary){
    
	    fHistoManager->FillNtuple(32,aTrack->GetPosition().x());	    
	    fHistoManager->FillNtuple(33,aTrack->GetPosition().y());
	    fHistoManager->FillNtuple(34,aTrack->GetPosition().z());

	    fHistoManager->FillNtuple(35,aTrack->GetMomentum().x());	    
	    fHistoManager->FillNtuple(36,aTrack->GetMomentum().y());
	    fHistoManager->FillNtuple(37,aTrack->GetMomentum().z()); 
            }
	 	};

 //Mylar window
  if((strcmp(namePre,"kr_winPV")==0 && strcmp(namePost,"kr_winAirPV")==0 && boundFl2)
    ||(strcmp(namePre,"kr_winPV")==0 && strcmp(namePost,"kr_winPV")==0) ) 
 //if((strcmp(namePre,"kr_housingPV")==0 && strcmp(namePost,"kr_winAirPV")==0 && boundFl2)||(strcmp(namePre,"kr_winAirPV")==0 && strcmp(namePost,"kr_winAirPV")==0) ) 

	{
	  copyNb1=theTouchable->GetCopyNumber(2);
	  fEventAction->AddKrCuwin(Edep,Stepl,copyNb1);
	  //cout<<"kratta Cu window: "<<Edep<<endl;
	};


  //air layer 1
   if((strcmp(namePre,"AirL1")==0 && strcmp(namePost,"Pdf")==0 && boundFl2)
   ||(strcmp(namePre,"AirL1")==0 && strcmp(namePost,"AirL1")==0) ) 
	{
	  copyNb1=theTouchable->GetCopyNumber(2);
	  fEventAction->AddKrAir1(Edep,Stepl,copyNb1);
	  //cout<<"AirL1: "<<Edep<<endl;
	};
        //air layer2
      if((strcmp(namePre,"AirL2")==0 && strcmp(namePost,"Pdf")==0 && boundFl2)||
         (strcmp(namePre,"AirL2")==0 && strcmp(namePost,"AirL2")==0) ) 
	{
	  copyNb1=theTouchable->GetCopyNumber(2);
	  fEventAction->AddKrAir2(Edep,Stepl, copyNb1);
	  //cout<<"Air2: "<<copyNb1<<" "<<Edep<<endl; 
	}
          //CsI short
      if((strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csi_short")==0)
      ||(strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csi_wr")==0&& boundFl2)
       ) 
	{
	  copyNb3=theTouchable->GetCopyNumber(2);
	  fEventAction->AddKrCsIs(Edep,Stepl, copyNb3);
	  // cout<<"CsI short: "<<copyNb3<<" "<<Edep<<endl;

	};
           //CsI wrapping- problem at the boundary ?
      
    if((strcmp(namePre,"csi_wr")==0 && strcmp(namePost,"csi_long")==0 && boundFl2)
     ||(strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csi_long")==0 && boundFl2)    
     ||(strcmp(namePre,"csi_wr")==0 && strcmp(namePost,"csi_wr")==0)
        ) 
    	{
	  copyNb1=theTouchable->GetCopyNumber(2);
	  
        fEventAction->AddKrCsIswr(Edep,Stepl, copyNb1);
	  //cout<<"wrapping: "<<Edep<<endl;
       };

  //CsI long 
  if((strcmp(namePre,"csi_long")==0 && strcmp(namePost,"csi_Pdf")==0 && boundFl2)
    ||(strcmp(namePre,"csi_long")==0 && strcmp(namePost,"csi_long")==0)) 
      {

	copyNb1=theTouchable->GetCopyNumber(2);
	  fEventAction->AddKrCsIl(Edep,Stepl, copyNb1);
	  //cout<<"Csi_long: "<<Edep<<endl;
	  //if(strcmp(namePre,"csi_wr")==0 && strcmp(namePost,"csi_long")==0 && boundFl)keCsI1b = aTrack->GetKineticEnergy();
	  //if (keCsI1b>-1)	fHistoManager->FillNtuple(39, keCsI1b);

	  // if(strcmp(namePre,"csi_long")==0 && strcmp(namePost,"csi_long")==0)
	 // cout<<"Csi_long: "<<aTrack->GetKineticEnergy()<<endl;
	    //cout<<"Csi_long: "<<keCsI1b<<endl;

      };
	
	//PD  front dead	
	if((strcmp(namePre,"Pdf")==0 && strcmp(namePost,"PdAc")==0 && boundFl2) 
	|| (strcmp(namePre,"Pdf")==0 && strcmp(namePost,"Pdf")==0)) 
	    {
	       //G4int nn=theTouchable->GetVolume(0)->GetCopyNo();
	       G4int nn=PostStep->GetTouchableHandle()->GetVolume(1)->GetCopyNo();
	       //G4String name=theTouchable->GetVolume(0)->GetName();
	       G4String name=PostStep->GetTouchableHandle()->GetVolume(1)->GetName();
	       copyNb1=theTouchable->GetCopyNumber(3);

	       //cout<<"XXXXXXXXXX "<<nn<<" "<<name<<endl;
	       if (strcmp(name,"PD")==0 && nn>-1 )copyNb2=nn;
	       else if (!strcmp(name,"PD")==0 )copyNb2=-1;
	      fEventAction->AddKrPddf(Edep, Stepl, copyNb1, copyNb2);
	      //cout<<"Pdf: "<<copyNb1<<" "<<copyNb2<<" "<<Edep<<endl;
	    };
	
	//PD  active
	if((strcmp(namePre,"PdAc")==0 && strcmp(namePost,"Pdr")==0 && boundFl2)
	|| (strcmp(namePre,"PdAc")==0 && strcmp(namePost,"PdAc")==0)) 
	{

	  G4int nn=PostStep->GetTouchableHandle()->GetVolume(1)->GetCopyNo();
	  G4String name=PostStep->GetTouchableHandle()->GetVolume(1)->GetName();
	     copyNb1=theTouchable->GetCopyNumber(3);  
	  //cout<<"XXXXXXXXXX "<<nn<<" "<<name<<" "<<Edep<<endl;
	       if (strcmp(name,"PD")==0 && nn>-1 )copyNb2=nn;
	       else if (!strcmp(name,"PD")==0 )copyNb2=-1;
	  fEventAction->AddKrPdAc(Edep, Stepl, copyNb1, copyNb2);
	  //cout<<"Pdac: "<<copyNb1<<" "<<copyNb2<<" "<<Edep<<endl;
	  
	};
	//PD  rear dead
      if((strcmp(namePre,"Pdr")==0 && strcmp(namePost,"PdAc")==0 && boundFl2)
    	    ||(strcmp(namePre,"Pdr")==0 && strcmp(namePost,"AirL2")==0 && boundFl2)
    	    ||(strcmp(namePre,"Pdr")==0 && strcmp(namePost,"csi_short")==0 && boundFl2)
    	    || (strcmp(namePre,"Pdr")==0 && strcmp(namePost,"Pdr")==0)) 
	{
	  G4int nn=PostStep->GetTouchableHandle()->GetVolume(1)->GetCopyNo();
	  G4String name=PostStep->GetTouchableHandle()->GetVolume(1)->GetName();
	       copyNb1=theTouchable->GetCopyNumber(3);
	  //cout<<"XXXXXXXXXX "<<nn<<" "<<name<<endl;
	       if (strcmp(name,"PD")==0 && nn>-1 )copyNb2=nn;
	       else if (!strcmp(name,"PD")==0 )copyNb2=-1;
	       fEventAction->AddKrPddr(Edep,Stepl, copyNb1, copyNb2);
	       //if (copyNb2==1) cout<<"Pdr: "<<copyNb1<<" "<<copyNb2<<" "<<Edep<<endl;
	};
     
      //air layer 3 
      if(strcmp(namePre,"AirL3")==0 && strcmp(namePost,"AirL3")==0) 
	{
	  G4int nn=PostStep->GetTouchableHandle()->GetVolume(1)->GetCopyNo();
	  G4String name=PostStep->GetTouchableHandle()->GetVolume(1)->GetName();
	       copyNb1=theTouchable->GetCopyNumber(2);
	  //cout<<"XXXXXXXXXX "<<nn<<" "<<name<<endl;
	       if (strcmp(name,"PD")==0 && nn>-1 )copyNb2=nn;
	       else if (!strcmp(name,"PD")==0 )copyNb2=-1;
	  fEventAction->AddKrAir3(Edep,Stepl, copyNb1);
	   
	};	




      //if(strcmp(namePre,"Pdr")==0 && strcmp(namePost,"csi_short")==0 )keCsI1a = aTrack->GetKineticEnergy();
//if(strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csi_wr")==0 && boundFl==1)keCsI1b = aTrack->GetKineticEnergy();
//if(strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csi_long")==0 )keCsI1b = aTrack->GetKineticEnergy();



  // Get Tracks properties
  
  IDnow = EventNo + 10000*TrackID+ 100000000*ParentID;
  //cout<<"------>>> "<<eventNum<<" "<<ParticleName<<" "<<aParticle->GetPDGEncoding()<<endl;
  //cout<<"00: "<<eventNum<<" ParentID "<<ParentID<<" "<<ParticleName<<" "<<aParticle->GetPDGEncoding()<<" TrackID "<<TrackID<<endl;
  //IDnow = eventNum;
  //if(IDnow != IDold){
      IDold = IDnow;
      
      
      if(copyNb3>-0.5){
	//cout<<"AAAA "<<copyNb3<<endl;
	  fEventAction->fKrNb[copyNb3]++;

	  if (copyNb2<0.)fEventAction->fPdNb[copyNb1][3]++;
	  else fEventAction->fPdNb[copyNb1][copyNb2]++;
      }
	  
	   // Get the primary particle
      if(aTrack->GetCurrentStepNumber()==1 )
	{
	  //fEventAction->fKrNb[copyNb1]=copyNb1;
	    //fEventAction->fpartID=copyNb1;

	  //fHistoManager->FillNtuple(7, copyNb1);
	  //fHistoManager->FillNtuple(14, copyNb2);
	  //fHistoManager->FillNtuple(19, eventNum);
	  //cout<<eventNum<<" "<<aTrack->GetCurrentStepNumber()<<endl;
	  //for (int i=0;i<3;i++)cout<<i<<" "<<fEventAction->fKrNb[i]<<endl;
    //if(copyNb2>0)cout<<eventNum<<" ----->> "<<copynb<<" "<<copyNb1<<" "<<copyNb2<<endl;
	  //cout<<"01: "<<eventNum<<" ParentID "<<ParentID<<" "<<ParticleName<<" TrackID "<<TrackID<<endl;
	  //cout<<"EVENT "<<IDnow<<" "<<IDold<<endl;
	  //cout<<"EVENT "<<eventNum<<endl;
	  //cout<<"StepNb:  "<<aTrack->GetCurrentStepNumber()<<endl;	
	  PrimaryVertex    = aTrack->GetVertexPosition(); 
	  PrimaryDirection = aTrack->GetVertexMomentumDirection();
	  
	  NSecondaries = 1;	  
	  

      // fHistoManager->FillNtuple(39, keCsI2);
G4ParticleDefinition* particleDefinition  = G4ParticleTable::GetParticleTable()->FindParticle("proton");
myXS_test = new B4aNucleonElasticXS(particleDefinition);
	  //Secondaries[NSecondaries][1] = aParticle->GetPDGEncoding();
	  fEventAction->fpartID = -1;

	  if(strcmp(ParticleName,"proton")==0)fEventAction->fpartID = 1;
	  else if(strcmp(ParticleName,"deuteron")==0)fEventAction->fpartID = 2;
	  else if(strcmp(ParticleName,"He3")==0)fEventAction->fpartID = 3;
	  else if(strcmp(ParticleName,"alpha")==0)fEventAction->fpartID = 4;
	  else fEventAction->fpartID = 5;
	  //cout<<"------>>> "<<ParticleName<<" "<<aParticle->GetPDGEncoding()<<endl;
	  //fHistoManager->FillNtuple(21,aParticle->GetPDGEncoding());
	  
	  //Secondaries[NSecondaries][2] = PrimaryVertex.x();
	  //fHistoManager->FillNtuple(22,Secondaries[NSecondaries][2]);

	  double vx=PrimaryVertex.x();
	  double vy=PrimaryVertex.y();
	  double vz=PrimaryVertex.z();
	  // if(vx<0.01&&vx>-0.01||vy<0.01&&vy>-0.01||vz<0.01&&vz>-0.01){
	  // 	cout<<"*******"<<vx<<"*******"<<vy<<"*******"<<vz<<endl;
	  // cout<<"**********"<<aDynamicParticle->GetKineticEnergy()<<endl;
	  // cout<<"********"<<PrimaryDirection.theta()*180./CLHEP::pi<<endl;
	  // }
	  

	  fHistoManager->FillNtuple(20,vx);
	  //cout<<"------>>> "<< PrimaryVertex.x()<<endl;
	  
	  //Secondaries[NSecondaries][3] = PrimaryVertex.y();
	  fHistoManager->FillNtuple(21, vy);
	 

	  //Secondaries[NSecondaries][4] = PrimaryVertex.z();
	  fHistoManager->FillNtuple(22,vz);

	  
	  //Secondaries[NSecondaries][5] = (aDynamicParticle->GetMomentum()).x();
	  fHistoManager->FillNtuple(23,(aDynamicParticle->GetMomentum()).x()); 
	 //cout<<"momentumX:"<<(aDynamicParticle->GetMomentum()).x()<<endl; 
	 
	  
	   //Secondaries[NSecondaries][6] = (aDynamicParticle->GetMomentum()).y();
	  fHistoManager->FillNtuple(24,(aDynamicParticle->GetMomentum()).y());
	  
	  //Secondaries[NSecondaries][7] = (aDynamicParticle->GetMomentum()).z();
	  fHistoManager->FillNtuple(25,(aDynamicParticle->GetMomentum()).z());

	  //Secondaries[NSecondaries][8] = aDynamicParticle->GetTotalMomentum();
	  fHistoManager->FillNtuple(26,aDynamicParticle->GetTotalMomentum());
	  
	  //Secondaries[NSecondaries][9] = aDynamicParticle->GetTotalEnergy();
	  fHistoManager->FillNtuple(27,aDynamicParticle->GetTotalEnergy());
	  	  
	  //Secondaries[NSecondaries][10] = aDynamicParticle->GetKineticEnergy();
	  fHistoManager->FillNtuple(28,aDynamicParticle->GetKineticEnergy());
	  //cout<<"KinEnergy: "<<aDynamicParticle->GetKineticEnergy()<<endl;
	  
	  //Secondaries[NSecondaries][11] = PrimaryVertex.theta()*180./CLHEP::pi;
	  fHistoManager->FillNtuple(29,PrimaryDirection.theta()*180./CLHEP::pi);
	  // cout<<"Theta: "<< PrimaryDirection.theta()*180./CLHEP::pi<<endl;
	  // cout<<"Phi: "<<PrimaryDirection.phi()*180./CLHEP::pi<<endl;
	 // myEventWeight=myXS_test->GetWeight(PrimaryDirection.theta()*180./CLHEP::pi); 
	 // fEventAction->fEventWeight=myEventWeight;

  //cout<<"-------------"<<PrimaryDirection.theta()*180./CLHEP::pi<<" "<<myEventWeight<<endl;
	 

	  //Secondaries[NSecondaries][12] = PrimaryVertex.phi()*180./CLHEP::pi;
	  fHistoManager->FillNtuple(30, PrimaryDirection.phi()*180./CLHEP::pi); 
	  //cout<<"Phi: "<< PrimaryDirection.phi()*180./CLHEP::pi<<endl;
	  //analysisManager->AddNtupleRow(1); 
	  //G4cout << " ****  Primary : " << EventNo << G4endl;
	  //G4cout << " Vertex : " << PrimaryVertex << G4endl;
	//}
      IDold=eventNum;
      
      // Get secondaries in he3 close to the primary tracks (DCA < 2.mm) 
      /*
      G4double DCACut = 2.*mm;
      G4String Material = aTrack->GetMaterial()->GetName();
      G4ThreeVector TrackPos = aTrack->GetVertexPosition();
      
      if(TrackID != 1 && ParentID == 1 && (strcmp(Material,"Air")==0) && (TrackPos.z() > 135.*cm)) 
	{
	  SecondaryVertex = aTrack->GetVertexPosition();
	  SecondaryDirection = aTrack->GetVertexMomentumDirection();
	  
	  // calculate DCA of secondries to primary particle
	  Distance = PrimaryVertex - SecondaryVertex ;
	  VectorProduct = PrimaryDirection.cross(SecondaryDirection);
	  if(VectorProduct == G4ThreeVector() &&  
	     PrimaryDirection != G4ThreeVector() && SecondaryDirection != G4ThreeVector()) 
	    {
	      G4ThreeVector Temp = Distance.cross(PrimaryDirection);
	      VectorProduct = Temp.cross(PrimaryDirection);
	    };	  
	  	  
VectorProductMagnitude = VectorProduct.mag();
	  if(VectorProductMagnitude == 0.) 
	    {
	      VectorProductNorm = G4ThreeVector();
	    } else {
	      VectorProductNorm = (1./VectorProduct.mag()) * VectorProduct ;
	    };	  
	  DistOfClosestApproach = Distance * VectorProductNorm ;
	  
	  if(std::abs(DistOfClosestApproach) < DCACut) 
	    {
	      NSecondaries++;	      
	      Secondaries[0][0] = NSecondaries;
	      Secondaries[NSecondaries][1] = aParticle->GetPDGEncoding();
	      Secondaries[NSecondaries][2] = (aTrack->GetVertexPosition()).x();
	      Secondaries[NSecondaries][3] = (aTrack->GetVertexPosition()).y();
	      Secondaries[NSecondaries][4] = (aTrack->GetVertexPosition()).z();
	      Secondaries[NSecondaries][5] =(aDynamicParticle->GetMomentum()).x(); 
	      Secondaries[NSecondaries][6] = (aDynamicParticle->GetMomentum()).y();
	      Secondaries[NSecondaries][7] = (aDynamicParticle->GetMomentum()).z();
	      Secondaries[NSecondaries][8] = aDynamicParticle->GetTotalMomentum();
	      Secondaries[NSecondaries][9] = aDynamicParticle->GetTotalEnergy();
	      Secondaries[NSecondaries][10] =aDynamicParticle->GetKineticEnergy();
	    };  
	};*/




	}//Edep
  //}//d

    };


      
  // Get the World leaving particle
  /*
  if(aTrack->GetNextVolume() == 0) {
    if(IDnow != IDout) {
      IDout = IDnow;

      NTracks++;

      OutOfWorldTracksData[0][0] = NTracks;

      OutOfWorldTracksData[NTracks][1] = aParticle->GetPDGEncoding();

      OutOfWorldTracksData[NTracks][2] = (aTrack->GetVertexPosition()).x();
      OutOfWorldTracksData[NTracks][3] = (aTrack->GetVertexPosition()).y();
      OutOfWorldTracksData[NTracks][4] = (aTrack->GetVertexPosition()).z();

      OutOfWorldTracksData[NTracks][5] = (aDynamicParticle->GetMomentum()).x();
      OutOfWorldTracksData[NTracks][6] = (aDynamicParticle->GetMomentum()).y();
      OutOfWorldTracksData[NTracks][7] = (aDynamicParticle->GetMomentum()).z();
      
      OutOfWorldTracksData[NTracks][8] = aDynamicParticle->GetTotalMomentum();

      OutOfWorldTracksData[NTracks][9] = aDynamicParticle->GetTotalEnergy();

      OutOfWorldTracksData[NTracks][10] = aDynamicParticle->GetKineticEnergy();      
    };
  };
 */ 
 
	//}


}
void B4aSteppingAction::initialize(G4int Nev) {
  EventNo = Nev;
  NTracks = 0;
  NSecondaries = 0;
  //EdepFCALEm = EdepFCALHad = 0.;
//for (int i =0;i<40;i++)e_dep[i]=0.;


/*
  for(G4int i=0; i<6000; i++)
    {
      for(G4int j=0; j<11; j++) 
	{ 
	  OutOfWorldTracksData[i][j] = 0.;
	  Secondaries[i][j] = 0.; 
	}
    };*/
    }

void B4aSteppingAction::DetectorLevel(const G4Step* aStep) {

//Find number of levels
  G4TouchableHistory* theTouchable = 
  (G4TouchableHistory*)( aStep->GetPreStepPoint()->GetTouchable() );
  G4int level= theTouchable->GetHistoryDepth() + 1;

  //Get name and copy numbers
  //G4TouchableHistory* theTouchable = 
    //(G4TouchableHistory*)( aStep->GetPreStepPoint()->GetTouchable() );
  for ( int ii = 0; ii < level; ii++ ) {
    name[ level - ii - 1 ]   = theTouchable->GetVolume(ii)->GetName();
    copyno[ level - ii - 1 ] = theTouchable->GetCopyNumber(ii);
  
  //cout<<" >>>>>>> "<<level<<" "<<name[level-ii-1]<<" - "<<copyno[level-ii-1]<<endl;
  
  }
 
}

G4TrackVector B4aSteppingAction::GetSecondariesOfCurrentStep(G4SteppingManager* fpSteppingManager )
{
 // number of secondaries in current step
  G4int nSecoStep = fpSteppingManager->GetfN2ndariesAtRestDoIt() + fpSteppingManager->GetfN2ndariesAlongStepDoIt() + fpSteppingManager->GetfN2ndariesPostStepDoIt();
  // list of secondaries since the beginning of track 
  const G4TrackVector* secondaryTracks = fpSteppingManager->GetSecondary();
  G4int nSecoTrack = G4int(secondaryTracks->size());
  // extract the last stepNseco tracks from the list 
  G4int ii;  
  G4TrackVector secondaries;
  for( ii = nSecoTrack-nSecoStep; ii < nSecoTrack; ii++ ){
    secondaries.push_back( (*secondaryTracks)[ii] );
  }

  return secondaries;
}
/*
G4double B4aSteppingAction::GetOutOfWorldTracks(G4int i, G4int j){
  return OutOfWorldTracksData[i][j];
}

G4double B4aSteppingAction::GetSecondaries(G4int i, G4int j){
  return Secondaries[i][j];
}

G4double B4aSteppingAction::GetEdepFCAL(G4String FCAL) {
  if(strcmp(FCAL,"FCALEm") == 0) {
    return EdepFCALEm;
  } else {
    if(strcmp(FCAL,"FCALHad") == 0) {
      return EdepFCALHad;}
  }
  return 0.0; 
} 
*/





