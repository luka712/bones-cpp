# BnsLoaders - various loaders for BNS files

set(CMAKE_CXX_STANDARD 17)

file(GLOB VULKAN_BACKEND_SOURCES src/*.cpp src/**/*.cpp)

ADD_LIBRARY(BnsVulkanBackend STATIC ${VULKAN_BACKEND_SOURCES})

# USE_VULKAN is defined in the root CMakeLists.txt
target_compile_options(BnsVulkanBackend PRIVATE -DUSE_VULKAN=${USE_VULKAN} 
-DDEBUG=${DEBUG}
-DLOGGING_ENABLED=${LOGGING_ENABLED}
-DEBUG_BREAKPOINT_ENABLED=${DEBUG_BREAKPOINT_ENABLED})

# Direcotry of the Vulkan SDK Libs. 
# Set in the root CMakeLists.txt
link_directories(${VULKAN_LIB_DIR}) 

target_link_libraries(BnsVulkanBackend PRIVATE vulkan-1)

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

    # system/machine specific
    ${VULKAN_INCLUDE}
)

