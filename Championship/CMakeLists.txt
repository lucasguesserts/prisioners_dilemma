project(Championship)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE ChampionshipLib PrisonersDilemmaFileLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})
