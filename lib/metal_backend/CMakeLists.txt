# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB METAL_BACKEND_SOURCES src/*.cpp src/**/*.cpp)

ADD_LIBRARY(BnsMetalBackend STATIC ${METAL_BACKEND_SOURCES})

# USE_METAL is defined in the root CMakeLists.txt
target_compile_options(BnsMetalBackend PRIVATE -DUSE_METAL=${USE_METAL})

# Set the target architecture to arm64 for Apple Silicon
set(CMAKE_OSX_ARCHITECTURES "arm64")
find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
find_library(APPLE_FWK_METAL Metal REQUIRED)


target_link_libraries(BnsMetalBackend PRIVATE ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL} 
BnsRenderingBackend BnsWindow)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # lib 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../window/include

    # vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor
)

