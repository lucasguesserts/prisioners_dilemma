project(StrategyLib)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/UtilsLib/include
	${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE UtilsLib)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})

# TODO: Imrpove this.
# The command below specify that the test of
# this library is called StrategyLibTest (${PROJECT_NAME}Test),
# which is true for now. That is, however, a terrible
# way of defining dependency because if anyone changes
# the name of the test, this will break.
setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_coverage EXECUTABLE ${PROJECT_NAME}Test DEPENDENCIES ${PROJECT_NAME}Test)
