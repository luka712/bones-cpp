# refere to https://eliemichel.github.io/LearnWebGPU/getting-started/project-setup.html as guide
cmake_minimum_required(VERSION 3.21)
project(
    BonesFramework # This is the name of the project
	VERSION 0.0.1 # The version of the project
)

include(FetchContent)
include(utils.cmake)

set(VULKAN_SDK_PATH )
set(VULKAN_INCLUDE "D:/VulkanSDK/1.3.268.0/Include")
set(VULKAN_LIB_DIR "D:/VulkanSDK/1.3.268.0/Lib")

# there are set specific for my machine, please change according to machine
if(WIN32)
    set(WINDOWS_SDK "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um")
endif()

# BACKEND RENDERER FLIPS, also used by /lib
# Multiplatform
set(USE_WEBGPU 0)

# Windows/Linux/Mac 
set(USE_OPENGL 0) 

# Windows/Linux 
set(USE_OPENGLES 0)
set(USE_VULKAN 1)

# Mac specific
set(USE_METAL 0)
# Windows specific
set(USE_D3D11 0)

# DEBUG 
# flips debug mode on/off
# webgpu backend has a debug mode that breaks on errors
set(DEBUG 1)
# flips debug breakpoint on/off. It is used throught the project to break on validation errors
set(DEBUG_BREAKPOINT_ENABLED 1)
# flips logging on/off. It is used throught the project to log errors and other info.
set(LOGGING_ENABLED 1)

# LIGHTS 
# Number of point lights available for sprite renderer when forward rendering is used 
set(FORWARD_2D_NUM_OF_POINT_LIGHTS 1)

# SDL2 - get it from github and build it
FetchContent_Declare(
    SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.3)
FetchContent_MakeAvailable(SDL2)

# If OpenGL is used, we need to find it
if(USE_OPENGL OR USE_OPENGLES)
find_package(OpenGL REQUIRED)
endif()

# VENDOR LIBRARIES
add_subdirectory(vendor/webgpu)
add_subdirectory(vendor/SDL2Extension)
if(USE_OPENGL)
add_subdirectory(vendor/glad EXCLUDE_FROM_ALL)
endif()
if(USE_OPENGLES)
add_subdirectory(vendor/glad_es EXCLUDE_FROM_ALL)
endif()

# PROJECT LIBRARIES
add_subdirectory(lib/common)
add_subdirectory(lib/window)
add_subdirectory(lib/sdl_window)
add_subdirectory(lib/loaders)
add_subdirectory(lib/math)
add_subdirectory(lib/rendering_backend)
if(USE_METAL)
    add_subdirectory(lib/metal_backend)
endif()
if(USE_D3D11)
    add_subdirectory(lib/d3d11_backend)
endif()
if(USE_WEBGPU)
    add_subdirectory(lib/webgpu_backend)
endif()
if(USE_OPENGL)
    add_subdirectory(lib/opengl_backend)
endif()
if(USE_OPENGLES)
    add_subdirectory(lib/opengles_backend)
endif()
if(USE_VULKAN)
    add_subdirectory(lib/vulkan_backend)
endif()

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
if(WIN32)
# TODO: add windows flags   
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
else() 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")
endif()
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

if(USE_OPENGL)
include_directories(
        # vendor     
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad
        # The lib dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/opengl_backend/include
    )
endif()
if(USE_OPENGLES)
include_directories(
        # vendor     
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad_es
        # The lib dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/opengles_backend/include
    )
endif()
if(USE_VULKAN)
include_directories(
        # the lib dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/vulkan_backend/include

        # The machine dependencies
        ${VULKAN_INCLUDE}
)
endif()

if(WIN32)
    include_directories(${WINDOWS_SDK})
endif()


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/headers

    # vendor 
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/webgpu/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include

    # The lib dependencies
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/window/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl_window/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/rendering_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/metal_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/webgpu_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/d3d11_backend/include
    SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/metal-cpp
)



# Add the executable
add_executable(App main.cpp ${SOURCES})

# COMPILE OPTIONS
# Custom extension for WebGPU and SDL2
if(APPLE)
    target_compile_options(SDL2Extension PRIVATE -x objective-c)
else()
    target_compile_options(SDL2Extension PRIVATE)
endif()

if(USE_OPENGL)
target_compile_options(glad PRIVATE)
endif()

if(USE_OPENGLES)
target_compile_options(glad_es PRIVATE)
endif()

# If we are on Apple, we can use Metal or WebGPU (Metal is the default)
target_compile_options(App PRIVATE 
-DDEBUG=${DEBUG} -DDEBUG_BREAKPOINT_ENABLED=${DEBUG_BREAKPOINT_ENABLED} -DLOGGING_ENABLED=${LOGGING_ENABLED}
-DUSE_METAL=${USE_METAL} -DUSE_D3D11=${USE_D3D11} -DUSE_WEBGPU=${USE_WEBGPU} -DUSE_OPENGL=${USE_OPENGL} -DUSE_OPENGLES=${USE_OPENGLES} -DUSE_VULKAN=${USE_VULKAN}
-DFORWARD_2D_NUM_OF_POINT_LIGHTS=${FORWARD_2D_NUM_OF_POINT_LIGHTS}
) 


# LINK LIBRARIES SECTION

# ADDITIONAL LINK DIRECTORIES
link_directories({WINDOWS_SDK})

target_link_directories(App PRIVATE ${VULKAN_LIB_DIR})

if(WIN32)
    # SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
    if(TARGET SDL2::SDL2main)
        # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
        target_link_libraries(App PRIVATE SDL2::SDL2main)
    endif()
endif()

# Link libraries which are shared between different targets
target_link_libraries(App PRIVATE BnsCommon)

if(APPLE)
# Link the libraries to the executable (SDL2, Metal, QuartzCore, Foundation) 
target_link_libraries(App PRIVATE SDL2::SDL2 ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} SDL2Extension 
BnsWindow
BnsSDLWindow
BnsLoaders 
BnsMath 
BnsRenderingBackend
)
elseif(WIN32)
target_link_libraries(App PRIVATE SDL2::SDL2 d3d11 dxgi d3dcompiler SDL2Extension 
BnsWindow
BnsSDLWindow
BnsLoaders 
BnsMath 
BnsRenderingBackend
)
else()
target_link_libraries(App PRIVATE SDL2::SDL2 SDL2Extension
BnsWindow
BnsSDLWindow
BnsLoaders 
BnsMath 
BnsRenderingBackend
)
endif()

# glad must be linked if OpenGL is used as it provides headers
if(USE_OPENGL)
    target_link_libraries(App PRIVATE glad BnsOpenGLBackend)
endif()
if(USE_OPENGLES)
    target_link_libraries(App PRIVATE glad_es BnsOpenGLESBackend)
endif()
if(USE_WEBGPU)
    target_link_libraries(App PRIVATE webgpu BnsWebGPUBackend)
endif()
if(USE_D3D11)
    target_link_libraries(App PRIVATE BnsD3D11Backend)
endif()
if(USE_METAL)
    target_link_libraries(App PRIVATE BnsMetalBackend)
endif()
if(USE_VULKAN)
    target_link_libraries(App PRIVATE vulkan-1 BnsVulkanBackend)
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
elseif(WIN32)
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)
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

if(WIN32)
    # copy SDL2.dll, SDL2_image.dll to the output directory
    add_custom_command(TARGET App POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:App>
           #  $<TARGET_FILE:SDL2_image::SDL2_image> $<TARGET_FILE_DIR:App>
            )
endif()
