project(UtilsLib)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION 0.0.0
	SOVERSION 0
)

target_include_directories(
	${PROJECT_NAME} PUBLIC
	$<INSTALL_INTERFACE:include/>
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Catch2::Catch2
	stdc++fs
)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEVELOPER_COMPILE_WARNINGS})

add_coverage(${PROJECT_NAME})

install_project()
