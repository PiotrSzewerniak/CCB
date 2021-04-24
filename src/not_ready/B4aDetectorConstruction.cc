#include "B4aDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"



G4ThreadLocal 
G4GlobalMagFieldMessenger* B4aDetectorConstruction::fMagFieldMessenger = 0; 



B4aDetectorConstruction::B4aDetectorConstruction()
 : G4VUserDetectorConstruction(),
   //fAbsorberPV(0),
   //fGapPV(0),
   fCheckOverlaps(true)
{
}



B4aDetectorConstruction::~B4aDetectorConstruction()
{ 
}



G4VPhysicalVolume* B4aDetectorConstruction::Construct()
{

  DefineMaterials();
  

  return DefineVolumes();
}



void B4aDetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  //G4NistManager* nistManager = G4NistManager::Instance();
  //nistManager->FindOrBuildMaterial("G4_Pb");
  G4NistManager* man = G4NistManager::Instance();

  G4double z, a, density, ncomponents;
  static const double     pi  = 3.14159265358979323846;
  static const double  twopi  = 2*pi;

  // Vacuum
  G4Material* vaccum =new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);


  // Air
  //G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  //G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  
  //G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  //air->AddElement(N, 70.*perCent);
  //air->AddElement(O, 30.*perCent);  
  G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
  
  //Aluminium 
  G4Material* Alu = man->FindOrBuildMaterial("G4_Al");
  
  //CsI 
  G4Material* CsI = man->FindOrBuildMaterial("G4_CsI");

  //Tal 

  G4Element* Tl =  man->FindOrBuildElement("Tl");
    //new G4Element("Talium", "Tl", z=81, a= 11.72*g/mole);

  //CsI (Tl)
  G4Material *CsI_Tl = new G4Material("CsI_Tl",density= 4.51*g/cm3,ncomponents=2);
  CsI_Tl->AddMaterial(CsI,99.6*perCent);
  CsI_Tl->AddElement(Tl,0.4*perCent);
  
  //Vikuiti ESR foil - polymer, non-metalic --  Polyethylene (??)
  G4Material* Vfoil = man->FindOrBuildMaterial("G4_POLYETHYLENE");

  //Si - photodiodes
  //G4Element* Si = new G4Element("Silicon", "Si", z=14., a=28.09*g/mole);
  G4Material* Si = man->FindOrBuildMaterial("G4_Si");

  //kratta window
  G4Material* Cu = man->FindOrBuildMaterial("G4_Cu");


  // *********************

  //Target windows
  G4Material* mylar = man->FindOrBuildMaterial("G4_MYLAR");
  
  //Target 
  G4Material* glass = man->FindOrBuildMaterial("G4_Pyrex_Glass");

  //Target He3
  //G4Material* he3 = = new G4Material("Hel3", z=2., a=12.0078*g/mole,density=0.1650 *kg/m3);
  G4Material* he3 =new G4Material("Helium3", z=2., a=12.0078*g/mole,density=0.1650 *kg/m3, kStateGas, 293*kelvin, 1.*bar);




  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}



