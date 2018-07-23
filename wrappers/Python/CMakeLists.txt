cmake_minimum_required(VERSION 2.8)
project(atfoundation)
find_package(SWIG REQUIRED)
include(UseSWIG)

find_package(PythonInterp)
find_package(PythonLibs)
get_filename_component(PYTHON_LIB_FOLDER ${PYTHON_LIBRARIES} DIRECTORY CACHE)
message("Python lib folder: "       ${PYTHON_LIB_FOLDER})
message("Python include folder: "   ${PYTHON_INCLUDE_DIRS})
message("Python libraries: "        ${PYTHON_LIBRARIES})
message("CMake Install folder: "    ${CMAKE_INSTALL_PREFIX})

set(PyModule "atfoundation")
include_directories(
    .
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ATAPI_ROOT}
    ${ATAPI_ROOT}/source
    ${ATAPI_ROOT}/source/core
    ${THIRD_PARTY_INSTALL_PREFIX}/include
    ${THIRD_PARTY_INSTALL_PREFIX}/include/dsl
    ${CMAKE_INSTALL_PREFIX}/lib
    ${PYTHON_INCLUDE_PATH}
)

link_directories(
${THIRD_PARTY_INSTALL_PREFIX}/lib
${CMAKE_BINARY_DIR}/lib
${PYTHON_LIB_FOLDER}
)

# set(CMAKE_SWIG_FLAGS "-DPOCO_STATIC")
set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_CURRENT_SOURCE_DIR}/${PyModule}.def)

set_source_files_properties(${PyModule}.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${PyModule}.i PROPERTIES SWIG_FLAGS "-threads")

SWIG_ADD_LIBRARY(${PyModule}
    TYPE MODULE 
    LANGUAGE python 
    SOURCES ${PyModule}.i
    )
    
TARGET_LINK_LIBRARIES (${PyModule}
    atCore
    ${CMAKE_INSTALL_PREFIX}/lib/dslPlugins.lib
    ${CMAKE_INSTALL_PREFIX}/lib/dslPythonPlugins.lib
    ${THIRD_PARTY_INSTALL_PREFIX}/lib/poco_foundation.lib
    ${PYTHON_LIB_FOLDER}/Python37_CG.lib
)

# INSTALL PYTHON BINDINGS
# Get the python site packages directory by invoking python
execute_process(COMMAND python -c "import site; print(site.getsitepackages()[0])" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
message("PYTHON_SITE_PACKAGES = ${PYTHON_SITE_PACKAGES}")

install(
    TARGETS ${PyModule}
    DESTINATION ${PYTHON_SITE_PACKAGES})

install(
    FILES         ${PyModule}.i
    DESTINATION   include/dsl
)

install(
    FILES         ${CMAKE_CURRENT_BINARY_DIR}/${PyModule}.py 
                  ${CMAKE_BINARY_DIR}/lib/_${PyModule}.tds
    DESTINATION   ${PYTHON_SITE_PACKAGES}
)
