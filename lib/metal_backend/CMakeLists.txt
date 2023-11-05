# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsMetalBackend STATIC src/texture/MetalTexture2D.cpp)

# Set the target architecture to arm64 for Apple Silicon
set(CMAKE_OSX_ARCHITECTURES "arm64")
find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
find_library(APPLE_FWK_METAL Metal REQUIRED)


target_link_libraries(BnsMetalBackend PRIVATE ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} BnsTexture)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # lib 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering-backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include

    # vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor
)

