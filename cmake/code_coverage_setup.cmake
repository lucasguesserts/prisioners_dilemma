# Code Coverage - gcov
# Based on <https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake> 
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CodeCoverage.cmake)

#mark_as_advanced(FORCE GCOVR_PATH GENHTML_PATH LCOV_PATH)

set(GCOV_FLAGS "--coverage")
set(GCOV_LIBRARIES "gcov")

macro(add_coverage NAME)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${GCOV_LIBRARIES})
	target_compile_options(${PROJECT_NAME} PRIVATE ${GCOV_FLAGS})
endmacro()

# Use this macro in all projects which
# define a test executable
macro(add_to_coverage_dependency NAME)
	set(CODE_COVERAGE_DEPENDENCIES "${CODE_COVERAGE_DEPENDENCIES};${NAME}" PARENT_SCOPE)
endmacro()
