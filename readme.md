# About 

Project is imagined as multiplatform project with 4 main renderers for learning purposes
- WebGPU, Vulkan, OpenGL, OpenGLES as main cross platform solutions
- Metal as Mac solution 
- DirectX12/DirectX11 as Windows solution
Note: In future it will also consider mobile devices.

Projects files are build with CMake, one can use it to generate following solutions:
- makefile project build
- xcode build

# CMAKE SETUP

## PROJECT

- lib - all game dependices go to lib folder. Engine is broken into smaller parts and parts of engine are in lib folder

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

### GOALS 0.1 
- DirectX11/Metal/WebGPU/OpenGL45/OpenGLES initial game. Make sure it runs on Win/Mac/Linux with WebGPU, Metal, DirectX, OpenGL, OpenGLES
### GOALS 0.2
- Emscripten go further with game using engine. Make sure it's compiled for web with WebGPU/OpenGLES using Emscripten.

### COMPILE SHADERS

#### VULKAN

##### Windows
To compile shader on Windows run ```glslc.exe -fshader-stage=<{stage}> {inputShader} -o {outputShader}``` for example ```D:/VulkanSDK/1.3.268.0/Bin/glslc.exe -fshader-stage<vert> shader.glsl -o vert.spv```
Of course make sure that path corresponds to your system.


# Dependencies
TODO: 
- create DX12/Vulkan renderer similar to DX11Renderer/OpenGL/OpenGLES (finish sprite renderer opengl, pay attention to buffer usages)
- change directx 3d hard coded folders similar to vulkan
- make sure that project can use multiple renderer, recompile and switch

- create guards for renderers

- Break project into smaller parts, start with loaders! 

- FORWARD_2D_NUM_OF_POINT_LIGHTS make sure it's passed to shader as well
- make sure to work correctly with 1 point light 
- Check point lights
- Optimize sprite renderers in endframe
- Think about and document post process pipeline
- All utils to utils folder
- add scene test cases