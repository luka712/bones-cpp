# BnsTexture - TODO: move to backend and managers 


set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(BnsTexture STATIC src/Texture2D.cpp src/TextureManager.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../loaders/include
)

