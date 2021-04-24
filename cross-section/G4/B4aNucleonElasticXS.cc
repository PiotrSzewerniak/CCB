#include "G4BGGNucleonElasticXS.hh"
#include "G4SystemOfUnits.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4NistManager.hh"
#include "G4Log.hh"
#include "G4Exp.hh"
#include "TGraph.h"
#include "TSpline.h"

#include "G4CrossSectionDataSetRegistry.hh"

const G4double llog10 = G4Log(10.);

B4aNucleonElasticXS::B4aNucleonElasticXS(const G4ParticleDefinition* p)
// : G4VCrossSectionDataSet("Barashenkov-Glauber") 
{
  verboseLevel = 0;
   
  
  for (G4int j = 0; j < 60; ++j) {
    for (G4int i = 0; i < 50; ++i) {
      theCSL[j][i] = 0.0;
      theThetaL[j][i] = 0.0;
    
      }
  }

 theThetaL[3][]={11.0,13.7,17.1,20.4,23.8,27.1,33.8,40.4,46.9,53.3,59.6,65.8,71.9,77.9,83.7,89.4,94.9,100.0,109.5,119.5,129.6,139.6,144.6,149.6,154.7,159.7,163.7,168.7};

theCSL[3][]={44.1,47.5,49.6,43.6,37.6,31.2,19.2,11.1,6.44,3.80,2.69,1.75,1.20,0.903,0.714,0.518,0.446,0.347,0.21,0.154,0.115,0.104,0.115,0.156,0.225,0.341,0.453,0.543};

 distrib = new TGraph(28,theThetaL,theCSL);
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


 void B4aNucleonElasticXS::SetCrossSection(TGraph *f, G4bool useSpline=kFALSE) {
          
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

    } else if (tcross)
      ret=tcross->Eval(th);
    else 
	ret=tcrossc;
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
	   << " in nucleus Z= " << Z << "  A= " << theA[Z]
	   << " XS(b)= " << cross/barn 
	   << G4endl;
  }
  
  return cross;
}


void G4BGGNucleonElasticXS::CrossSectionDescription(std::ostream& outFile) const
{
  outFile << "The Barashenkov-Glauber-Gribov cross section handles elastic\n"
          << "scattering of protons and neutrons from nuclei using the\n"
          << "Barashenkov parameterization below 91 GeV and the Glauber-Gribov\n"
          << "parameterization above 91 GeV. n";
}


