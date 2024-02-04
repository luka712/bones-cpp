# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB RENDERING_BACKEND_SOURCES src/*.cpp src/**/*.cpp)

ADD_LIBRARY(BnsRenderingBackend STATIC ${RENDERING_BACKEND_SOURCES})

# INCLUDE DIRECTORIES
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
)

# LINK LIBRARIES
target_link_libraries(BnsRenderingBackend PRIVATE BnsLoaders)
