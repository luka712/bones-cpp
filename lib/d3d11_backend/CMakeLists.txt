# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB D3D11_BACKEND_SOURCES src/*.cpp src/**/*.cpp)

ADD_LIBRARY(BnsD3D11Backend STATIC ${D3D11_BACKEND_SOURCES})

# USE_D3D11 is defined in the root CMakeLists.txt
target_compile_options(BnsD3D11Backend PRIVATE -DUSE_D3D11=${USE_D3D11}
-DDEBUG=${DEBUG}
-DLOGGING_ENABLED=${LOGGING_ENABLED}
-DEBUG_BREAKPOINT_ENABLED=${DEBUG_BREAKPOINT_ENABLED})

# Find DirectX Libraries
# Path to DirectX SDK
# system 
link_directories("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64") 

target_link_libraries(BnsD3D11Backend PRIVATE d3d11 dxgi d3dcompiler)

include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries 
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../window/include

    # vendor

    # system 
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um"
)

