#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : G4externals
# Package: Geant4.src.G4externals
#------------------------------------------------------------------------------

# - Recurse into subdirectories as needed
if(NOT GEANT4_USE_SYSTEM_CLHEP)
  add_subdirectory(clhep)
endif()

if(NOT GEANT4_USE_SYSTEM_EXPAT)
  add_subdirectory(expat)
endif()

if(NOT GEANT4_USE_SYSTEM_ZLIB)
  add_subdirectory(zlib)
endif()

# - G4tools always built
add_subdirectory(g4tools)

# PTL requires additional pre and post inclusion steps as it's a true subproject
if(NOT GEANT4_USE_SYSTEM_PTL)
  set(CMAKE_INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}/PTL)
  set(PTL_USE_TBB ${GEANT4_USE_TBB})

  if(NOT (GEANT4_BUILD_SANITIZER STREQUAL "none"))
    set(PTL_USE_SANITIZER ON)
    set(PTL_SANITIZER_TYPE ${GEANT4_BUILD_SANITIZER})
  endif()

  set(PTL_USE_LOCKS ${GEANT4_USE_PTL_LOCKS})

  add_subdirectory(ptl)
  # Needs to be in defined category list for static/shared to be linked correctly.
  set_property(GLOBAL APPEND PROPERTY GEANT4_DEFINED_CATEGORIES G4ptl)
  # ... and added to build dir include paths in scripts
  set_property(GLOBAL APPEND PROPERTY GEANT4_BUILDTREE_INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/ptl/include)
endif()

#----------------------------------------------------------------------------
# Alias the tasking libraries to Geant4 target naming convention
#
if(TARGET ptl-shared)
  add_library(G4ptl INTERFACE)
  target_link_libraries(G4ptl INTERFACE PTL::ptl-shared)
  install(TARGETS G4ptl
    EXPORT Geant4LibraryDepends
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
  add_library(Geant4::G4ptl ALIAS G4ptl)
endif()

if(TARGET ptl-static)
  add_library(G4ptl-static INTERFACE)
  target_link_libraries(G4ptl-static INTERFACE PTL::ptl-static)
  install(TARGETS G4ptl-static
    EXPORT Geant4LibraryDepends
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
  add_library(Geant4::G4ptl-static ALIAS G4ptl-static)
endif()
