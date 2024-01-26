cmake_minimum_required(VERSION 3.23)

project(
    1DFDToy
    VERSION 0.1
    LANGUAGES CXX
    )

#Set CXX version and make it required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

option(ENABLE_SERIAL "ENABLE_SERIAL" OFF)
option(ENABLE_MPI "ENABLE_MPI" ON)

if (ENABLE_MPI)
  find_package(MPI  REQUIRED)
  if (MPI_CXX_FOUND)
    message(STATUS "MPI Found")
  else()
    message(FATAL_ERROR "MPI Not Found")
  endif()
endif()

add_executable( 1DFDToy )
target_include_directories(1DFDToy PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_sources(1DFDToy PRIVATE
               src/1DFDToy.cpp
               src/allocateMemory.cpp
               src/deAllocateMemory.cpp
               src/MPIUtils.cpp
               src/initialize.cpp
               src/updateVector.cpp
)

if(ENABLE_SERIAL)
  target_compile_definitions(1DFDToy PRIVATE "ENABLE_SERIAL")
endif()

if(ENABLE_MPI)
  target_link_libraries( 1DFDToy PRIVATE MPI::MPI_CXX )
  target_compile_definitions(1DFDToy PRIVATE "ENABLE_MPI")
endif()
