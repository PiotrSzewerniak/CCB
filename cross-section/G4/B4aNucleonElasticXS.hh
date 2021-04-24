//#ifndef G4BGGNucleonElasticXS_h
//#define G4BGGNucleonElasticXS_h 1

#include "globals.hh"
//#include "G4VCrossSectionDataSet.hh"
#include "G4ParticleDefinition.hh"
#include "G4Element.hh"
#include "TGraph.h"
#include "TSpline.h"


class B4aNucleonElasticXS;
class G4Material;
class G4Element;
class G4Isotope;

class B4aNucleonElasticXS //: public B4aCrossSectionDataSet
{
public:

  B4aNucleonElasticXS (const G4ParticleDefinition*);

  virtual ~B4aNucleonElasticXS();
   
  virtual G4bool IsElementApplicable(const G4DynamicParticle*, G4int Z, const G4Material* mat = 0);
  virtual void SetCrossSection(TGraph *f, G4bool useSpline=kFALSE);
  virtual G4double GetWeight(G4double th);
  virtual G4double GetElementCrossSection(const G4DynamicParticle* dp,G4int ZZ, const G4Material*);
  virtual void CrossSectionDescription(std::ostream&) const;
  TGraph *distrib;

private:

  //G4BGGNucleonElasticXS(const G4BGGNucleonElasticXS&);
 
  G4double theThetaL[60][50];
  G4double theCSL[60][50];

  const G4ParticleDefinition*     particle;
  const G4ParticleDefinition*     theProton;
  G4bool                          isProton;
  G4bool                          isInitialized;
  G4bool spline;
  TSpline3 *g_spline;
  TGraph *tcrossg;

};

#endif
