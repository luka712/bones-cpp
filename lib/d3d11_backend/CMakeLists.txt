# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsD3D11Backend STATIC src/main.cpp)

# Find DirectX Libraries
# Path to DirectX SDK
# system 
link_directories("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64") 

target_link_libraries(BnsD3D11Backend PRIVATE d3d11 dxgi d3dcompiler BnsTexture)

include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering-backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include

    # vendor

    # system 
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um"
)

