# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB COMMON_SOURCES src/*.cpp src/**/*.cpp)

ADD_LIBRARY(BnsCommon STATIC ${COMMON_SOURCES})

include_directories(
    # local 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

