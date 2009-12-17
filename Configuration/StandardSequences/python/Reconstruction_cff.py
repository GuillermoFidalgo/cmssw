import FWCore.ParameterSet.Config as cms

from RecoLuminosity.LumiProducer.lumiProducer_cff import *
from RecoLocalMuon.Configuration.RecoLocalMuon_cff import *
from RecoLocalCalo.Configuration.RecoLocalCalo_cff import *
from RecoTracker.Configuration.RecoTracker_cff import *
from RecoParticleFlow.PFClusterProducer.particleFlowCluster_cff import *
from TrackingTools.Configuration.TrackingTools_cff import *
# Global  reco
from RecoEcal.Configuration.RecoEcal_cff import *
from RecoJets.Configuration.RecoJets_cff import *
from RecoJets.Configuration.JetIDProducers_cff import *
from RecoJets.Configuration.CaloTowersRec_cff import *
from RecoMET.Configuration.RecoMET_cff import *
from RecoMuon.Configuration.RecoMuon_cff import *
# Higher level objects
from RecoVertex.Configuration.RecoVertex_cff import *
from RecoEgamma.Configuration.RecoEgamma_cff import *
from RecoPixelVertexing.Configuration.RecoPixelVertexing_cff import *
#not needed anymore - the jet to track associations are in the next one
#include "RecoBTau/Configuration/data/RecoBTau.cff"
from RecoJets.Configuration.RecoJetAssociations_cff import *
from RecoJets.Configuration.RecoPFJets_cff import *
from RecoMET.Configuration.RecoPFMET_cff import *
from RecoBTag.Configuration.RecoBTag_cff import *
#
# please understand that division global,highlevel is completely fake !
#
#local reconstruction
from RecoLocalTracker.Configuration.RecoLocalTracker_cff import *
from RecoParticleFlow.Configuration.RecoParticleFlow_cff import *
#
# new tau configuration
#
from RecoTauTag.Configuration.RecoPFTauTag_cff import *
from RecoTauTag.Configuration.RecoTauTag_cff import *
# Also BeamSpot
from RecoVertex.BeamSpotProducer.BeamSpot_cff import *
localreco = cms.Sequence(trackerlocalreco+muonlocalreco+calolocalreco+particleFlowCluster+lumiProducer)
localreco_HcalNZS = cms.Sequence(trackerlocalreco+muonlocalreco+calolocalrecoNZS+particleFlowCluster+lumiProducer)

#
# temporarily switching off recoGenJets; since this are MC and wil be moved to a proper sequence
#
globalreco = cms.Sequence(offlineBeamSpot+recopixelvertexing*ckftracks+ecalClusters+caloTowersRec*vertexreco*recoJets*recoJetIds+muonrecoComplete+electronGsfTracking)
globalreco_plusRS = cms.Sequence(globalreco*rstracks)
globalreco_plusPL= cms.Sequence(globalreco*ctfTracksPixelLess)
highlevelreco = cms.Sequence(recoJetAssociations*tautagging*particleFlowReco*egammarecoFull*metrecoPlusHCALNoise*reducedRecHitsSequence*btagging*recoPFJets*recoPFMET*PFTau)
#emergency sequence wo conversions
highlevelreco_woConv = cms.Sequence(recoJetAssociations*tautagging*particleFlowReco*egammareco_woConvPhotons*metrecoPlusHCALNoise*reducedRecHitsSequence*btagging*recoPFJets*recoPFMET*PFTau)


from FWCore.Modules.logErrorHarvester_cfi import *

# "Export" Section
reconstruction         = cms.Sequence(localreco        *globalreco       *highlevelreco*muoncosmicreco*logErrorHarvester)

#sequences with additional stuff
reconstruction_withPixellessTk  = cms.Sequence(localreco        *globalreco_plusPL*highlevelreco*muoncosmicreco*logErrorHarvester)
reconstruction_withRS  = cms.Sequence(localreco        *globalreco_plusRS*highlevelreco*muoncosmicreco*logErrorHarvester)
reconstruction_HcalNZS = cms.Sequence(localreco_HcalNZS*globalreco       *highlevelreco*muoncosmicreco*logErrorHarvester)

#sequences without some stuffs
#
reconstruction_woConv        = cms.Sequence(localreco*globalreco*highlevelreco_woConv*muoncosmicreco*logErrorHarvester)
reconstruction_woCosmicMuons = cms.Sequence(localreco*globalreco*highlevelreco       *logErrorHarvester)


# define a standard candle. please note I am picking up individual
# modules instead of sequences
#
reconstruction_standard_candle = cms.Sequence(localreco*globalreco*vertexreco*recoJetAssociations*btagging*electronSequence*photonSequence)


