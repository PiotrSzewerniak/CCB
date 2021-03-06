#include "B4aEventAction.hh"
#include "B4aRunAction.hh"
#include "B4aAnalysis.hh"
#include "B4aHistoManager.hh"
#include "B4aPrimaryGeneratorAction.hh"
#include "B4aSteppingAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"
#include <iomanip>
using namespace std;


B4aEventAction::B4aEventAction(HistoManager *histo)//,B4aPrimaryGeneratorAction *myPrimaryGA )
  : G4UserEventAction(),fHistoManager(histo),    
    fEnergyHe3(0.),fEventWeight(0.),
  fEnergyPyrex(0.),
  fEnergySwin1(0.),
  fEnergySwin2(0.),
  fEnergyFwin1(0.),
  fEnergyFwin2(0.),
  fEnergyAir(0.),
  fpartID(0.)

   
{
Vx= 0.;
Vy= 0.;
Vz= 0.;
}

B4aEventAction::~B4aEventAction()
{}

void B4aEventAction::BeginOfEventAction(const G4Event* evt)
{  
  // initialisation per event
  
  fEnergyHe3 = 0.;
  fEnergyTg2 = 0.;
  fEnergyPyrex = 0.;
  fEnergySwin1 = 0.; 
  fEnergySwin2  = 0.;
  fEnergyFwin1  = 0.;
  fEnergyFwin2 = 0.;
  fEnergyAir = 0.;

  maxDet=28;



  for (int i=0;i<50;i++){

    for (int j=0;j<4;j++){
      
      fEnergyPddf[i][j]=0;
      fEnergyPddr[i][j]=0.;
      fEnergyPdac[i][j]=0.;
      fEnergyPd[i][j]=0.;
    
      fTrackLPd[i][j]=0.;
      fTrackLPddf[i][j]=0.;
      fTrackLPddr[i][j]=0.;
      fTrackLPdac[i][j]=0;
      fPdNb[i][j]=-1;
    }
    
    fEnergyKrHouse[i]=0.;
    fEnergyCuwin[i]=0.;
    fEnergyAir1[i]=0.;
    fEnergyAir2[i]=0.;
    fEnergyAir3[i]=0.;
    fEnergyPlastic[i]=0.;
    
    fKrNb[i]=-1;
    
    fEnergyCsIl[i]=0.;
    fEnergyCsIlwr[i]=0.;
    fEnergyCsIs[i]=0.;
    fEnergyCsIswr[i]=0.;
    
    fTrackLPlastic[i]=0.;
    fTrackLKrHouse[i]=0.;
    fTrackLCuwin[i]=0.;
    fTrackLAir1[i]=0.;
    fTrackLAir2[i]=0.;
    fTrackLAir3[i]=0.;
    
    fTrackLCsIl[i]=0.;
    fTrackLCsIlwr[i]=0.;
    fTrackLCsIs[i]=0.;
    fTrackLCsIswr[i]=0.;
    
  }
  

}



