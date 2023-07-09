# refere to https://eliemichel.github.io/LearnWebGPU/getting-started/project-setup.html as guide
cmake_minimum_required(VERSION 3.21)
project(
    BonesFramework # This is the name of the project
	VERSION 0.0.1 # The version of the project
)

include(utils.cmake)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/webgpu)
add_subdirectory(vendor/glfw3webgpu)

# Set the target architecture to arm64
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
elseif(UNIX)
    set(CMAKE_SYSTEM_PROCESSOR "aarch64")
endif()

if(APPLE)
    find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
    find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
    find_library(APPLE_FWK_METAL Metal REQUIRED)
endif()

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES 
src/*.cpp src/**/*.cpp src/**/**/*.cpp src/**/**/**/*.cpp 
headers/*.hpp headers/**/*.hpp headers/*.hpp headers/**/**/*.hpp headers/**/**/**/*.hpp)

# include it only once
include_guard(GLOBAL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/metal-cpp
)

# Add the executable
add_executable(App main.cpp ${SOURCES})

if(APPLE)
target_link_libraries(App ${SDL2_LIBRARIES} ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} glfw webgpu glfw3webgpu)
else()
target_link_libraries(App ${SDL2_LIBRARIES} glfw webgpu glfw3webgpu)

endif()

# Set the executable's properties for Xcode
if(XCODE)
    set_target_properties(App PROPERTIES
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal")
else()
# Set the executable's properties for Cmake
set_target_properties(App PROPERTIES CXX_STANDARD 17)
endif()
set_target_properties(webgpu PROPERTIES IMPORTED_LOCATION webgpu)
set_target_properties(App PROPERTIES VS_DEBUGGER_ENVIRONMENT "DAWN_DEBUG_BREAK_ON_ERROR=1")

# Disabled due to metal specific stuff
# target_treat_all_warnings_as_errors(App)

# The application's binary must find wgpu.dll or libwgpu.so at runtime,
# so we automatically copy it (it's called WGPU_RUNTIME_LIB in general)
# next to the binary.
target_copy_webgpu_binaries(App)