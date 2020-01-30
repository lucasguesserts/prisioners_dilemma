project(StrategyLibTest)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE StrategyLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
