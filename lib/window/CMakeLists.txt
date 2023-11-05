# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsWindow STATIC src/Window.cpp)

# LIBRARIES
target_link_libraries(BnsWindow BnsWebGPUBackend)
if(WIN32)
    target_link_libraries(BnsWindow BnsD3D11Backend)
elseif(APPLE)
    target_link_libraries(BnsWindow BnsMetalBackend)
endif()


include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../webgpu_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../d3d11_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../metal_backend/include

    # vendor
    ${CMAKE_BINARY_DIR}/_deps/dawn-src/include
    ${CMAKE_BINARY_DIR}/_deps/dawn-build/gen/include
  
)

