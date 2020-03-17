project(PrisonersDilemmaFileLib)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${HDF5_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/UtilsLib/include
	${CMAKE_SOURCE_DIR}/StrategyLib/include
	${CMAKE_SOURCE_DIR}/PlayerLib/include
	${CMAKE_SOURCE_DIR}/ChampionshipLib/include
	${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${HDF5_LIBRARIES}
	UtilsLib
	StrategyLib
	PlayerLib
	ChampionshipLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})

add_coverage(${PROJECT_NAME})
