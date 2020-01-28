project(Championship)

include_directories("${HDF5_INCLUDE_DIRS}/")
set(INCLUDE_DEPENDENCIES UtilsLib StrategyLib PlayerLib ChampionshipLib PrisonersDilemmaFileLib ${PROJECT_NAME})
set(LINK_DEPENDENCIES ${HDF5_LIBRARIES} UtilsLib StrategyLib PlayerLib ChampionshipLib PrisonersDilemmaFileLib)

foreach(INCLUDE_DEPENDENCY in ${INCLUDE_DEPENDENCIES})
	include_directories(${CMAKE_SOURCE_DIR}/${INCLUDE_DEPENDENCY}/include)
endforeach(INCLUDE_DEPENDENCY)

file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} ${LINK_DEPENDENCIES})
