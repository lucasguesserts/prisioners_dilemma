CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/pkg)

project(test_install_prisoners_dilemma)

# Import Prisoner's Dilemma
if(NOT DEFINED prisoners_dilemma_ROOT)
	set(prisoners_dilemma_ROOT "$ENV{HOME}/libs/prisoners_dilemma/" CACHE STRING "Location of the 'prisoners_dilemma' package." FORCE)
endif()

set(prisoners_dilemma_DEBUG_MESSAGES TRUE)
if(USE_MODULE)
	find_package(prisoners_dilemma 0.0.0 REQUIRED MODULE)
else()
	find_package(prisoners_dilemma 0.0.0 REQUIRED CONFIG)
endif()

# Add executable

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${prisoners_dilemma_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${prisoners_dilemma_LIBRARIES})

# Extended debug messages
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
	#message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
