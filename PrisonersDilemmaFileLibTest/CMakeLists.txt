project(PrisonersDilemmaFileLibTest)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${HDF5_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/UtilsLib/include
	${CMAKE_SOURCE_DIR}/StrategyLib/include
	${CMAKE_SOURCE_DIR}/PlayerLib/include
	${CMAKE_SOURCE_DIR}/ChampionshipLib/include
	${CMAKE_SOURCE_DIR}/PrisonersDilemmaFileLib/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Catch2::Catch2
	stdc++fs
	${HDF5_LIBRARIES}
	UtilsLib
	StrategyLib
	PlayerLib
	ChampionshipLib
	PrisonersDilemmaFileLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEVELOPER_COMPILE_WARNINGS})

target_compile_definitions(${PROJECT_NAME} PRIVATE PUBLIC_TEST_METHODS)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

add_to_coverage_dependency(${PROJECT_NAME})
