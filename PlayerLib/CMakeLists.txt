project(PlayerLib)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/UtilsLib/include
	${CMAKE_SOURCE_DIR}/StrategyLib/include
	${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
	UtilsLib
	StrategyLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})

add_coverage(${PROJECT_NAME})
