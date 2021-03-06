#ifndef B4aNucleonElasticXS_h
#define B4aNucleonElasticXS_h 1

#include "globals.hh"
//#include "G4VCrossSectionDataSet.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"

#include "G4Element.hh"
#include <TGraph.h>
#include <TSpline.h>
#include "g4root.hh"

class TGraph;
class TSpline;
class G4Material;
class G4Element;
class G4Isotope;

class B4aNucleonElasticXS //: public G4VCrossSectionDataSet
{
public:

  //B4aNucleonElasticXS (const G4ParticleDefinition*);
  B4aNucleonElasticXS (const G4ParticleDefinition*);

  virtual ~B4aNucleonElasticXS();
   
  virtual G4bool IsElementApplicable(const G4DynamicParticle*, G4int Z, const G4Material* mat = 0);
  virtual void SetCrossSection(TGraph *f, G4bool useSpline=kFALSE);
  G4double GetWeight(G4double th);
  virtual G4double GetElementCrossSection(const G4DynamicParticle* dp,G4int ZZ, const G4Material*);
  virtual void CrossSectionDescription(std::ostream&) const;
  TGraph *distrib;

private:
  B4aNucleonElasticXS & operator=(const B4aNucleonElasticXS &right);
  B4aNucleonElasticXS(const B4aNucleonElasticXS&);
 
  //G4double theThetaL[50];
  //G4double theCSL[50];

  const G4ParticleDefinition*     particle;
  const G4ParticleDefinition*     theProton;
  G4bool                          isProton;
  G4bool                          isInitialized;
  G4bool spline;
  TSpline3 *g_spline;
  TGraph *tcrossg;
  G4int verboseLevel;
};

#endif
