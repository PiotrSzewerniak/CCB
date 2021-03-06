//#include "G4BGGNucleonElasticXS.hh"
#include "G4SystemOfUnits.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4NistManager.hh"
#include "G4Log.hh"
#include "G4Exp.hh"
#include "B4aNucleonElasticXS.hh"
#include <TGraph.h>
#include <TSpline.h>
#include "G4LorentzVector.hh"
#include "G4CrossSectionDataSetRegistry.hh"
using namespace std;

const G4double llog10 = G4Log(10.);

B4aNucleonElasticXS::B4aNucleonElasticXS(const G4ParticleDefinition* p)
 //: G4VCrossSectionDataSet() 
{
  verboseLevel = 0;
   
  /*
  for (G4int j = 0; j < 60; ++j) {
    for (G4int i = 0; i < 50; ++i) {
      //theCSL[j][i] = 0.0;
      //theThetaL[j][i] = 0.0;
    
      }
  }
  */
  //cout<<"CROSS SECTION FOR ES READY"<<endl;
  //G4float theThetaL[]={11.0,13.7,17.1,20.4,23.8,27.1,33.8,40.4,46.9,53.3,59.6,65.8,71.9,77.9,83.7,89.4,94.9,100.0,109.5,119.5,129.6,139.6,144.6,149.6,154.7,159.7,163.7,168.7};
  //G4float theCSL[]={44.1,47.5,49.6,43.6,37.6,31.2,19.2,11.1,6.44,3.80,2.69,1.75,1.20,0.903,0.714,0.518,0.446,0.347,0.21,0.154,0.115,0.104,0.115,0.156,0.225,0.341,0.453,0.543};

  //CS for elastic p-He3 scattering in mb/sr for 100 MeV od p beam
  //G4float theThetaL[]={20.5,24.,30.,35.,40.,44.,49.2,54.2,60.7,64.2,69.,75.,80.,85.,90.7,103.7,114.5, 118.,122.,127.,135.,140.};
  //G4float theCSL[]={42.,28.4,14.,7.5,4.6,2.91,2.03,1.53,0.88,0.75,0.51,0.4,0.251,0.202,0.141,0.076,0.04,0.037,0.029,0.033,0.04,0.053};


  //CS for elastic p-Ti46 scattering in mb/sr for 100 MeV  p beam
  //original CS is divided by CSrutherford
  
  G4float theThetaL[]={7.824,9.3,10.3,11.74,13.21,15.2,15.7,17.12,17.6,18.6,20.1,23.,24.,24.5,25.45,27.4,29.4,30.35,31.8,33.3,36.2,38.2,41.2,42.63,44.6,46.6,49.5,51.,52.6,55.5,57.2,59.,63.35,65.5,67.8,68.3,69.8,71.4,74.3,77.3,80.73,83.2,85.4,87.2,89.2, 90.,91.2,93.2,96.2,100.7,105.8,108.8,111.8,114.8,118.,120.,125.,129.,135.1,140.2,145.3,150.4,154.4,159.6,165.7,167.7};

  G4float theCS_CM[]={2.35E+00,3.19E+00,3.68E+00,3.68E+00,2.97E+00,1.93E+00,1.70E+00,1.03E+00,7.51E-01, 5.07E-01,3.74E-01,1.13E+00,1.37E+00,1.70E+00,2.04E+00,2.15E+00,2.07E+00,1.73E+00,1.33E+00,1.00E+00,6.75E-01, 6.17E-01,7.25E-01,7.92E-01,7.65E-01,5.85E-01,4.32E-01,3.55E-01,2.97E-01,2.91E-01,3.07E-01,3.02E-01,2.19E-01,1.30E-01,9.47E-02,8.07E-02,4.81E-02,4.02E-02,4.09E-02,5.25E-02,5.16E-02,5.16E-02,3.02E-02,2.48E-02,1.64E-02,1.21E-02,7.25E-03,4.72E-03,3.24E-03,4.81E-03,5.07E-03,3.13E-03,2.91E-03,9.82E-04,5.25E-04,4.98E-04,6.28E-04,8.66E-04,1.03E-03,5.07E-04,3.19E-04,3.07E-04,1.37E-04,2.48E-04,1.93E-04,1.59E-04};

  G4float theJAC_L_CM[]={9.5683e-01,9.5699e-01,9.5711e-01,9.5732e-01,9.5756e-01,9.5792e-01,9.5801e-01, 9.5832e-01,9.5843e-01,9.5866e-01,9.5903e-01,9.5983e-01,9.6013e-01,9.6028e-01,9.6059e-01,9.6124e-01,9.6194e-01,9.6231e-01,9.6288e-01,9.6348e-01,9.6474e-01,9.6564e-01,9.6706e-01,9.6780e-01,9.6883e-01,9.6990e-01,9.7157e-01,9.7243e-01,9.7331e-01,9.7514e-01,9.7545e-01,9.7672e-01,9.8035e-01,9.8172e-01,9.8347e-01,9.8382e-01,9.8489e-01,9.8598e-01,9.8818e-01,9.9042e-01,9.9308e-01,9.9500e-01,9.9655e-01,9.9811e-01,9.9968e-01,1.0005e+00,1.0012e+00,1.0028e+00,1.0052e+00,1.0087e+00,1.0126e+00,1.0149e+00,1.0172e+00,1.0194e+00,1.0216e+00,1.0230e+00,1.0264e+00,1.0291e+00,1.0327e+00,1.0355e+00,1.0380e+00,1.0403e+00,1.0418e+00,1.0435e+00,1.0450e+00,1.0453e+00};
  
  //#####################################
//CS for elastic p-12C scattering in mb/sr for 96 MeV  p beam
  //original CS is in CM

  //G4float theThetaL[]={3.6,4.,4.74,5.2,5.9,6.,6.7,7.,7.33,7.9,8.4,9.2,9.92,10.35,11.1,11.68,12.7,13.5,13.9,14.68,14.8, 16.1, 16.84, 17.7, 18.6, 19.6, 20.75, 21.4,22.2, 23.4, 24., 26.4, 28.8, 31., 33.5, 35.7, 38., 42.8, 47.4, 52., 57.2, 62.12, 66.8,71.3,76.44,86.5  };

  //G4float theCS_CM[]={7000,2600,1310,721,552,461,463,452,448,493,495,472,473,502,478,438, 426, 394, 339, 356, 341, 287, 219, 196.4, 163, 156, 115.2, 100.1, 70., 58.8, 49.3, 25.6, 13.04, 8., 4.8, 3.41, 2.96, 1.623, .773, .368, .221, .2084,.179,.125,.096,.027};

  //G4float theJAC_L_CM[]={7.4307e-01,7.4321e-01, 7.4335e-01, 7.4351e-01,7.4388e-01,7.4388e-01,7.4430e-01,7.4453e-01,7.4453e-01,7.4503e-01,7.4530e-01,7.4589e-01, 7.4620e-01,7.4653e-01,7.4723e-01,7.4760e-01,7.4880e-01,7.4839e-01,7.4967e-01,7.5059e-01,7.5108e-01,7.5261e-01, 7.5315e-01,7.5428e-01,7.5546e-01,7.5669e-01,7.5866e-01,7.5934e-01,7.6074e-01,7.6296e-01,7.6451e-01,7.6864e-01,7.7313e-01, 7.7798e-01,7.8427e-01,7.8992e-01,7.9594e-01,8.1046e-01,8.2521e-01,8.4144e-01,8.6100e-01,8.8231e-01,9.0320e-01, 9.2547e-01, 9.4907e-01, 9.9991e-01 };


G4int sz=sizeof(theThetaL)/sizeof(G4float); 
 G4float theCS_L[100];//={0.};


for ( int i =0;i< sz;i++){

  //for Ti
  theCS_L[i]=(1./theJAC_L_CM[i])*theCS_CM[i]*(1.296*(46.*1/100.)*(46.*1/100.)*1./pow(sin((CLHEP::pi/180.)*theThetaL[i]/2.),4));

  //for the rest
//theCS_L[i]=(1./theJAC_L_CM[i])*theCS_CM[i];

    }


 distrib = new TGraph(sz,theThetaL,theCS_L);
 SetCrossSection(distrib, kTRUE);
  
  particle = p;
  theProton= G4Proton::Proton();
  isProton = false;
  isInitialized = false;

  

}



