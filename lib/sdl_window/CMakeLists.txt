# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsSDLWindow STATIC src/SDLWindow.cpp)

# USE_WEBGPU is defined in the root CMakeLists.txt
target_compile_options(BnsSDLWindow PRIVATE 
    -DUSE_WEBGPU=${USE_WEBGPU} 
    -DUSE_METAL=${USE_METAL}
    -DUSE_D3D11=${USE_D3D11}
    -DUSE_OPENGL=${USE_OPENGL}
)

# Custom extension for WebGPU and SDL2
if(APPLE)
    target_compile_options(SDL2Extension PRIVATE -x objective-c)
else()
    target_compile_options(SDL2Extension PRIVATE)
endif()


# LIBRARIES
target_link_libraries(BnsSDLWindow BnsWindow)

if(USE_WEBGPU)
target_link_libraries(BnsWindow SDL2Extension BnsWebGPUBackend)
endif()

if(USE_OPENGL)
target_link_libraries(BnsWindow BnsOpenGLBackend)
endif()

if(USE_D3D11)
    target_link_libraries(BnsWindow BnsD3D11Backend)
endif()

if(USE_METAL)
    target_link_libraries(BnsWindow BnsMetalBackend)
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../opengl_backend/include

    # vendor
    ${CMAKE_BINARY_DIR}/_deps/dawn-src/include
    ${CMAKE_BINARY_DIR}/_deps/dawn-build/gen/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad
  
)