void B4aEventAction::EndOfEventAction(const G4Event* event)
{
 
 //cout<<":::::: "<<fpartID<<endl;
 
 
  // Accumulate statistics
 
//    Vx=myPGA->GetVertexX();
  const G4ThreeVector &pos=event->GetPrimaryVertex()->GetPosition();
  Vx=pos.x();
  Vy=pos.y();
  //Vz=pos.z();
  

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
  // fill histograms
  //analysisManager->FillH1(1, Vx);
  //analysisManager->FillH1(2, Vy);
  //analysisManager->FillH1(3, Vz);
  //analysisManager->FillH1(4, fTrackLGap);
  //cout<<"------->>>> EventAction: "<<Vx<<" "<<Vy<<" "<<Vz<<endl; 
  G4int kr_nb=0, pb_nb[]={0};
  
  // fill ntuple
for (int i=0;i<maxDet;i++ ){
    
      if(fKrNb[i]>-0.5)kr_nb++;

      /* 
for (int j=0;j<3;j++ ){
   
     if(fPdNb[i][j]>0)pb_nb++;

    
     }*/
  //cout<<"--------->>>> "<<kr_nb<<endl;    
 }
 

  
//cout<<"------->>>> fEventWeight: "<<fEventWeight<<endl; 

 if(kr_nb==1){
 
  fHistoManager->FillNtuple(0, fEnergyHe3);
  fHistoManager->FillNtuple(11, fEnergyTg2);
  fHistoManager->FillNtuple(12, fEventWeight);

  //fHistoManager->FillNtuple(1, fEnergyPyrex);
  //fHistoManager->FillNtuple(2, fEnergySwin1);
  //fHistoManager->FillNtuple(3, fEnergySwin2);
  //fHistoManager->FillNtuple(4, fEnergyFwin1);
  //fHistoManager->FillNtuple(5, fEnergyFwin2);
  fHistoManager->FillNtuple(31, fEnergyAir);  
  fHistoManager->FillNtuple(19, fpartID);  
  
  
  //cout<<"------->>>> fEnergyPyrex: "<<fEnergyPyrex<<endl; 
  //cout<<"------->>>> fEnergyHe3: "<<fEnergyHe3<<" "<<fpartID<<endl; 
  //cout<<"------->>>> fEnergySwin1: "<<fEnergySwin1<<endl; 
   
 
  // cout<<"------->>>> fEventWeight: "<<fEventWeight<<endl; 


  for (int i=0;i<maxDet;i++ ){

    for (int j=0;j<2;j++ ){

    
      //if(fEnergyPd[i][j])
	//fHistoManager->FillNtuple(10, fEnergyPd[i][j]);
      if(fEnergyPddf[i][j]){
	if(j==0)fHistoManager->FillNtuple(5, fEnergyPddf[i][j]);
	else if(j==1)fHistoManager->FillNtuple(8, fEnergyPddf[i][j]);
            }
      if(fEnergyPddr[i][j])
	{
      if(j==0)fHistoManager->FillNtuple(6, fEnergyPddr[i][j]);
      else if(j==1)fHistoManager->FillNtuple(9, fEnergyPddr[i][j]);
	}
      if(fEnergyPdac[i][j]){
      if(j==0)fHistoManager->FillNtuple(7, fEnergyPdac[i][j]);
      if(j==1)fHistoManager->FillNtuple(10, fEnergyPdac[i][j]);
      }

      if(fEnergyPddf[i][j] && fEnergyPddr[i][j] &&fEnergyPdac[i][j] ){
	
	
	//if(j==0)fHistoManager->FillNtuple(11, j);
	//else if(j==1)fHistoManager->FillNtuple(12, j);
	
	//cout<<i<<" "<<j<<" "<<fPdNb[i][j]<<endl;
      
      }
      if (fPdNb[i][j]==-1) {
	//cout<<fPdNb[i][j]<<endl;
	//fHistoManager->FillNtuple(11, -1);
	//fHistoManager->FillNtuple(12, -1);

}
      

    }
    /*     
    for (int i=0;i<kr_nb;i++ ){
      cout<<pb_nb[i]<<endl;

      if(pb_nb[i]==2){
	
	fHistoManager->FillNtuple(8, 1);
	fHistoManager->FillNtuple(8, 2);
      }   
      else {
	fHistoManager->FillNtuple(8, -1);
	fHistoManager->FillNtuple(8, -1);

}


} */
   

    //if(fEnergyKrHouse[i])
    fHistoManager->FillNtuple(1, fEnergyKrHouse[i]);  
    if(fKrNb[i]>-0.5){
    fHistoManager->FillNtuple(2, i);    
    //cout<<"----------------< "<<i<<endl;
    
    //if(fEnergyCuwin[i])
    fHistoManager->FillNtuple(3, fEnergyCuwin[i]);
    //if(fEnergyAir1[i])
    fHistoManager->FillNtuple(4, fEnergyAir1[i]);
    //if(fEnergyAir2[i])
    fHistoManager->FillNtuple(13, fEnergyAir2[i]);
    //if(fEnergyCsIs[i])
    fHistoManager->FillNtuple(14, fEnergyCsIs[i]);
    //if(fEnergyCsIs[i])cout<<i<<" "<<fEnergyCsIs[i]<<endl;
    //cout<<"csi: "<<i<<" "<<fEnergyCsIs[i]<<endl;
    //if(fEnergyCsIswr[i])
    fHistoManager->FillNtuple(15, fEnergyCsIswr[i]);
    //if(fEnergyCsIl[i])
    fHistoManager->FillNtuple(16, fEnergyCsIl[i]);
    //if(fEnergyAir3[i])
    fHistoManager->FillNtuple(18, fEnergyAir3[i]);

    fHistoManager->FillNtuple(38, fEnergyPlastic[i]);
    }

  }
 





  //analysisManager->AddNtupleRow(1);
  //analysisManager1->FillNtupleDColumn(1, Vy);
  //analysisManager1->FillNtupleDColumn(2, Vz);
  //analysisManager->FillNtupleDColumn(25, Vy);
  //analysisManager->FillNtupleDColumn(26, Vz);
  
  //analysisManager->FillNtupleDColumn(3, fTrackLGap);
  
  //fHistoManager->FillNtuple(25, Vy);
  //fHistoManager->FillNtuple(26, Vz);
 
 //analysisManager->FillNtupleDColumn(27, fTrackLGap);
  // Print per event (modulo n)
  //
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  //if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
  G4cout << "---> End of event: " << eventID << G4endl;     
  //G4cout << "---> Vx: " << pos.x() << G4endl;     
  fHistoManager->FillNtuple(17,G4double(eventID));
 
 
  analysisManager->AddNtupleRow(1);
 
 }
 

 //}



  //const G4Event* evt = fpEventManager->get_const_currentEvent();

//G4EventManager *fpEventManager;
/*
  event= fpEventManager->get_const_currentEvent();
  G4SDManager * SDman = G4SDManager::get_SDMpointer();
  G4String colNam;
  G4int trackerCollID = SDman->get_collectionID(colNam="TrackerCollection");
  G4int calorimeterCollID = SDman->get_collectionID(colNam="CalCollection");
  G4TrajectoryContainer * trajectoryContainer = event->get_trajectoryContainer();
  G4int n_trajectories = 0;
 
  if(trajectoryContainer) n_trajectories = trajectoryContainer->entries(); 
  
  G4HCofThisEvent * HCE = evtent->get_HCofThisEvent();
  G4int n_hitCollection = 0;


  if(HCE){ 
    n_hitCollection = HCE->get_capacity(); 
  }


  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
    {
      // Declare begininng of visualization
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/scene/notifyHandlers");
      // Draw trajectories
      for(G4int i=0; i< n_trajectories; i++)
	{
  (*(evt->get_trajectoryContainer()))[i]->DrawTrajectory();
	}
      // Construct 3D data for hits
      MyTrackerHitsCollection* THC
	= (MyTrackerHitsCollection*)(HCE->get_HC(trackerCollID));
      if(THC) THC->DrawAllHits();
      MyCalorimeterHitsCollection* CHC
= (MyCalorimeterHitsCollection*)(HCE->get_HC(calorimeterCollID));
      if(CHC) CHC->DrawAllHits();
      // Declare end of visualization
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
} 



*/





}  