G4VPhysicalVolume* B4aDetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  
  //Full Thicknesses
  G4double ESRfoilThick= 0.065*mm;
  G4double airLayer = 2*mm;
  G4double pdThick = 0.5*mm;
  G4double housThick = 2*mm;
  //G4double krwinThick = 0.2*mm;
  G4double krwinfoilThick = 0.1*mm;
  G4double frameThick = 2.*mm;
  
  G4double air_gap1Thick = 20*mm;
  G4double air_gap2Thick = 10*mm;
  G4double air_gap3Thick = 5*mm;

  G4double glassThick=2.*mm; 
  G4double tarwinThick=0.01*mm; 


  //Half Sizes
 
  G4double fworldSizeXY = 500*mm;
  G4double fworldSizeZ  = 500*mm; 

  //CsI - short
  G4double fCsiShort_xy1 =  14.*mm;
  G4double fCsiShort_xy2 =  14.835*mm;
  G4double fCsiShort_z   = 12.5 *mm;

  //CsI - long
  G4double fCsiLong_xy1 =  16.385*mm;
  G4double fCsiLong_xy2 =  19.25*mm;
  G4double fCsiLong_z   = 62.5 *mm;

  //PD
  G4double fPd_xy =  14.0*mm;//28x28 mm^2
  G4double fPd_z    = 0.25*mm;

  //PD active layer
  G4double fPDdac_z    = 0.23925*mm; 

  //Front dead layer of PD
  G4double fPDdeadF_z    = 0.00075*mm;

  //Rear dead layer of PD
  G4double fPDdeadR_z    = 0.01*mm;

  //Kratta window
  G4double fKRwin_xy = 14.0*mm;
  
  //Kratta housing
  G4double fKRhouse_xy1 =  14.*mm  + frameThick;
  G4double fKRhouse_xy2 =  20*mm + frameThick;// ?
  G4double fKRhouse_z   =  55.75 *mm+ frameThick;
  
  //air gap 1
  G4double fKRairgap1_xy =  14.*mm + frameThick;
  G4double fKRairgap1_z =  7.5*mm;

  //air gap 2
  G4double fKRairgap2_xy =  14.*mm + frameThick;
  G4double fKRairgap2_z =  2*mm;

  //air gap 3
  G4double fKRairgap3_xy =  14.*mm + frameThick;
  G4double fKRairgap3_z =  5.*mm;

  //target cell
  G4double fRmax = 520*mm;
  G4double fRmin = fRmax-glassThick;
  G4double fh_z =  52.*mm;

  //target side windows 
  G4double ftarws_x = 8*mm;
  G4double ftarws_y = 30*mm;

  //target face windows 
  G4double ftarwfR = 8*mm;
   

  //target-detector full distance 
  G4double ftar_det = 400*mm;



  // Get materials
  G4Material* defaultMaterial = G4Material::GetMaterial("Air");
  G4Material* csi_mat = G4Material::GetMaterial("CsI_Tl");
  G4Material* pd_mat = G4Material::GetMaterial("G4_Si");
  G4Material* tgwin_mat = G4Material::GetMaterial("G4_MYLAR");
  G4Material* krwin_mat = G4Material::GetMaterial("G4_Cu");
  G4Material* cell_mat = G4Material::GetMaterial("G4_Pyrex_Glass");
  G4Material* target_mat = G4Material::GetMaterial("Helium3");
  G4Material* housing_mat = G4Material::GetMaterial("Alu");
  G4Material* csiwr_mat = G4Material::GetMaterial("G4_POLYETHYLENE");
  
  //if ( ! defaultMaterial || ! absorberMaterial || ! gapMaterial ) {
  //G4ExceptionDescription msg;
  //msg << "Cannot retrieve materials already defined."; 
  //G4Exception("B4DetectorConstruction::DefineVolumes()", "MyCode0001", FatalException, msg);
  //}  
  

  //     
  // World
  //

  G4VSolid* worldS = new G4Box("World",fworldSizeXY, fworldSizeXY, fworldSizeZ); 
                    
  G4LogicalVolume* worldLV = new G4LogicalVolume( worldS, defaultMaterial, "World");         
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  


  //                               
  // KRATTA housing
  // 
 
  //G4VSolid* kr_housingS1 = new G4Trd("kr_housing1",fKRhouse_xy1,fKRhouse_xy2,fKRhouse_xy1,fKRhouse_xy2,fKRhouse_z);
  //G4VSolid* kr_housingS2 = new G4Trd("kr_housing2",fKRhouse_xy1+housThick,fKRhouse_xy2+housThick,fKRhouse_xy1,fKRhouse_xy2+housThick,fKRhouse_z+housThick);
 
  //front window
  G4VSolid* kr_housingS1 = new G4Box("kr_housing1",fKRwin_xy,fKRwin_xy,frameThick);          
  G4VSolid* kr_housingS2 = new G4Trd("kr_housing2",fKRhouse_xy1+housThick,fKRhouse_xy2+housThick,fKRhouse_xy1,fKRhouse_xy2+housThick,fKRhouse_z+housThick);

  G4VSolid* kr_housingS= new G4SubtractionSolid("kr_housingS", kr_housingS2, kr_housingS1);
  //G4VSolid* kr_housingS = new G4Trd("kr_housingS",fKRhouse_xy1,fKRhouse_xy2,fKRhouse_xy1,fKRhouse_xy2,fKRhouse_z);

                       
  G4LogicalVolume* kr_housingLV
    = new G4LogicalVolume(
		 kr_housingS,  // its solid
                 housing_mat,  // its material
                 "kr_housing");   // its name
    
  /*                           
  G4PVPlacement *kr_housingPV =  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0,0,fKRhouse_z+ftar_det),  
                 kr_housingLV,          // its logical volume                  
                 "kr_housing",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  */
  
  //                               
  // kratta window
  //  
  G4VSolid* kr_hwinS = new G4Box("kr_hwin",fKRwin_xy,fKRwin_xy,0.5*krwinfoilThick);         
  G4LogicalVolume* kr_hwinLV= new G4LogicalVolume(kr_hwinS,krwin_mat,"kr_hwin");          
  /*  
  G4PVPlacement *fkrwinPV = new G4PVPlacement(
                 0,                
                 G4ThreeVector(0., 0., 73.6*mm), 
                 kr_hwinLV,       
                 "kr_hwin",           
                 kr_housingLV,     
                 false,            
                 0,                
                 fCheckOverlaps);  
  */
  //*****************************************
  //                               
  // CSI-short
  //

  G4VSolid* csi_shortS = new G4Trd("csi_short",fCsiShort_xy1,fCsiShort_xy2,fCsiShort_xy1,fCsiShort_xy2,fCsiShort_z);
                         
  G4LogicalVolume* csi_shortLV= new G4LogicalVolume(csi_shortS,csi_mat,"csi_short");          

  //G4Double csi1_z=ftar_det+frameThick+air_gap1Thick+2.*pdThick+air_gap2Thick+fCsiShort_z;
  G4double csi1_z=41.05*mm;
                           
    
  G4PVPlacement *fcsi_shortPV = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., csi1_z), // its position
                 csi_shortLV,       // its logical volume                      
                 "csi_short",           // its name
                 kr_housingLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 


  //                               
  // CsI-short-wrapping Volium
  //
  G4double wr=2.*ESRfoilThick;
  G4VSolid* csi_shortwrS = new G4Trd("csi_shortwr",fCsiShort_xy1+wr,fCsiShort_xy2+wr,fCsiShort_xy1+wr,fCsiShort_xy2+wr,fCsiShort_z+wr);
                         
  G4LogicalVolume* csi_shortwrLV= new G4LogicalVolume(csi_shortwrS,csiwr_mat,"csiwr_short");          
 
  //  G4Double csi1wr_z=40.4*mm;
  G4double csi1wr_z=41.05*mm;
  /*
  G4PVPlacement *fcsi_shortwrPV = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., csi1wr_z), // its position
                 csi_shortwrLV,       // its logical volume                     
                 "csi_shortwr",           // its name
                 kr_housingLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  */
  //                               
  // CSI-long
  //
  
  G4VSolid* csi_longS = new G4Trd("csi_long",fCsiLong_xy1,fCsiLong_xy2,fCsiLong_xy1,fCsiLong_xy2,fCsiShort_z);
  G4LogicalVolume* csi_longLV= new G4LogicalVolume(csi_longS,csi_mat,"csi_long");          
  G4double csi2_z=-35.25*mm;
  /*                       
    
  G4PVPlacement *fcsi_longPV = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., csi2_z), // its position
                 csi_shortLV,       // its logical volume                      
                 "csi_long",           // its name
                 kr_housingLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  */

  //                               
  // CsI-long-wrapping Volium
  //
  wr=2.*ESRfoilThick;
  G4VSolid* csi_longwrS = new G4Trd("csi_longwr",fCsiLong_xy1+wr,fCsiLong_xy2+wr,fCsiLong_xy1+wr,fCsiLong_xy2+wr,fCsiLong_z+wr);
                         
  G4LogicalVolume* csi_longwrLV= new G4LogicalVolume(csi_longwrS,csiwr_mat,"csiwr_long");          
 
  G4double csi2wr_z=-35.25*mm;
                           
  /*
  G4PVPlacement *fcsi_longwrPV = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., csi2wr_z), // its position
                 csi_longwrLV,       // its logical volume                      
                 "csi_longwr",           // its name
                 kr_housingLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  */
  //******************************************                                 
  // PD
  //
  G4VSolid* pdS = new G4Box("Pd",fPd_xy,fPd_xy,fPd_z);                 
  G4LogicalVolume* pdLV = new G4LogicalVolume(pdS, pd_mat,"Pd");
  //                                 
  // PD-Active Layer
  //
  G4VSolid* pdacS = new G4Box("Pdac",fPd_xy,fPd_xy,fPDdac_z);    
  G4LogicalVolume* pdacLV = new G4LogicalVolume(pdacS, pd_mat,"Pdac");
  //                                 
  // PD-Front Dead Layer
  //
  G4VSolid* pddfS = new G4Box("Pddf",fPd_xy,fPd_xy,fPDdeadF_z);    
  G4LogicalVolume* pddfLV = new G4LogicalVolume(pddfS, pd_mat,"Pddf");   
  //                                 
  // PD-Rear Dead Layer
  //
  G4VSolid* pddrS = new G4Box("Pddr",fPd_xy,fPd_xy,fPDdeadR_z);    
  G4LogicalVolume* pddrLV = new G4LogicalVolume(pddrS, pd_mat,"Pddr");   
 



  /*
 fpd0PV = new G4PVPlacement(0,           
			    G4ThreeVector(0., 0., 58.30925*mm), 
			    pd0LV,    
			    "Pd0",  
			    kr_housingLV,  
			    false,         
			    0,             
			    fCheckOverlaps);
  */


