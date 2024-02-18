# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsSDLWindow STATIC src/SDLWindow.cpp src/time/SDLTimeManager.cpp)

# USE_WEBGPU is defined in the root CMakeLists.txt
target_compile_options(BnsSDLWindow PRIVATE 
    -DUSE_WEBGPU=${USE_WEBGPU} 
    -DUSE_METAL=${USE_METAL}
    -DUSE_D3D11=${USE_D3D11}
    -DUSE_OPENGL=${USE_OPENGL}
    -DUSE_OPENGLES=${USE_OPENGLES}
    -DUSE_VULKAN=${USE_VULKAN}

    # Debug options
    -DDEBUG=${DEBUG} 
    -DLOGGING_ENABLED=${LOGGING_ENABLED}
    -DDEBUG_BREAKPOINT_ENABLED=${DEBUG_BREAKPOINT_ENABLED}
)

# Custom extension for WebGPU and SDL2
if(APPLE)
    target_compile_options(SDL2Extension PRIVATE -x objective-c)
else()
    target_compile_options(SDL2Extension PRIVATE)
endif()

# LINK DIRECTORIES
if(USE_VULKAN)
    # VULKAN_LIB is defined in the root CMakeLists.txt
    link_directories(${VULKAN_LIB})
endif()

# LIBRARIES
target_link_libraries(BnsSDLWindow BnsCore BnsWindow)

if(USE_WEBGPU)
target_link_libraries(BnsWindow SDL2Extension BnsWebGPUBackend)
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

if(USE_VULKAN)
    target_link_libraries(BnsWindow BnsVulkanBackend)
endif()


include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries 
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../window/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../webgpu_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../d3d11_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../metal_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vulkan_backend/include

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

if(USE_VULKAN)
    # VULKAN_INCLUDE is defined in the root CMakeLists.txt
    include_directories(${VULKAN_INCLUDE})
endif() 
