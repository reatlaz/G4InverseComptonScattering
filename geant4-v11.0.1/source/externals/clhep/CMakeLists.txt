#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : G4clhep
# Package: Geant4.src.G4externals.G4clhep
#
# CMakeLists.txt for G4clhep. We do not use the usual Geant4 sources.cmake
# approach because G4clhep requires a custom install solution for its
# headers. These are in a nested structure so this needs to be replicated
# when we install, i.e:
# <INCLUDE>
# +- geant4
#    +- CLHEP
#       +- Vector
#       |  +- ThreeVector.h
#       ...
#
# Nevertheless, we're able to build the library via the standard
# GEANT4_LIBRARY_TARGET macro.
#
# Created on: 02/06/2011
#
# $Date$
# $Revision$
# $Author$
#
#------------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Includes for this modules
#
include_directories(include)


#----------------------------------------------------------------------------
# Compile definitions needed
#
add_definitions(-DCLHEP_EXPORT)

#----------------------------------------------------------------------------
# List the headers and sources
#
# - Headers
set(G4clhep_HEADERS
    include/CLHEP/Evaluator/Evaluator.h
    include/CLHEP/Evaluator/hash_map.icc
    include/CLHEP/Evaluator/stack.icc
    include/CLHEP/Evaluator/string.icc
    include/CLHEP/Geometry/BasicVector3D.h
    include/CLHEP/Geometry/Normal3D.h
    include/CLHEP/Geometry/Plane3D.h
    include/CLHEP/Geometry/Point3D.h
    include/CLHEP/Geometry/Transform3D.h
    include/CLHEP/Geometry/Vector3D.h
    include/CLHEP/Random/ranluxpp/helpers.h
    include/CLHEP/Random/ranluxpp/mulmod.h
    include/CLHEP/Random/ranluxpp/ranlux_lcg.h
    include/CLHEP/Random/DoubConv.h
    include/CLHEP/Random/DualRand.h
    include/CLHEP/Random/EngineFactory.h
    include/CLHEP/Random/engineIDulong.h
    include/CLHEP/Random/JamesRandom.h
    include/CLHEP/Random/mixmax_skip_N8.icc
    include/CLHEP/Random/mixmax_skip_N17.icc
    include/CLHEP/Random/mixmax_skip_N240.icc
    include/CLHEP/Random/MixMaxRng.h
    include/CLHEP/Random/MTwistEngine.h
    include/CLHEP/Random/NonRandomEngine.h
    include/CLHEP/Random/RandBinomial.h
    include/CLHEP/Random/RandBinomial.icc
    include/CLHEP/Random/RandBit.h
    include/CLHEP/Random/RandBreitWigner.h
    include/CLHEP/Random/RandBreitWigner.icc
    include/CLHEP/Random/RandChiSquare.h
    include/CLHEP/Random/RandChiSquare.icc
    include/CLHEP/Random/RandExponential.h
    include/CLHEP/Random/RandExponential.icc
    include/CLHEP/Random/RandFlat.h
    include/CLHEP/Random/RandFlat.icc
    include/CLHEP/Random/RandGamma.h
    include/CLHEP/Random/RandGamma.icc
    include/CLHEP/Random/RandGauss.h
    include/CLHEP/Random/RandGauss.icc
    include/CLHEP/Random/RandGaussQ.h
    include/CLHEP/Random/RandGaussQ.icc
    include/CLHEP/Random/RandGeneral.h
    include/CLHEP/Random/RandGeneral.icc
    include/CLHEP/Random/RandLandau.h
    include/CLHEP/Random/RandLandau.icc
    include/CLHEP/Random/RandPoisson.h
    include/CLHEP/Random/RandPoisson.icc
    include/CLHEP/Random/RandPoissonQ.h
    include/CLHEP/Random/RandPoissonQ.icc
    include/CLHEP/Random/RandStudentT.h
    include/CLHEP/Random/RandStudentT.icc
    include/CLHEP/Random/Random.h
    include/CLHEP/Random/Random.icc
    include/CLHEP/Random/RandomEngine.h
    include/CLHEP/Random/RandomEngine.icc
    include/CLHEP/Random/Randomize.h
    include/CLHEP/Random/RanecuEngine.h
    include/CLHEP/Random/Ranlux64Engine.h
    include/CLHEP/Random/RanluxppEngine.h
    include/CLHEP/Random/RanluxEngine.h
    include/CLHEP/Random/RanshiEngine.h
    include/CLHEP/Random/SeedTable.h
    include/CLHEP/Random/Stat.h
    include/CLHEP/Random/StaticRandomStates.h
    include/CLHEP/Random/gaussQTables.cdat
    include/CLHEP/Random/gaussTables.cdat
    include/CLHEP/Random/poissonTables.cdat
    include/CLHEP/Units/PhysicalConstants.h
    include/CLHEP/Units/SystemOfUnits.h
    include/CLHEP/Utility/defs.h
    include/CLHEP/Utility/keywords.h
    include/CLHEP/Utility/memory.h
    include/CLHEP/Utility/noncopyable.h
    include/CLHEP/Utility/use_atomic.h
    include/CLHEP/Vector/AxisAngle.h
    include/CLHEP/Vector/AxisAngle.icc
    include/CLHEP/Vector/Boost.h
    include/CLHEP/Vector/Boost.icc
    include/CLHEP/Vector/BoostX.h
    include/CLHEP/Vector/BoostX.icc
    include/CLHEP/Vector/BoostY.h
    include/CLHEP/Vector/BoostY.icc
    include/CLHEP/Vector/BoostZ.h
    include/CLHEP/Vector/BoostZ.icc
    include/CLHEP/Vector/EulerAngles.h
    include/CLHEP/Vector/EulerAngles.icc
    include/CLHEP/Vector/LorentzRotation.h
    include/CLHEP/Vector/LorentzRotation.icc
    include/CLHEP/Vector/LorentzVector.h
    include/CLHEP/Vector/LorentzVector.icc
    include/CLHEP/Vector/Rotation.h
    include/CLHEP/Vector/Rotation.icc
    include/CLHEP/Vector/RotationInterfaces.h
    include/CLHEP/Vector/RotationInterfaces.icc
    include/CLHEP/Vector/RotationX.h
    include/CLHEP/Vector/RotationX.icc
    include/CLHEP/Vector/RotationY.h
    include/CLHEP/Vector/RotationY.icc
    include/CLHEP/Vector/RotationZ.h
    include/CLHEP/Vector/RotationZ.icc
    include/CLHEP/Vector/ThreeVector.h
    include/CLHEP/Vector/ThreeVector.icc
    include/CLHEP/Vector/TwoVector.h
    include/CLHEP/Vector/TwoVector.icc
)