//******************************************                                 
// Air Layer1
//
  G4VSolid* airlayer1S = new G4Box("AirL1",fKRairgap1_xy,fKRairgap1_xy,fKRairgap1_z);                 
  G4LogicalVolume* airlayer1LV = new G4LogicalVolume(airlayer1S, defaultMaterial,"AirL1");
  /*                        
  G4PVPlacement *fairlayer1PV = new G4PVPlacement( 0,           
				    G4ThreeVector(0., 0., 66.05*mm), 
				    airlayer1LV,    
				    "AirL1",  
				    kr_housingLV,  
				    false,         
				    0,             
				    fCheckOverlaps);
  */
//******************************************                                 
// Air Layer2
//
  G4VSolid* airlayer2S = new G4Box("AirL2",fKRairgap2_xy,fKRairgap2_xy,fKRairgap2_z);                 
  G4LogicalVolume* airlayer2LV = new G4LogicalVolume(airlayer2S, defaultMaterial,"AirL2");
    
  /*                        
  G4PVPlacement *fairlayer2PV = new G4PVPlacement( 0,           
				    G4ThreeVector(0., 0., 56.05*mm), 
				    airlayer2LV,    
				    "AirL2",  
				    kr_housingLV,  
				    false,         
				    0,             
				    fCheckOverlaps);
  */
