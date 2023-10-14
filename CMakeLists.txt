# refere to https://eliemichel.github.io/LearnWebGPU/getting-started/project-setup.html as guide
cmake_minimum_required(VERSION 3.21)
project(
    BonesFramework # This is the name of the project
	VERSION 0.0.1 # The version of the project
)

include(FetchContent)
include(utils.cmake)

# If we are on Apple, we can use Metal or WebGPU.
set(USE_METAL 1)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Leave this for now
# find_package(SDL2 REQUIRED) # Find the SDL2 library, assumes it's installed system-wide

# SDL2 - get it from github and build it
FetchContent_Declare(
    SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.3)
FetchContent_MakeAvailable(SDL2)


add_subdirectory(vendor/webgpu)
add_subdirectory(vendor/SDL2Extension)

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
headers/*.hpp headers/**/*.hpp headers/*.hpp headers/**/**/*.hpp headers/**/**/**/*.hpp
vendor/tinyxml2/tinyxml2.cpp
)

# copy assets to build/assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/assets)


# include it only once
include_guard(GLOBAL)


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

# Custom extension for WebGPU and SDL2
target_compile_options(SDL2Extension PRIVATE -x objective-c)

# If we are on Apple, we can use Metal or WebGPU (Metal is the default)
target_compile_options(App PRIVATE -DUSE_METAL=${USE_METAL})

if(WIN32)
    # SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
    if(TARGET SDL2::SDL2main)
        # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
        target_link_libraries(App PRIVATE SDL2::SDL2main)
    endif()
endif()


if(APPLE)
# Link the libraries to the executable (SDL2, Metal, QuartzCore, Foundation) 
target_link_libraries(App PRIVATE SDL2::SDL2 ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} glfw webgpu SDL2Extension)
else()
target_link_libraries(App PRIVATE SDL2::SDL webgpu SDL2Extension)
endif()


    # copy SDL2.dll, SDL2_image.dll to the output directory
add_custom_command(TARGET App POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:App>
)



# Set the executable's properties for Xcode
if(XCODE)

    # Copy non source files to build dir such as shaders, assets, etc
    add_custom_command(TARGET App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders 
        ${CMAKE_CURRENT_BINARY_DIR}/Debug/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets 
        ${CMAKE_CURRENT_BINARY_DIR}/Debug/assets
    COMMENT "Copying non-build folders(shaders,assets) to build dir"
    )

    # enable metal frame capture
    set_target_properties(App PROPERTIES
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal")
else()
# Set the executable's properties for Cmake
set_target_properties(App PROPERTIES CXX_STANDARD 17)
endif()

# set 
set_target_properties(webgpu PROPERTIES IMPORTED_LOCATION webgpu)
set_target_properties(App PROPERTIES VS_DEBUGGER_ENVIRONMENT "DAWN_DEBUG_BREAK_ON_ERROR=1")

# Disabled due to metal specific stuff
# target_treat_all_warnings_as_errors(App)

# The application's binary must find wgpu.dll or libwgpu.so at runtime,
# so we automatically copy it (it's called WGPU_RUNTIME_LIB in general)
# next to the binary.
target_copy_webgpu_binaries(App)
