#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(ACsim)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

set(CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
find_package(ROOT REQUIRED)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})



#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


root_generate_dictionary(
  ACBaseHitDict            # path to dictionary to generate
  ACBaseHit.hh  # list of includes
  LINKDEF       # list of classes to process
  ACBaseHitLinkDef.hh                    # ROOT linkDef file
)
add_library(hit SHARED ACBaseHitDict.cxx)
set(sources ${sources} ACBaseHitDict.cxx)  # append dictionary to sources

root_generate_dictionary(
  ACBaseTrackDict            # path to dictionary to generate
  ACBaseTrack.hh  # list of includes
  LINKDEF       # list of classes to process
  ACBaseTrackLinkDef.hh                    # ROOT linkDef file
)
add_library(track SHARED ACBaseTrackDict.cxx)
set(sources ${sources} ACBaseTrackDict.cxx)  # append dictionary to sources


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(ACsim ACsim.cc ${sources} ${headers})
target_link_libraries(ACsim hit track ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build ACsim. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(ACsim_SCRIPTS
    ACsim.in vis.mac
  )

foreach(_script ${ACsim_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ACsim DESTINATION bin)

