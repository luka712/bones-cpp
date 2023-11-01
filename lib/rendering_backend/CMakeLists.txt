# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsRenderingBackend STATIC src/buffer-layout/BufferLayoutData.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
)

