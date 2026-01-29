cmake_minimum_required(VERSION 3.10)
project(ida-rpc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# IDA SDK path
set(IDA_SDK_DIR "$ENV{HOME}/idasdk91/idasdk91" CACHE PATH "Path to IDA SDK")
set(IDA_INSTALL_DIR "$ENV{HOME}/ida-pro-9.1" CACHE PATH "Path to IDA installation")

# Check if SDK exists
if(NOT EXISTS "${IDA_SDK_DIR}/include/ida.hpp")
    message(FATAL_ERROR "IDA SDK not found at ${IDA_SDK_DIR}")
endif()

# Plugin source files
set(SOURCES
    main.cpp
    options.cpp
)

# Create shared library (IDA plugin)
add_library(ida-rpc64 SHARED ${SOURCES})

# Include directories
target_include_directories(ida-rpc64 PRIVATE
    ${IDA_SDK_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/discord-rpc/linux64-static/include
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/lib-utils
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/build-version
)

# Platform definitions for Linux 64-bit
target_compile_definitions(ida-rpc64 PRIVATE
    __LINUX__
    __X64__
    __IDP__
    __EA64__
    _Release64
    USE_STANDARD_FILE_FUNCTIONS
)

# Compiler flags
target_compile_options(ida-rpc64 PRIVATE
    -fPIC
    -fvisibility=hidden
    -Wno-deprecated-declarations
)

# Link directories
target_link_directories(ida-rpc64 PRIVATE
    ${IDA_SDK_DIR}/lib/x64_linux_gcc_64
    ${CMAKE_CURRENT_SOURCE_DIR}/discord-rpc/linux64-static/lib
)

# Link libraries
target_link_libraries(ida-rpc64 PRIVATE
    ida
    discord-rpc
    pthread
)

# Set output name without lib prefix
set_target_properties(ida-rpc64 PROPERTIES
    PREFIX ""
    OUTPUT_NAME "ida-rpc64"
    SUFFIX ".so"
)

# Install to IDA plugins directory
install(TARGETS ida-rpc64
    LIBRARY DESTINATION ${IDA_INSTALL_DIR}/plugins
)
