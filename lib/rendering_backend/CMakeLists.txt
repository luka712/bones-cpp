# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsRenderingBackend STATIC 
    src/renderer/Renderer.cpp
    src/buffer_layout/BufferLayoutData.cpp
    )

# INCLUDE DIRECTORIES
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # project libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../texture/include
)

# LINK LIBRARIES
target_link_libraries(BnsRenderingBackend PRIVATE BnsTexture)
