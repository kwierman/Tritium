# Kevin Wierman <kwierman@physics.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Tritium)
#----------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS ${PROJECT_NAME} " requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()
#----------------------------------------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()
#----------------------------------------------------------------------------
#Use the FindRoot Macro to link the executable against ROOT
include(cmake/FindROOT.cmake)
find_package(Boost 1.36 REQUIRED filesystem system)
include_directories(${ROOT_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})
#----------------------------------------------------------------------------
# Locate sources and headers for this project
set(SOURCE_FOLDERS Design Common IO  )
set(SOURCE_HEADERS)
set(SOURCE_FILES)
#set(LIBRARY_LIST)
foreach( folder ${SOURCE_FOLDERS})
	message(STATUS "Configuring Library: " ${GRANULAR_LIBRARY})
	file(GLOB sources ${PROJECT_SOURCE_DIR}/${folder}/src/*.cxx )
	file(GLOB headers ${PROJECT_SOURCE_DIR}/${folder}/inc/*.h )
	include_directories(${PROJECT_SOURCE_DIR}/${folder}/inc/)
	foreach(source ${sources})
		list(APPEND SOURCE_FILES ${source})
	endforeach()
	foreach(header ${headers})
		list(APPEND SOURCE_HEADERS ${header})
	endforeach()	
endforeach()
#----------------------------------------------------------------------------
# Build Libraries
add_library(Tritium SHARED ${SOURCE_HEADERS} ${SOURCE_FILES}  )
#set_target_properties(TritiumMC PROPERTIES LINKER_LANGUAGE CXX )
target_link_libraries(Tritium ${ROOT_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS Tritium DESTINATION lib)
#----------------------------------------------------------------------------
# Locate Executables, and link against all libraries
#file(GLOB applications ${PROJECT_SOURCE_DIR}/Applications/*.cxx)
file(GLOB applications ${PROJECT_SOURCE_DIR}/Applications/Tritium*.cxx)
foreach(_app ${applications})
	get_filename_component (name_without_extension ${_app} NAME_WE)
	add_executable(${name_without_extension} ${_app} )#${sources} ${headers})
	target_link_libraries(${name_without_extension} ${ROOT_LIBRARIES} ${LIBRARY_LIST} Tritium ${Boost_LIBRARIES})
	install(TARGETS ${name_without_extension} DESTINATION bin)
endforeach()
#----------------------------------------------------------------------------
#Add in Documentation
#add_subdirectory(Documentation)
#----------------------------------------------------------------------------


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
