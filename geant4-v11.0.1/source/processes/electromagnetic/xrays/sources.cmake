# - G4xrays module build definition

# Define the Geant4 Module.
geant4_add_module(G4xrays
  PUBLIC_HEADERS
    G4Cerenkov.hh
    G4ForwardXrayTR.hh
    G4GammaXTRadiator.hh
    G4GaussXTRadiator.hh
    G4RegularXTRadiator.hh
    LightTarget.hh
    G4Scintillation.hh
    G4ScintillationTrackInformation.hh
    G4StrawTubeXTRadiator.hh
    G4SynchrotronRadiation.hh
    G4SynchrotronRadiationInMat.hh
    G4TransitionRadiation.hh
    G4TransparentRegXTRadiator.hh
    G4VTRModel.hh
    G4VTransitionRadiation.hh
    G4VXTRenergyLoss.hh
    G4InverseCompton.hh
    G4XTRGammaRadModel.hh
    G4XTRRegularRadModel.hh
    G4XTRTransparentRegRadModel.hh
  SOURCES
    G4Cerenkov.cc
    G4ForwardXrayTR.cc
    G4GammaXTRadiator.cc
    G4GaussXTRadiator.cc
    G4RegularXTRadiator.cc
    LightTarget.cc
    G4Scintillation.cc
    G4ScintillationTrackInformation.cc
    G4StrawTubeXTRadiator.cc
    G4SynchrotronRadiation.cc
    G4SynchrotronRadiationInMat.cc
    G4TransitionRadiation.cc
    G4TransparentRegXTRadiator.cc
    G4VTransitionRadiation.cc
    G4VXTRenergyLoss.cc
    G4InverseCompton.cc
    G4XTRGammaRadModel.cc
    G4XTRRegularRadModel.cc
    G4XTRTransparentRegRadModel.cc)

geant4_module_link_libraries(G4xrays
  PUBLIC
    G4bosons
    G4emutils
    G4geometrymng
    G4globman
    G4leptons
    G4materials
    G4navigation
    G4partman
    G4procman
    G4track
  PRIVATE
    G4cuts
    G4emstandard
    G4hepnumerics
    G4heprandom
    G4magneticfield)
