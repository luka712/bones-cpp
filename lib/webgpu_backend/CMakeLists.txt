# BnsWebGPUBackend - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB WEBGPU_BACKEND_SOURCES src/*.cpp src/**/*.cpp)

# USE_WEBGPU is required for window
ADD_LIBRARY(BnsWebGPUBackend STATIC ${WEBGPU_BACKEND_SOURCES})

# Set the target architecture to arm64 for Apple Silicon
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
    find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
    find_library(APPLE_FWK_METAL Metal REQUIRED)
endif()

# COMPILE OPTIONS
target_compile_options(BnsWebGPUBackend PRIVATE -DUSE_WEBGPU=1)

if(APPLE)
    target_link_libraries(BnsWebGPUBackend  PRIVATE ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} BnsRenderingBackend BnsWindow)
else()
    target_link_libraries(BnsWebGPUBackend  PRIVATE BnsRenderingBackend BnsWindow)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # lib 
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../window/include

    # vendor
    ${CMAKE_BINARY_DIR}/_deps/dawn-src/include
    ${CMAKE_BINARY_DIR}/_deps/dawn-build/gen/include
)

