# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsLoaders STATIC 
    src/FileLoader.cpp 
    src/ImageLoader.cpp 
    src/ImageData.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor
)

