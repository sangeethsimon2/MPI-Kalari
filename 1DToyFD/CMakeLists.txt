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
# include_directories("${MPI_CXX_INCLUDE_DIRS}")
endif()

#add_subdirectory(src)
add_subdirectory(app)

