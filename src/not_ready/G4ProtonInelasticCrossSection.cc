#include "G4ProtonInelasticCrossSection.hh"
#include "G4SystemOfUnits.hh"
#include "G4DynamicParticle.hh"
#include "G4Proton.hh"
#include "G4HadTmpUtil.hh"
#include "G4NistManager.hh"

G4ProtonInelasticCrossSection::G4ProtonInelasticCrossSection()
  : G4VCrossSectionDataSet("Axen-Wellisch"),thEnergy(19.8*CLHEP::GeV)
{
  nist = G4NistManager::Instance();
  theProton = G4Proton::Proton();
}

G4ProtonInelasticCrossSection::~G4ProtonInelasticCrossSection()
{}

G4bool 
G4ProtonInelasticCrossSection::IsElementApplicable(
                             const G4DynamicParticle* aPart, 
			     G4int Z, const G4Material*)
{
  return ((1 < Z) && (aPart->GetDefinition() == theProton));
}

G4double G4ProtonInelasticCrossSection::GetElementCrossSection(
			     const G4DynamicParticle* aPart, 
			     G4int Z, const G4Material*)
{
  return GetProtonCrossSection(aPart->GetKineticEnergy(), Z);
}

G4double G4ProtonInelasticCrossSection::GetProtonCrossSection(
			     G4double kineticEnergy, G4int Z)
{
  if(kineticEnergy <= 0.0) { return 0.0; }
 
  // constant cross section above ~20GeV
  if (kineticEnergy > thEnergy) { kineticEnergy = thEnergy; }

  G4double a = nist->GetAtomicMassAmu(Z);
  G4double a13 = std::pow(a,-0.3333333333);
  G4int nOfNeutrons = G4lrint(a) - Z;
  kineticEnergy /=GeV;
  G4double alog10E = std::log10(kineticEnergy);

  static const G4double nuleonRadius=1.36e-15;
  static const G4double fac=CLHEP::pi*nuleonRadius*nuleonRadius;

  G4double b0   = 2.247-0.915*(1 - a13);
  G4double fac1 = b0*(1 - a13);
  G4double fac2 = 1.;
  if(nOfNeutrons > 1) { fac2=std::log((G4double(nOfNeutrons))); }
  G4double crossSection = 1.0E31*fac*fac2*(1. + 1./a13 - fac1);

  // high energy correction
  crossSection *= (1 - 0.15*std::exp(-kineticEnergy))/(1.0 - 0.0007*a);

  // first try on low energies: rise
  G4double ff1= 0.70-0.002*a;  // slope of the drop at medium energies.
  G4double ff2= 1.00+1/a;  // start of the slope.
  G4double ff3= 0.8+18/a-0.002*a; // stephight

  G4double ff4= 1.0 - (1.0/(1+std::exp(-8*ff1*(alog10E + 1.37*ff2))));

  crossSection *= (1 + ff3*ff4);

  // low energy return to zero

  ff1=1. - 1./a - 0.001*a;       // slope of the rise
  ff2=1.17 - 2.7/a - 0.0014*a;   // start of the rise
 
  ff4=-8.*ff1*(alog10E + 2.0*ff2);
 
  crossSection *= millibarn/(1. + std::exp(ff4));
  return crossSection;
}
