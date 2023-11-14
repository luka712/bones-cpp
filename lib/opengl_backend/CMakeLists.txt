# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB OpenGL_BACKEND_SOURCES src/*.cpp src/**/*.cpp)

ADD_LIBRARY(BnsOpenGLBackend STATIC ${OpenGL_BACKEND_SOURCES})

# USE_WEBGPU is defined in the root CMakeLists.txt
target_compile_options(BnsOpenGLBackend PRIVATE 
    -DUSE_OPENGL=${USE_OPENGL}
    -DDEBUG_BREAKPOINT_ENABLED=${DEBUG_BREAKPOINT_ENABLED}
    -DLOGGING_ENABLED=${LOGGING_ENABLED}
)

target_link_libraries(BnsOpenGLBackend PRIVATE Glad)

include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../rendering_backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../window/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include

    # vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad

    # system 

)

