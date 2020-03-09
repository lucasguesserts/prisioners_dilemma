CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_CXX_COMPILER "g++")

project(prisoners_dilemma
	VERSION 0.0.0
	DESCRIPTION "Simulations of the Prisoner's Dilemma problem."
	HOMEPAGE_URL "https://github.com/lucasguesserts/prisoners_dilemma"
	LANGUAGES CXX)

# Check compiler
set(GXX_MINIMUM_VERSION 7.4.0)
set(REQUIRED_COMPILER "GNU")
if (NOT CMAKE_CXX_COMPILER_ID STREQUAL ${REQUIRED_COMPILER})
	message(FATAL_ERROR "The compiler required is ${REQUIRED_COMPILER}")
endif()
if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 7.4.0)
	message(FATAL_ERROR "g++ version required to be at least 7.4.0")
endif()

# Compiler Setup
set(CMAKE_BUILD_TYPE Debug)
set(DEFAULT_COMPILE_WARNINGS -fmax-errors=1 -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wnull-dereference -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wunsafe-loop-optimizations -Wundef -Wunused-macros -Wcast-qual -Wcast-align -Wzero-as-null-pointer-constant -Wdangling-else -Wuseless-cast -Wlogical-op -Wmissing-declarations -Winline -Wvla -Wdisabled-optimization -Wconversion -Wsign-conversion -Wshadow=local)
if (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 8.3.0)
	set(DEFAULT_COMPILE_WARNINGS ${DEFAULT_COMPILE_WARNINGS} -Wcast-align=strict -Wextra-semi)
endif()

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

# External Packages
set(HDF5_VERSION "1.10.3")
set(HDF5_ROOT "$ENV{HOME}/libs/hdf5-${HDF5_VERSION}/")
find_package(HDF5 ${HDF5_VERSION} EXACT REQUIRED COMPONENTS CXX)                             

# Testing
enable_testing()

# Libraries
add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(StrategyLib)
add_subdirectory(StrategyLibTest)
add_subdirectory(PlayerLib)
add_subdirectory(PlayerLibTest)
add_subdirectory(ChampionshipLib)
add_subdirectory(ChampionshipLibTest)
add_subdirectory(PrisonersDilemmaFileLib)
add_subdirectory(PrisonersDilemmaFileLibTest)

# Apps
add_subdirectory(Championship)

# Messages
message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version		 = ${PROJECT_VERSION}")
message("Description      = ${PROJECT_DESCRIPTION}")
message("Homepage         = ${PROJECT_HOMEPAGE_URL}")
message("C++ compiler	 = ${CMAKE_CXX_COMPILER}")
message("Compiler flags	 = ${CMAKE_CXX_FLAGS}")
message("Compiler version = ${CMAKE_CXX_COMPILER_VERSION}")
if(HDF5_FOUND)                                                     
	message("HDF5 version     = ${HDF5_VERSION}")
else()                                                          
	message("HDF5 not found")
endif()                                                                                                                                            
message("\n")

