#ifndef RecoEgamma_EgammaTools_AnyMVAEstimatorRun2Base_H
#define RecoEgamma_EgammaTools_AnyMVAEstimatorRun2Base_H

#include "DataFormats/Candidate/interface/Candidate.h"

class AnyMVAEstimatorRun2Base {

 public:
  // Constructor, destructor
  AnyMVAEstimatorRun2Base(){};
  ~AnyMVAEstimatorRun2Base(){};

  // Functions that must be provided in derived classes
  // These function should work on electrons or photons
  // of the reco or pat type

  virtual float mvaValue( const edm::Ptr<reco::Candidate>& particle) = 0;
 
  virtual int findCategory( const edm::Ptr<reco::Candidate>& particle) = 0;
 
};


#endif
