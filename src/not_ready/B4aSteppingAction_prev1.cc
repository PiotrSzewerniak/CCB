#include <iostream>

#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4aDetectorConstruction.hh"
#include "B4aHistoManager.hh"

#include "G4SteppingManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4DynamicParticle.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"

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
{;}

B4aSteppingAction::~B4aSteppingAction()
{;}



void B4aSteppingAction::UserSteppingAction(const G4Step* astep)
{ 

G4int eventNum = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

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
 
    G4int boundFl=0;

  // Get Edep
   G4double Edep = astep->GetTotalEnergyDeposit();
   G4double Stepl= astep->GetStepLength();

   // Get Track
    G4Track* aTrack = astep->GetTrack();
    G4VPhysicalVolume* physVol; 


   // Get Touchable History
     //G4TouchableHistory* theTouchable =  (G4TouchableHistory*)(aTrack->GetTouchable());
G4TouchableHistory* theTouchable = (G4TouchableHistory*)( astep->GetPreStepPoint()->GetTouchable() );

 G4int d = theTouchable->GetHistoryDepth();
 physVol = theTouchable->GetVolume();

 copyNb1=-1;
copyNb2=-1;

 //for (int i=0;i<3;i++) copyNb2[i]=0;
 
 G4int copynb=-1;
 //DetectorLevel(astep);      

 for (int i=d;i>=0;i--){
   //cout<<d<<" "<<i<<" "<<name[d]<<endl;
   //copynb=theTouchable->GetCopyNumber(i);
   //for (int j=0;j<=copynb;j++){
   //G4int nn=theTouchable->GetVolume(i)->GetCopyNo();

   //G4String name=theTouchable->GetVolume(i)->GetName();
   G4int copynb=theTouchable->GetCopyNumber(i);
   //cout<<d<<" "<<i<<" "<<name<<" "<<copynb<<" "<<endl;
   
   //if(strcmp(name,"PD0")==0) copyNb2[0]=1;	   	    
   //if(strcmp(name,"PD1")==0) copyNb2[1]=1;	
   //if(strcmp(name,"PD2")==0) copyNb2[2]=1;	
 }
  
 

 // Energy deposit 
  if(Edep != 0.) 
    {
      if (PostStep->GetStepStatus() == fGeomBoundary) boundFl++;
      copyNb1 = theTouchable->GetCopyNumber();

      
      //cout<<"---- "<<namePre<<" "<<namePost<<" "<<Edep<<" "<< boundFl<<endl;	
           
     
      if(strcmp(namePre,"targ_volPV0")==0 && strcmp(namePost,"targ_volPV0")==0)
	    {

	 fEventAction->AddHe3(Edep,Stepl);
	 
	    }

        //cout<<namePre<<" "<<namePost<<endl;
      if((strcmp(namePre,"targ_volPV0")==0 && strcmp(namePost,"World")==0 && boundFl==1) ||(strcmp(namePre,"World")==0 && strcmp(namePost,"World")==0) )
	    {
	      //cout<<namePre<<" "<<namePost<<" "<<boundFl<<endl;
	  fEventAction->AddAir(Edep,Stepl);
	  
	    };

      
      if((strcmp(namePre,"World")==0 && strcmp(namePost,"krMainPV")==0 && boundFl==1) || (strcmp(namePre,"krMainPV")==0 && strcmp(namePost,"krMainPV")==0) )
    	{

	  fEventAction->AddAir(Edep,Stepl);
	}


      //KRATTA

      if((strcmp(namePre,"krMainPV")==0 && strcmp(namePost,"kr_housingPV")==0 && boundFl==1) || (strcmp(namePre,"kr_housingPV")==0 && strcmp(namePost,"kr_housingPV")==0)) 
    	{

	  if(PreStep->GetStepStatus() == fGeomBoundary){
    
	    fHistoManager->FillNtuple(34,aTrack->GetPosition().x());	    
	    fHistoManager->FillNtuple(35,aTrack->GetPosition().y());
	    fHistoManager->FillNtuple(36,aTrack->GetPosition().z());

	    fHistoManager->FillNtuple(37,aTrack->GetMomentum().x());	    
	    fHistoManager->FillNtuple(38,aTrack->GetMomentum().y());
	    fHistoManager->FillNtuple(39,aTrack->GetMomentum().z()); 
            }
	  	  
	 
	  //copyNb1 = theTouchable->GetCopyNumber();
	     
         
         
	    fEventAction->AddKrHous(Edep,Stepl, copyNb1);
	    //cout<<"----------"<<Edep<<" "<<copyNb1<<endl;
	    //cout<<"---------- "<<copyNb1<<endl;
	    }


   //Cu-window

   if(strcmp(namePre,"krMainPV")==0 && strcmp(namePost,"AirL1")==0 && boundFl==1)     
	{
	  fEventAction->AddKrCuwin(Edep,Stepl, copyNb1);

	  //cout<<"Kratta Cu window: "<<Edep<<endl;
  
	};

  //air layer 1
      if(strcmp(namePre,"AirL1")==0 && strcmp(namePost,"AirL1")==0 ) 
	{
	  fEventAction->AddKrAir1(Edep,Stepl,copyNb1);
	  //cout<<"AirL1: "<<Edep<<endl;
	};

   //PD0
      /*   
      if(copyNb2[0] && (strcmp(namePre,"AirL1")==0 && strcmp(namePost,"PD0")==0 && boundFl==1) || (strcmp(namePre,"PD0")==0 && strcmp(namePost,"PD0")==0)) 
	    {
	   
	
	   copyNb2[0]=0;	   	    
	
	   
	    fEventAction->AddKrPd(Edep,Stepl,copyNb1, copyNb2);
	    //cout<<copyNb1<<" "<<Edep<<endl;
	}
      */
	//front Cu window
     //G4StepPoint *prePoint1= astep->GetPreStepPoint(); 
     //G4StepPoint *prePoint2= astep->GetPostStepPoint(); 
     //G4String kr_win1=prePoint1->GetPhysicalVolume()->GetName() ;
     //G4String kr_win2=prePoint2->GetPhysicalVolume()->GetName() ;
  
     //cout<<"----------"<<namePre<<" "<<namePost<<endl;
     //copyNb1 = prePoint1->GetTouchableHandle()->GetCopyNumber();
    	

        //air layer2
      if((strcmp(namePre,"Pdr")==0 && strcmp(namePost,"AirL2")==0 && boundFl==1) || (strcmp(namePre,"AirL2")==0 && strcmp(namePost,"AirL2")==0) ) 
	{

	  fEventAction->AddKrAir2(Edep,Stepl, copyNb1);
	  //cout<<" xxxxxxxxxx"<<copyNb1<<" "<<Edep<<endl; 
	};
       

      //PD1 
      /*
      //if((strcmp(namePre,"AirL2")==0 && strcmp(namePost,"PD1")==0 && boundFl==1) || (strcmp(namePre,"PD1")==0 && strcmp(namePost,"PD1")==0)) 
 if(strcmp(name,"PD1")==0) 
	    {
	    //G4StepPoint *prePoint2 = astep->GetPreStepPoint();
	     //copyNb2 = PreStep->GetTouchableHandle()->GetCopyNumber();
	
	   copyNb2=1;
	    
	   	    
	    fEventAction->AddKrPd(Edep,Stepl,copyNb1, copyNb2);
	    //cout<<"PD1: "<<Edep<<endl;
	}
      */
   //CsI short
        if((strcmp(namePre,"Pdr")==0 && strcmp(namePost,"csi_short")==0 && boundFl==1) ||(strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csi_short")==0)) 
	{
	  fEventAction->AddKrCsIs(Edep,Stepl, copyNb1);
	   //cout<<"CsI short: "<<copyNb1<<" "<<Edep<<endl;
	};
    
           //CsI short wrapping
        if((strcmp(namePre,"csi_short")==0 && strcmp(namePost,"csiwr")==0 && boundFl==1) || (strcmp(namePre,"csiwr")==0 && strcmp(namePost,"csiwr")==0)) 
	{
	  fEventAction->AddKrCsIswr(Edep,Stepl, copyNb1);
	   	
	};

  //CsI long 
        if((strcmp(namePre,"csiwr")==0 && strcmp(namePost,"csi_long")==0 && boundFl==1) ||(strcmp(namePre,"csi_long")==0 && strcmp(namePost,"csi_long")==0)) 
	{
	  fEventAction->AddKrCsIl(Edep,Stepl, copyNb1);
	  // cout<<Edep<<endl;
	   
	};

	/*
	//if((strcmp(namePre,"csi_long")==0 && strcmp(namePost,"PD2")==0 && boundFl==1) || (strcmp(namePre,"PD2")==0 && strcmp(namePost,"PD2")==0) ) 
if(strcmp(name,"PD2")==0) 
	    {
	    //G4StepPoint *prePoint2 = astep->GetPreStepPoint();
	     //copyNb2 = PreStep->GetTouchableHandle()->GetCopyNumber();
	
	   copyNb2=2;
	   	    
	    fEventAction->AddKrPd(Edep,Stepl,copyNb1, copyNb2);
	    	}
	
	*/	
	//PD  front dead	
	if((strcmp(namePre,"AirL1")==0 && strcmp(namePost,"Pdf")==0 && boundFl==1 ) ||(strcmp(namePre,"AirL2")==0 && strcmp(namePost,"Pdf")==0 && boundFl==1) || (strcmp(namePre,"csi_long")==0 && strcmp(namePost,"Pdf")==0 && boundFl==1) || (strcmp(namePre,"Pdf")==0 && strcmp(namePost,"Pdf")==0)) 
	    {
	       //G4int nn=theTouchable->GetVolume(0)->GetCopyNo();
	       G4int nn=PostStep->GetTouchableHandle()->GetVolume(1)->GetCopyNo();
	       //G4String name=theTouchable->GetVolume(0)->GetName();
	       G4String name=PostStep->GetTouchableHandle()->GetVolume(1)->GetName();
	       
	       cout<<"XXXXXXXXXX "<<nn<<" "<<name<<endl;
	      fEventAction->AddKrPddf(Edep, Stepl, copyNb1, copyNb2);
	      //cout<<"Pdf: "<<copyNb1<<" "<<copyNb2<<" "<<Edep<<endl;
	    };
	
	//PD  active
	if((strcmp(namePre,"Pdf")==0 && strcmp(namePost,"PdAc")==0 && boundFl==1)|| (strcmp(namePre,"PdAc")==0 && strcmp(namePost,"PdAc")==0)) 
	{

	  fEventAction->AddKrPdAc(Edep, Stepl, copyNb1, copyNb2);
         if (copyNb2==1) cout<<"Pdac: "<<copyNb1<<" "<<copyNb2<<" "<<Edep<<endl;
	  
	};
	//PD  rear dead
      if((strcmp(namePre,"PdAc")==0 && strcmp(namePost,"Pdr")==0 && boundFl==1)|| (strcmp(namePre,"Pdr")==0 && strcmp(namePost,"Pdr")==0)) 
	{
	  fEventAction->AddKrPddr(Edep,Stepl, copyNb1, copyNb2);
	  if (copyNb2==1) cout<<"Pdr: "<<copyNb1<<" "<<copyNb2<<" "<<Edep<<endl;
	};

      
    
      
         //CsI long wrapping
        //if(strcmp(name,"csi_longwr") == 0 ) 
	//{
	  //fEventAction->AddKrCsIlwr(Edep,Stepl, copyNb1);
	   
	//};
     
      //air layer 3 
      if((strcmp(namePre,"PD2")==0 && strcmp(namePost,"AirL3")==0 && boundFl==1)|| (strcmp(namePre,"AirL3")==0 && strcmp(namePost,"AirL3")==0)) 
	{
	  fEventAction->AddKrAir3(Edep,Stepl, copyNb1);
	   
	};	

       

	}//Edep
  //}//d


   
  // Get Tracks properties
    G4int TrackID = aTrack->GetTrackID();
    G4int ParentID = aTrack->GetParentID();

  // Get Associated particle
  const G4DynamicParticle * aDynamicParticle = aTrack->GetDynamicParticle();
  G4ParticleDefinition * aParticle = aTrack->GetDefinition();
  G4String ParticleName = aParticle->GetParticleName();
  
  IDnow = EventNo + 10000*TrackID+ 100000000*ParentID;
  //cout<<"------>>> "<<eventNum<<" "<<ParticleName<<" "<<aParticle->GetPDGEncoding()<<endl;
  //cout<<"00: "<<eventNum<<" ParentID "<<ParentID<<" "<<ParticleName<<" "<<aParticle->GetPDGEncoding()<<" TrackID "<<TrackID<<endl;
  //IDnow = eventNum;
  //if(IDnow != IDold){
      IDold = IDnow;
      
      
      if(copyNb1>-0.5){
	//cout<<"AAAA "<<copyNb1<<endl;
	  fEventAction->fKrNb[copyNb1]++;

	  if (copyNb2<0.)fEventAction->fPdNb[copyNb1][4]++;
	  else fEventAction->fPdNb[copyNb1][copyNb2]++;
      }
	  
	   // Get the primary particle
      if(TrackID<=2  && ParentID==0 && (aTrack->GetCurrentStepNumber()) == 1)
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
	  
	  //Secondaries[NSecondaries][1] = aParticle->GetPDGEncoding();
	  fEventAction->fpartID = -1;
	  if(strcmp(ParticleName,"proton")==0)fEventAction->fpartID = 1;
	  if(strcmp(ParticleName,"He3")==0)fEventAction->fpartID = 2;
	  
	  //cout<<"------>>> "<<ParticleName<<" "<<aParticle->GetPDGEncoding()<<endl;
	  //fHistoManager->FillNtuple(21,aParticle->GetPDGEncoding());
	  
	  //Secondaries[NSecondaries][2] = PrimaryVertex.x();
	  //fHistoManager->FillNtuple(22,Secondaries[NSecondaries][2]);
	  fHistoManager->FillNtuple(22,PrimaryVertex.x());
	  //cout<<"------>>> "<< PrimaryVertex.x()<<endl;
	  
	  //Secondaries[NSecondaries][3] = PrimaryVertex.y();
	  fHistoManager->FillNtuple(23, PrimaryVertex.y());
	 

	  //Secondaries[NSecondaries][4] = PrimaryVertex.z();
	  fHistoManager->FillNtuple(24,PrimaryVertex.z());
	  
	  //Secondaries[NSecondaries][5] = (aDynamicParticle->GetMomentum()).x();
	  fHistoManager->FillNtuple(25,(aDynamicParticle->GetMomentum()).x()); 
	 //cout<<"momentumX:"<<(aDynamicParticle->GetMomentum()).x()<<endl; 
	 
	  
	   //Secondaries[NSecondaries][6] = (aDynamicParticle->GetMomentum()).y();
	  fHistoManager->FillNtuple(26,(aDynamicParticle->GetMomentum()).y());
	  
	  //Secondaries[NSecondaries][7] = (aDynamicParticle->GetMomentum()).z();
	  fHistoManager->FillNtuple(27,(aDynamicParticle->GetMomentum()).z());

	  //Secondaries[NSecondaries][8] = aDynamicParticle->GetTotalMomentum();
	  fHistoManager->FillNtuple(28,aDynamicParticle->GetTotalMomentum());
	  
	  //Secondaries[NSecondaries][9] = aDynamicParticle->GetTotalEnergy();
	  fHistoManager->FillNtuple(29,aDynamicParticle->GetTotalEnergy());
	  	  
	  //Secondaries[NSecondaries][10] = aDynamicParticle->GetKineticEnergy();
	  fHistoManager->FillNtuple(30,aDynamicParticle->GetKineticEnergy());
	  //cout<<"KinEnergy: "<<aDynamicParticle->GetKineticEnergy()<<endl;
	  
      //Secondaries[NSecondaries][11] = PrimaryVertex.theta()*180./CLHEP::pi;
	  fHistoManager->FillNtuple(31,PrimaryDirection.theta()*180./CLHEP::pi);
	  //cout<<"Theta: "<< PrimaryDirection.theta()*180./CLHEP::pi<<endl;
	  
	  //Secondaries[NSecondaries][12] = PrimaryVertex.phi()*180./CLHEP::pi;
	  fHistoManager->FillNtuple(32, PrimaryDirection.phi()*180./CLHEP::pi); 
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





