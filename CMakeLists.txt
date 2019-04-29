# Set minimum version
cmake_minimum_required(VERSION 3.9.6)

# Set project
project(infr10067 LANGUAGES CXX)

# Set sources to source files under src directory
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add library
add_library(infr10067 SHARED ${SOURCES})

# Include include directory
target_include_directories(infr10067
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(infr10067 PROPERTIES PUBLIC_HEADER include/rail_fence.hpp)

include(GNUInstallDirs)

install(TARGETS infr10067
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

target_compile_options(infr10067 PRIVATE -Werror)
target_compile_features(infr10067 PRIVATE cxx_std_17)
