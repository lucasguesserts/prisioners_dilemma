project(StrategyLibTest)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/UtilsLib/include
	${CMAKE_SOURCE_DIR}/StrategyLib/include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Catch2::Catch2
	UtilsLib
	StrategyLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEVELOPER_COMPILE_WARNINGS})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

add_to_coverage_dependency(${PROJECT_NAME})
