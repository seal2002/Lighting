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
	2.1.basiclightingdiffuse
	2.2.basiclightingspecular
	2.3.basiclightingEx1
	2.4.basiclightingEx3
	2.5.basiclightingEx4
	3.1.materials
	3.2.materialslight
	3.3.materialsEx1
	4.1.lightingmapsdiffusemap
	4.2.lightingmapsspecularmap
	4.3.lightingmapsEx3
	4.4.lightingmapsEx4
	5.1.lightcastersdirectional
	5.2.lightcasterspoint
	5.3.lightcastersspot
	5.4.lightcastersspotsoft
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