# - Sources
set(G4clhep_SOURCES
    src/AxisAngle.cc
    src/BasicVector3D.cc
    src/Boost.cc
    src/BoostX.cc
    src/BoostY.cc
    src/BoostZ.cc
    src/DoubConv.cc
    src/DualRand.cc
    src/EngineFactory.cc
    src/engineIDulong.cc
    src/erfQ.cc
    src/EulerAngles.cc
    src/Evaluator.cc
    src/flatToGaussian.cc
    src/gammln.cc
    src/JamesRandom.cc
    src/LorentzRotation.cc
    src/LorentzRotationC.cc
    src/LorentzRotationD.cc
    src/LorentzVectorB.cc
    src/LorentzVector.cc
    src/LorentzVectorC.cc
    src/LorentzVectorK.cc
    src/LorentzVectorL.cc
    src/LorentzVectorR.cc
    src/MixMaxRng.cc
    src/MTwistEngine.cc
    src/NonRandomEngine.cc
    src/Normal3D.cc
    src/Plane3D.cc
    src/Point3D.cc
    src/RandBinomial.cc
    src/RandBit.cc
    src/RandBreitWigner.cc
    src/RandChiSquare.cc
    src/RandExponential.cc
    src/RandFlat.cc
    src/RandGamma.cc
    src/RandGauss.cc
    src/RandGaussQ.cc
    src/RandGeneral.cc
    src/RandLandau.cc
    src/Random.cc
    src/RandomEngine.cc
    src/RandPoisson.cc
    src/RandPoissonQ.cc
    src/RandStudentT.cc
    src/RanecuEngine.cc
    src/Ranlux64Engine.cc
    src/RanluxppEngine.cc
    src/RanluxEngine.cc
    src/RanshiEngine.cc
    src/RotationA.cc
    src/Rotation.cc
    src/RotationC.cc
    src/RotationE.cc
    src/RotationInterfaces.cc
    src/RotationIO.cc
    src/RotationL.cc
    src/RotationP.cc
    src/RotationX.cc
    src/RotationY.cc
    src/RotationZ.cc
    src/setStdMath.cc
    src/setSystemOfUnits.cc
    src/SpaceVector.cc
    src/SpaceVectorD.cc
    src/SpaceVectorP.cc
    src/SpaceVectorR.cc
    src/StaticRandomStates.cc
    src/ThreeVector.cc
    src/ThreeVectorR.cc
    src/Transform3D.cc
    src/TwoVector.cc
    src/Vector3D.cc
    src/ZMinput.cc
)


#----------------------------------------------------------------------------
# Now add the library targets
#
include(Geant4MacroLibraryTargets)
GEANT4_LIBRARY_TARGET(NAME G4clhep SOURCES ${G4clhep_SOURCES} ${G4clhep_HEADERS})

# Interface usage requirements (build time clients only)
foreach(__g4clhep_target G4clhep G4clhep-static)
  if(TARGET ${__g4clhep_target})
    target_include_directories(${__g4clhep_target}
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      )
  endif()
endforeach()

#----------------------------------------------------------------------------
# Ensure the header directory gets added to the list of ones to export
#
set_property(GLOBAL APPEND PROPERTY GEANT4_BUILDTREE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


#----------------------------------------------------------------------------
# Install the headers, retaining their nested structure
#
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    COMPONENT Development
    PATTERN ".svn" EXCLUDE
    PATTERN "*.h"
    PATTERN ".icc")











