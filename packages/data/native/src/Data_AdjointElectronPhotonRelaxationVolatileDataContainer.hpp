//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native adjoint electron-photon-relaxation volatile data container class
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_VOLATILE_DATA_CONTAINER_HPP
#define DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_VOLATILE_DATA_CONTAINER_HPP

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace Data{

//! The electron-photon-relaxation volatile data container
class AdjointElectronPhotonRelaxationVolatileDataContainer : public AdjointElectronPhotonRelaxationDataContainer
{

public:

  //! Default constructor
  AdjointElectronPhotonRelaxationVolatileDataContainer();

  //! Constructor (from saved archive)
  AdjointElectronPhotonRelaxationVolatileDataContainer(
           const std::string& archive_name,
           const Utility::ArchivableObject::ArchiveType archive_type );

  // Add the setter member functions to the public interface
  using AdjointElectronPhotonRelaxationDataContainer::setNotes;

  // Basic table functions
  using AdjointElectronPhotonRelaxationDataContainer::setAtomicNumber;
  using AdjointElectronPhotonRelaxationDataContainer::setMinPhotonEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setMaxPhotonEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setMinElectronEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setMaxElectronEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setGridConvergenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setGridAbsoluteDifferenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setGridDistanceTolerance;

  // Photon table functions
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistNormConstantNudgeValue;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistNormConstantNudgeValue;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentMaxEnergyNudgeValue;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentEnergyToMaxEnergyNudgeValue;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentEvaluationTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentGridConvergenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentGridAbsoluteDifferenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentGridDistanceTolerance;

  // Electron table functions
  using AdjointElectronPhotonRelaxationDataContainer::setCutoffAngleCosine;
  using AdjointElectronPhotonRelaxationDataContainer::setNumberOfAdjointMomentPreservingAngles;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronGridConvergenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronAbsoluteDifferenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronDistanceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungMaxEnergyNudgeValue;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungEvaluationTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungGridConvergenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungAbsoluteDifferenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungDistanceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationEvaluationTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationGridConvergenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationAbsoluteDifferenceTolerance;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationDistanceTolerance;

  // Relaxation functions
  using AdjointElectronPhotonRelaxationDataContainer::setSubshells;
  using AdjointElectronPhotonRelaxationDataContainer::setSubshellOccupancy;
  using AdjointElectronPhotonRelaxationDataContainer::setSubshellBindingEnergy;

  // Photon functions
  using AdjointElectronPhotonRelaxationDataContainer::setComptonProfileMomentumGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setComptonProfile;
  using AdjointElectronPhotonRelaxationDataContainer::setOccupationNumberMomentumGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setOccupationNumber;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunctionMomentumGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunction;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactorMomentumGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactor;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeSquaredAtomicFormFactor;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeIncoherentMaxEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeIncoherentCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxIncoherentMaxEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxIncoherentCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxSubshellIncoherentCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeCoherentCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeTotalMaxEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeTotalCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxTotalMaxEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxTotalCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeTotalCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setImpulseApproxTotalCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistributionGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistribution;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistributionNormConstantGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistributionNormConstant;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistributionGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistribution;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistributionNormConstantGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistributionNormConstant;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonBremsstrahlungEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonBremsstrahlungEnergyAtIncomingEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonBremsstrahlungPDFAtIncomingEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonBremsstrahlungEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonBremsstrahlungPDF;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungPhotonCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungPhotonCrossSectionThresholdEnergyIndex;

  // Electron functions
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElasticAngularEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticAnglesAtEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticPDFAtEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticAngles;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticPDF;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticDiscreteAnglesAtEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticWeightsAtEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticDiscreteAngles;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticWeights;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilEnergyAtIncomingEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilPDFAtIncomingEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilPDF;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronBremsstrahlungEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronBremsstrahlungEnergyAtIncomingEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronBremsstrahlungPDFAtIncomingEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronBremsstrahlungEnergy;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronBremsstrahlungPDF;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationEnergyGain;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronEnergyGrid;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticCrossSectionThresholdEnergyIndex;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointScreenedRutherfordElasticCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTotalElasticCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointTotalElasticCrossSectionThresholdEnergyIndex;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingCrossSectionThresholdEnergyIndex;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationCrossSectionThresholdEnergyIndex;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungElectronCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationCrossSection;
  using AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex;

  // Add the export member function to the public interface
  using AdjointElectronPhotonRelaxationDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using AdjointElectronPhotonRelaxationDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

