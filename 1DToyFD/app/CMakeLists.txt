add_executable( 1DFDToy 1DFDToy.cpp)
target_include_directories(1DFDToy PUBLIC "${PROJECT_SOURCE_DIR}/include")

if(ENABLE_SERIAL)
  target_compile_definitions(1DFDToy PRIVATE "ENABLE_SERIAL")
endif()

if(ENABLE_MPI)
  target_link_libraries( 1DFDToy PRIVATE MPI::MPI_CXX )
  target_compile_definitions(1DFDToy PRIVATE "ENABLE_MPI")
endif()
