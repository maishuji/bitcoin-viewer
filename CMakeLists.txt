cmake_minimum_required(VERSION 3.10)
project(BitcoinPlot)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Python3 and NumPy
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

# Find libcurl
find_package(CURL REQUIRED)

# Find nlohmann_json
find_package(nlohmann_json REQUIRED)

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
)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp src/plot.cpp)

add_custom_command(
    OUTPUT ${PROJECT_SOURCE_DIR}/include/external/matplotlibcpp.h
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/matplotlibcpp/src/matplotlibcpp/matplotlibcpp.h
        ${PROJECT_SOURCE_DIR}/include/external/matplotlibcpp.h
    DEPENDS matplotlibcpp  # Ensure this happens after matplotlibcpp is downloaded
    COMMENT "Copying matplotlibcpp.h to the src directory"
)

# Create a custom target to trigger the copy before building the main project
add_custom_target(copy_matplotlibcpp_header ALL
    DEPENDS ${PROJECT_SOURCE_DIR}/include/external/matplotlibcpp.h
)

# Make sure matplotlibcpp is downloaded before compiling
add_dependencies(${PROJECT_NAME} copy_matplotlibcpp_header)

target_include_directories(${PROJECT_NAME} PUBLIC include)

# Link Python3 libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Python3::Python 
        Python3::NumPy 
        CURL::libcurl 
        nlohmann_json::nlohmann_json)