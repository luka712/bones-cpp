function(target_treat_all_warnings_as_errors Target)
	# Treat warnings as errors
	set_target_properties(${Target} PROPERTIES COMPILE_WARNING_AS_ERROR ON)

	# Turn all warnings on
	if (MSVC)
		target_compile_options(${Target} PRIVATE /W4)
	else()
		target_compile_options(${Target} PRIVATE -Wall -Wextra -pedantic)
	endif()
endfunction()


# Function to link libraries to a target
# Target - The target. In our case one of BonesFrameworkExe, BonesFrameworkStatic, BonesFrameworkDynamic
function(target_link_libraries_util Target)

	message(STATUS "Calling target_link_libraries_util(${Target})")
	message(STATUS "Linking libraries to ${Target}")
	message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
	message(STATUS "USE_OPENGL: ${USE_OPENGL}")
	message(STATUS "USE_OPENGLES: ${USE_OPENGLES}")
	message(STATUS "USE_WEBGPU: ${USE_WEBGPU}")
	message(STATUS "USE_D3D11: ${USE_D3D11}")
	message(STATUS "USE_METAL: ${USE_METAL}")
	message(STATUS "USE_VULKAN: ${USE_VULKAN}")

	if(WIN32)
		# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
		if(TARGET SDL2::SDL2main)
			# It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
			target_link_libraries(${Target} PRIVATE SDL2::SDL2main)
		endif()
	endif()


	# Link libraries which are shared between different targets
	target_link_libraries(${Target} PRIVATE SDL2::SDL2 BnsCore BnsWindow BnsSDLWindow BnsLoaders BnsRenderingBackend)
	if(USE_WEBGPU)
		target_link_libraries(${Target} PRIVATE SDL2Extension)
	endif()

	if(APPLE)
		# Link the libraries to the executable (SDL2, Metal, QuartzCore, Foundation) 
		target_link_libraries(${Target} PRIVATE ${APPLE_FWK_FOUNDATION} ${APPLE_FWK_QUARTZ_CORE} ${APPLE_FWK_METAL})
	elseif(WIN32)
		target_link_libraries(${Target} PRIVATE  d3d11 dxgi d3dcompiler)
	endif()

	# glad must be linked if OpenGL is used as it provides headers
	if(USE_OPENGL)
		target_link_libraries(${Target} PRIVATE glad BnsOpenGLBackend)
	endif()
	if(USE_OPENGLES)
		target_link_libraries(${Target} PRIVATE glad_es BnsOpenGLESBackend)
	endif()
	if(USE_WEBGPU)
		target_link_libraries(${Target} PRIVATE webgpu BnsWebGPUBackend)
	endif()
	if(USE_D3D11)
		target_link_libraries(${Target} PRIVATE BnsD3D11Backend)
	endif()
	if(USE_METAL)
		target_link_libraries(${Target} PRIVATE BnsMetalBackend)
	endif()
	if(USE_VULKAN)
		target_link_libraries(${Target} PRIVATE vulkan-1 BnsVulkanBackend)
	endif()
endfunction()


# This will copy all the engine headers to build/headers. Those are from /lib folders.
function(copy_framework_headers)

file(COPY headers DESTINATION ${CMAKE_BINARY_DIR}) # headers should be at one points only in lib
file(COPY lib/core/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/loaders/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/sdl_window/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/window/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/rendering_backend/include DESTINATION ${CMAKE_BINARY_DIR})

# Backends
file(COPY lib/d3d11_backend/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/metal_backend/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/opengl_backend/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/opengles_backend/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/vulkan_backend/include DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib/webgpu_backend/include DESTINATION ${CMAKE_BINARY_DIR})

endfunction()

# The vendor headers. These won't be necessary in future.
function(copy_vendor_headers)

file(COPY vendor/glad/glad DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY vendor/glad/KHR DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/glad_es/glad DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY vendor/glad_es/KHR DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/Metal DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/SDL2 DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/SDL2Extension DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/stb DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/tinyxml2 DESTINATION ${CMAKE_BINARY_DIR}/include)

file(COPY vendor/webgpu/include DESTINATION ${CMAKE_BINARY_DIR}) 
file(COPY build/_deps/dawn-src/include DESTINATION ${CMAKE_BINARY_DIR}/include) 

endfunction()