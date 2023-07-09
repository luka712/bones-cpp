# About 

Project is imagined as multiplatform project with 4 main renderers (WebGPU as main cross platform solution, Metal as Mac solution, Vulkan as Linux solution and DirectX 12 as Windows solution). In future we will also consider mobile devices.

Projects files are build with CMake, one can use it to generate following solutions:
- makefile project build
- xcode build

# CMAKE SETUP

## PROJECT

### Generate Build Files
cmake . -B build

### Build
cmake --build build

## Run
build/App

## XCODE

### Generate Build Files
run: cmake -G Xcode -H. -Bbuild_xcode

### Build
open: _build_xcode/BonesFramework.xcodeproj
then: navigate to product -> build

### Run
do: Simply run project in xcode

