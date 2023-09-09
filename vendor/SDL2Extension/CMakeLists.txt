# This is only meant to be included as a subdirectory in another project.
# It assumes that targets 'sdl' and 'webgpu' exist.
# Loot at examples/CMakeLists.txt to see how to use it in a project.

# The SDL2WebGPU target
add_library(SDL2Extension STATIC SDL2_Extension.c)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_include_directories(SDL2Extension PUBLIC .)
target_link_libraries(SDL2Extension PUBLIC ${SDL2_LIBRARIES} webgpu)

if (APPLE)
  target_compile_options(SDL2Extension PRIVATE -x objective-c)
  target_link_libraries( SDL2Extension PRIVATE "-framework Cocoa" "-framework CoreVideo" "-framework IOKit" "-framework QuartzCore")
endif ()

