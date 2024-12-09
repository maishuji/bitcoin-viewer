cmake_minimum_required(VERSION 3.10)
project(BitcoinPlot)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Python3 and NumPy
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

# Add an ExternalProject to fetch matplotlibcpp.h
include(ExternalProject)

# Set the destination directory for the header file
set(MATPLOTLIBCPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)

# Download the latest matplotlibcpp.h
ExternalProject_Add(
    matplotlibcpp
    PREFIX ${CMAKE_BINARY_DIR}/matplotlibcpp
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_DISCONNECTED ON
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    LOG_INSTALL ON
    LOG_UPDATE ON
    # Copy the header file to the destination directory
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/matplotlibcpp/src/matplotlibcpp/matplotlibcpp.h 
        ${PROJECT_SOURCE_DIR}/matplotlibcpp.h
)
message(STATUS "Bin dir : ${CMAKE_BINARY_DIR}")

# Add executable
add_executable(bitcoin_plot src/main.cpp src/plot.cpp)

# Make sure matplotlibcpp is downloaded before compiling
add_dependencies(bitcoin_plot matplotlibcpp)

# Link Python3 libraries
target_link_libraries(bitcoin_plot PRIVATE Python3::Python Python3::NumPy)