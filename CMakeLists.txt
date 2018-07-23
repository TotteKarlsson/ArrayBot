cmake_minimum_required(VERSION 2.8)
project(atp)

SET(ATAPI_MAJOR_VERSION 0)
SET(ATAPI_MINOR_VERSION 8)
SET(ATAPI_BUILD_VERSION 5)
SET(ATAPI_VERSION "${ATAPI_MAJOR_VERSION}.${ATAPI_MINOR_VERSION}.${ATAPI_BUILD_VERSION}")

set(ATAPI_ROOT 	${CMAKE_CURRENT_SOURCE_DIR})
#mark_as_advanced(
#)

#Options
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

OPTION(BUILD_SHARED_LIBS 		    "Build Shared Libs"                         ON)
OPTION(INSTALL_CXX_LIBS 		    "Install CXX libraries and header"          OFF)
OPTION(INSTALL_PYTHON 			    "Build Python Module"                       OFF)
OPTION(INSTALL_CXX_EXAMPLES         "Install CXX Examples"	                    OFF)
 
#Boost root
set(BOOST_ROOT  CACHE PATH "Directory containing Boost.")
if("${BOOST_ROOT}" STREQUAL "")
  set(BOOST_ROOT "C:/Borland" CACHE PATH "Directory containing ThirdParty install" FORCE)
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/bin)

#=== COMPILER SPECIFICS 
if(${BORLAND})
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")
    set(SUPPRESS_WARNINGS   "-w-8128 -w-8057 -w-8012 -w-8004 -w-8070" )
    include_directories( 
        )
endif()

#Warning string looks different depending on the compiler..
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SUPPRESS_WARNINGS}")

#ThidParty include
    set(THIRD_PARTY_INSTALL_PREFIX  CACHE PATH "Directory containing ThirdParty install.")
    if("${THIRD_PARTY_INSTALL_PREFIX}" STREQUAL "")
      set(THIRD_PARTY_INSTALL_PREFIX "x:/" CACHE PATH "Directory containing ThirdParty install" FORCE)
    endif()

set(TP_INCLUDE                     ${THIRD_PARTY_INSTALL_PREFIX}/include)

if(${INSTALL_PYTHON})
    OPTION(INSTALL_PYTHON_EXAMPLES  "Install Python Examples"	                 ON)
    find_package(PythonInterp)
    find_package(PythonLibs)
    message("Python include folder: " ${PYTHON_INCLUDE_DIRS})
    include_directories(
    ${PYTHON_INCLUDE_DIRS}
    )
endif()

include_directories(
${BOOST_ROOT}
${BOOST_ROOT}/boost/tr1/tr1
)

link_directories(
${THIRD_PARTY_INSTALL_PREFIX}/lib
)
   
#Source Code Folders
add_subdirectory(source)
add_subdirectory(wrappers)
add_subdirectory(Examples)

#======================= INSTALL ========================================================
set(RootDest .)
install (FILES 
    README.txt 
    LICENSE.txt 
    AUTHORS.txt 
    VERSION.txt 
    INSTALL.txt 
    NOTICE.txt
    CHANGELOG.txt
    DESTINATION ${RootDest} 	
    COMPONENT info
   )

