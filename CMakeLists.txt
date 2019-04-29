# Set minimum version
cmake_minimum_required(VERSION 3.9.6)

# Set project
project(mycyrpto LANGUAGES CXX)

# Set sources to source files under src directory
file(GLOB SOURCES "src/*.cpp")

# Add FAL executable
add_library(mycrypto SHARED ${SOURCES})

# Include include directory
target_include_directories(mycrypto
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS mycrypto DESTINATION lib/mycrypto)

file(GLOB HEADERS include/*.hpp)

install(FILES ${HEADERS} DESTINATION include/mycrypto)

target_compile_options(mycrypto PRIVATE -Werror)
target_compile_features(mycrypto PRIVATE cxx_std_17)