B4aNucleonElasticXS::~B4aNucleonElasticXS()
{


}



G4bool B4aNucleonElasticXS::IsElementApplicable(const G4DynamicParticle*, G4int,  const G4Material*)
{
  return true;
}


 void B4aNucleonElasticXS::SetCrossSection(TGraph *f, G4bool useSpline) {
          
      tcrossg=f;
      spline=useSpline;

      if (spline) {
	g_spline=new TSpline3("",f);
	
      }
    }

 G4double B4aNucleonElasticXS::GetWeight(G4double th) {
    G4double ret=0;
   
    if (tcrossg) {
      ret=tcrossg->Eval(th,g_spline,"");
      //ret=h_spline->Eval(mass[0]);
        
      
	//We have to check that we are not below the first and the last point
	if (th<tcrossg->GetX()[0]) {
	  ret=tcrossg->GetY()[0];
     	}
     	if (th>((tcrossg->GetX())[tcrossg->GetN()-1])) {
     	  ret=(tcrossg->GetY())[tcrossg->GetN()-1];
     	}
	//cout<<r<<" "<<mass[0]<<" "<<ret<<endl;	

    } //else if (tcross)
      //ret=tcross->Eval(th);
    //else 
    //	ret=tcrossc;
    //cout << "ret:" << ret << endl;
    if (ret>0) return ret ;
    return 0.;

}



G4double
B4aNucleonElasticXS::GetElementCrossSection(const G4DynamicParticle* dp,G4int ZZ, const G4Material*)
{
  // proton on Nucleus

  G4double cross = 0.0;
  G4double ekin = dp->GetKineticEnergy();
  G4LorentzVector prot4Mom=dp->Get4Momentum();
  G4double protTh = prot4Mom.theta();


  G4int Z = ZZ;
  if(Z) {
    cross = GetWeight(protTh);
  } 
  

  if(verboseLevel > 1) {
    G4cout << "G4BGGNucleonElasticXS::GetElementCrossSection  for "
	   << dp->GetDefinition()->GetParticleName()
	   << "  Ekin(GeV)= " << dp->GetKineticEnergy()/CLHEP::GeV
	   << " in nucleus Z= " << Z 
	   << " XS(b)= " << cross/barn 
	   << G4endl;
    }
  
  return cross;
}


void B4aNucleonElasticXS::CrossSectionDescription(std::ostream& outFile) const
{
  /*
  outFile << "The Barashenkov-Glauber-Gribov cross section handles elastic\n"
          << "scattering of protons and neutrons from nuclei using the\n"
          << "Barashenkov parameterization below 91 GeV and the Glauber-Gribov\n"
          << "parameterization above 91 GeV. n";
  */

}


