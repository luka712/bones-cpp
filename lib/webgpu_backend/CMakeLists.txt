# BnsWebGPUBackend - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsWebGPUBackend STATIC 
            src/texture/WebGPUTexture2D.cpp
            src/util/WebGPUTextureViewDescriptorUtil.cpp)

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
    target_link_libraries(BnsWebGPUBackend PRIVATE ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} BnsTexture)
else()
    target_link_libraries(BnsWebGPUBackend PRIVATE BnsTexture)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # lib 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering-backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include

    # vendor
    ${CMAKE_BINARY_DIR}/_deps/dawn-src/include
    ${CMAKE_BINARY_DIR}/_deps/dawn-build/gen/include
)

