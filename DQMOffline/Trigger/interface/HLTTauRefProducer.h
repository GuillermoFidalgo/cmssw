/*HLTTauRefProducer
Producer that creates LorentzVector Collections
from offline reconstructed quantities to be used
in Offline Trigger DQM etc
*/

#ifndef HLTTauRefProducer_h
#define HLTTauRefProducer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "TLorentzVector.h"
// TAU includes
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"
#include "DataFormats/TauReco/interface/CaloTau.h"

// ELECTRON includes
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "AnalysisDataFormats/Egamma/interface/ElectronIDAssociation.h"
#include "AnalysisDataFormats/Egamma/interface/ElectronID.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/TrackReco/interface/Track.h"
// MUON includes
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"

//Photon Includes
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include <vector>
#include <string>

class HLTTauRefProducer : public edm::EDProducer {
  
public:
  explicit HLTTauRefProducer(const edm::ParameterSet&);
  ~HLTTauRefProducer();

  virtual void produce(edm::Event&, const edm::EventSetup&);
  
 private:
  typedef math::XYZTLorentzVectorD LorentzVector;
  typedef std::vector<LorentzVector> LorentzVectorCollection;
  
  edm::InputTag PFTaus_;
  std::vector<edm::InputTag> PFTauDis_;
  bool doPFTaus_;
  double ptMinPFTau_;
  
  
  edm::InputTag Electrons_;
  bool doElectrons_;
  edm::InputTag e_idAssocProd_;
  edm::InputTag e_ctfTrackCollection_;
  double ptMinElectron_;
  bool e_doID_;
  bool e_doTrackIso_;
  double e_trackMinPt_;
  double e_lipCut_;
  double e_minIsoDR_;
  double e_maxIsoDR_;
  double e_isoMaxSumPt_;
  bool doElecFromZ_;
  double e_zMmin_,e_zMmax_;
  double e_FromZet_;

  edm::InputTag Photons_;
  bool doPhotons_;
  double photonEcalIso_;
  double ptMinPhoton_;


  edm::InputTag Muons_;
  bool doMuons_;
  double ptMinMuon_;


  edm::InputTag Jets_;
  bool doJets_;
  double ptMinJet_;

  edm::InputTag Towers_;
  bool doTowers_;
  double ptMinTower_;
  double towerIsol_;

  double etaMax;

  void doPFTaus(edm::Event&,const edm::EventSetup&);
  void doMuons(edm::Event&,const edm::EventSetup&);
  void doElectrons(edm::Event&,const edm::EventSetup&);
  void doElectronsFromZ(edm::Event&,const edm::EventSetup&,std::auto_ptr<LorentzVectorCollection>&);
  double ElectronTrkIsolation(const reco::TrackCollection*, const reco::GsfElectron&);
  void doJets(edm::Event&,const edm::EventSetup&);
  void doPhotons(edm::Event&,const edm::EventSetup&);
  void doTowers(edm::Event&,const edm::EventSetup&);

};

#endif