//******************************************                                 
// Air Layer3
//
  G4VSolid* airlayer3S = new G4Box("AirL3",fKRairgap3_xy,fKRairgap3_xy,fKRairgap3_z);                 
  G4LogicalVolume* airlayer3LV = new G4LogicalVolume(airlayer3S, defaultMaterial,"AirL3");

  /*                            
  G4PVPlacement *fairlayer3PV = new G4PVPlacement( 0,           
				    G4ThreeVector(0., 0., -103.9*mm), 
				    airlayer3LV,    
				    "AirL3",  
				    kr_housingLV,  
				    false,         
				    0,             
				    fCheckOverlaps);
  */
//******************************************                                 
// Target
//
 
//target volume
  G4VSolid* targ_volS = new G4Tubs("targ_vol",0.,fRmax,fh_z,0.,twopi); 
  G4LogicalVolume* targ_volLV = new G4LogicalVolume(targ_volS,target_mat,"targ_volLV");
  /*
  G4PVPlacement *ftarg_volPV = new G4PVPlacement( 0,           
				   G4ThreeVector(), 
				   targ_volLV,    
				   "targ_volPV",  
				   worldLV,
				   false,         
				   0,             
				   fCheckOverlaps);

  */
  //target cell
  G4VSolid* targS1 = new G4Tubs("targ1",fRmin,fRmax,fh_z,0.,twopi);          
  G4VSolid* targS2 = new G4Box("targ2",ftarws_x,ftarws_y,25*mm);
  G4VSolid* targS3 = new G4Tubs("targ3",0.,ftarwfR,fh_z,0.,twopi);
  G4VSolid* targS12= new G4SubtractionSolid("targS12",targS1,targS2);

  G4VSolid* targS= new G4SubtractionSolid("targS",targS12,targS3);
  G4LogicalVolume* targLV = new G4LogicalVolume(targS,cell_mat,"targL");
  /*                            
  G4PVPlacement *ftargcellPV = new G4PVPlacement( 0,           
				   G4ThreeVector(), 
				   targLV,    
				   "targPV",  
				   targ_volLV,
				   false,         
				   0,             
				   fCheckOverlaps);


  */
  //target side windows
 
  //fRmax=Rmin --- oznacza Rmax dla komorki, a nie okienka !!!

  G4double ph=0.1538;//ph=8mm/52.005mm[rad]
  G4VSolid* targ_winS1S = new G4Tubs("targ_winS1S",fRmax,fRmax+tarwinThick,ftarws_y,(-1.)*ph,ph);
  G4LogicalVolume* targ_winS1LV = new G4LogicalVolume(targ_winS1S,tgwin_mat,"targ_winS1L");
  /*                        
  G4PVPlacement *ftarg_winS1PV = new G4PVPlacement( 0,           
				     G4ThreeVector(fRmax,0.,0.), 
				     targ_winS1LV,    
				     "targ_winS1PV",  
				     targLV,
				     false,         
				     0,             
				     fCheckOverlaps);

  */
  G4VSolid* targ_winS2S = new G4Tubs("targ_winS2S",fRmax,fRmax+tarwinThick,ftarws_y,(-1.)*ph,ph);
  G4LogicalVolume* targ_winS2LV = new G4LogicalVolume(targ_winS2S,tgwin_mat,"targ_winS2L");
  /*                        
  G4PVPlacement *ftarg_winS2PV = new G4PVPlacement( 0,           
				     G4ThreeVector((-1.)*fRmax,0.,0.), 
				     targ_winS2LV,    
				     "targ_winS2PV",  
				     targLV,
				     false,         
				     0,             
				     fCheckOverlaps);
  */


  //target face windows

  
  G4VSolid* targ_winF1S = new G4Tubs("targ_winF1S",0.,ftarwfR,0.5*tarwinThick,0.,twopi);
  G4LogicalVolume* targ_winF1LV = new G4LogicalVolume(targ_winF1S,tgwin_mat,"targ_winF1L");
  /*                            
  G4PVPlacement *ftarg_winF1PV = new G4PVPlacement( 0,           
				     G4ThreeVector(0.,0.,fh_z+0.5*tarwinThick), 
				     targ_winF1LV,    
				     "targ_winF1PV",  
				     targLV,
				     false,         
				     0,             
				     fCheckOverlaps);

  */
  G4VSolid* targ_winF2S = new G4Tubs("targ_winF2S",0.,ftarwfR,0.5*tarwinThick,0.,twopi);
  G4LogicalVolume* targ_winF2LV = new G4LogicalVolume(targ_winF2S,tgwin_mat,"targ_winF2L");
  /*                        
  G4PVPlacement *ftarg_winF2PV = new G4PVPlacement( 0,           
				     G4ThreeVector(0.,0.,(-1.)*(fh_z+0.5*tarwinThick)), 
				     targ_winF2LV,    
				     "targ_winF2PV",  
				     targLV,
				     false,         
				     0,             
				     fCheckOverlaps);
  */

  /*
  //                                 
  // Layer
  //
  G4VSolid* layerS 
    = new G4Box("Layer",           // its name
                 calorSizeXY/2, calorSizeXY/2, layerThickness/2); // its size
                         
  G4LogicalVolume* layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                 defaultMaterial,  // its material
                 "Layer");         // its name

  new G4PVReplica(
                 "Layer",          // its name
                 layerLV,          // its logical volume
                 calorLV,          // its mother
                 kZAxis,           // axis of replication
                 nofLayers,        // number of replica
                 layerThickness);  // witdth of replica
  
  */


  
  //
  // print parameters
  //
  
  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    //  << "---> The calorimeter is " << nofLayers << " layers of: [ "
    //<< absoThickness/mm << "mm of " << absorberMaterial->GetName() 
    //<< " + "
    //<< gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
    << "------------------------------------------------------------" << G4endl;
  

  //                                        
  // Visualization attributes
  //
  // worldLV->SetVisAttributes (G4VisAttributes::Invisible);

  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
 simpleBoxVisAtt->SetVisibility(true);
  //calorLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}



void B4aDetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.

  G4ThreeVector fieldValue = G4ThreeVector();
  // fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  //fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  //G4AutoDelete::Register(fMagFieldMessenger);
}


