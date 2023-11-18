# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsWindow STATIC src/Window.cpp)

# TARGET CONFIGURATION
target_compile_options(BnsWindow PRIVATE 
    -DUSE_WEBGPU=${USE_WEBGPU} 
    -DUSE_METAL=${USE_METAL}
    -DUSE_D3D11=${USE_D3D11}
    -DUSE_OPENGL=${USE_OPENGL}
    -DUSE_OPENGLES=${USE_OPENGLES}
) 

# LIBRARIES
if(USE_WEBGPU)
target_link_libraries(BnsWindow BnsWebGPUBackend)
endif()

if(USE_OPENGL)
target_link_libraries(BnsWindow BnsOpenGLBackend)
endif()

if(USE_OPENGLES)
target_link_libraries(BnsWindow BnsOpenGLESBackend)
endif()

if(USE_D3D11)
    target_link_libraries(BnsWindow BnsD3D11Backend)
endif()

if(USE_METAL)
    target_link_libraries(BnsWindow BnsMetalBackend)
endif()

target_link_libraries(BnsWindow BnsCommon)

# INCLUDES
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor
)

if(USE_OPENGL)
    include_directories(
        # project 
        ${CMAKE_CURRENT_SOURCE_DIR}/../opengl_backend/include

        # vendor
        ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad
    )
endif()

if(USE_OPENGLES)
    include_directories(
        # project
        ${CMAKE_CURRENT_SOURCE_DIR}/../opengles_backend/include
        
        # vendor
        ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad_es
    )
endif()

