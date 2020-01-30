project(PrisonersDilemmaFileLib)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${HDF5_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${HDF5_LIBRARIES} ChampionshipLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})
