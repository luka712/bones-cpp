# About 

Project is imagined as multiplatform project with 4 main renderers for learning purposes
- WebGPU, Vulkan as main cross platform solutions
- Metal as Mac solution 
- DirectX 12 as Windows solution
Note: In future it will also consider mobile devices.

Projects files are build with CMake, one can use it to generate following solutions:
- makefile project build
- xcode build

# CMAKE SETUP

## PROJECT

### Generate Build Files
cmake . -B build

### Build

#### MAKE - the makefile build
cmake --build build

#### XCODE - the build for xcode
cmake -G Xcode -H. -Bbuild_xcode

## Run
build/App

### Generate Build Files
run: cmake -G Xcode -H. -Bbuild_xcode

### Build
open: _build_xcode/BonesFramework.xcodeproj
then: navigate to product -> build

### Run
do: Simply run project in xcode

# Dependencies
TODO: 
- FORWARD_2D_NUM_OF_POINT_LIGHTS make sure it's passed to shader as well
- make sure to work correctly with 1 point light 
- Check point lights
- Optimize sprite renderers in endframe
- Think about and document post process pipeline
- All utils to utils folder
- add scene test cases