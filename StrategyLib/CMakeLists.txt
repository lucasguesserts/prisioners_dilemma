project(StrategyLib)

set(INCLUDE_DEPENDENCIES UtilsLib ${PROJECT_NAME})
set(LINK_DEPENDENCIES UtilsLib)

foreach(INCLUDE_DEPENDENCY in ${INCLUDE_DEPENDENCIES})
	include_directories(${CMAKE_SOURCE_DIR}/${INCLUDE_DEPENDENCY}/include)
endforeach(INCLUDE_DEPENDENCY)

file(GLOB ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.hpp)
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} ${LINK_DEPENDENCIES})
