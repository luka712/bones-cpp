# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsSDLWindow STATIC src/SDLWindow.cpp)

# Custom extension for WebGPU and SDL2
if(APPLE)
    target_compile_options(SDL2Extension PRIVATE -x objective-c)
else()
    target_compile_options(SDL2Extension PRIVATE)
endif()


# LIBRARIES
target_link_libraries(BnsSDLWindow SDL2Extension BnsWindow BnsWebGPUBackend)
if(WIN32)
    target_link_libraries(BnsSDLWindow BnsD3D11Backend)
elseif(APPLE)
    target_link_libraries(BnsSDLWindow BnsMetalBackend)
endif()


include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../window/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../webgpu_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../d3d11_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../metal_backend/include

    # vendor
    ${CMAKE_BINARY_DIR}/_deps/dawn-src/include
    ${CMAKE_BINARY_DIR}/_deps/dawn-build/gen/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor
  
)

