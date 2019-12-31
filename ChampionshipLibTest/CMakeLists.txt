project(ChampionshipLibTest)

set(INCLUDE_DEPENDENCIES UtilsLib StrategyLib PlayerLib ChampionshipLib ${PROJECT_NAME})
set(LINK_DEPENDENCIES StrategyLib PlayerLib ChampionshipLib)

foreach(INCLUDE_DEPENDENCY in ${INCLUDE_DEPENDENCIES})
	include_directories(${CMAKE_SOURCE_DIR}/${INCLUDE_DEPENDENCY}/include)
endforeach(INCLUDE_DEPENDENCY)

file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} ${LINK_DEPENDENCIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
