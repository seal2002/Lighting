cmake_minimum_required (VERSION 3.6)
project (Lighting)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

set(LIBS glfw3 opengl32)

# first create relevant static libraries requried for other projects
add_library(STB_IMAGE "src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

set(DEMO
	1.colors
	2.1.basic_lighting_diffuse
	2.2.basic_lighting_specular
	2.3.basic_lighting_Ex1
	2.4.basic_lighting_Ex3
	2.5.basic_lighting_Ex4
	3.1.materials
	3.2.materials_light
	3.3.materials_Ex1
	4.1.lighting_maps_diffusemap
	4.2.lighting_maps_specularmap
	4.3.lighting_maps_Ex3
	4.4.lighting_maps_Ex4
	5.1.light_casters_directional
	5.2.light_casters_point
	5.3.light_casters_spot
	5.4.light_casters_spot_soft
	6.multiple_lights
)

# then create a project file per tutorial
foreach(DEMO ${DEMO})
		file(GLOB SOURCE
            "src/${DEMO}/*.cpp"
        )
		set(NAME "${DEMO}")
		# add the executable
		add_executable (${NAME} ${SOURCE})
		target_link_libraries (${NAME} ${LIBS})
endforeach(DEMO)