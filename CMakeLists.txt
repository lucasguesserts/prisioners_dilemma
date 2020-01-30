CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(DEFAULT_COMPILE_WARNINGS -Og -Wall -Wextra -ansi -Wpedantic -pedantic-errors -Wnull-dereference -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wduplicated-branches -Wduplicated-cond)

project(prisoners_dilemma)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

find_package(HDF5 REQUIRED COMPONENTS CXX)                             

enable_testing()

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version		= ${VERSION}")
message("C++ compiler	= ${CMAKE_CXX_COMPILER}")
message("Compiler flags	= ${CMAKE_CXX_FLAGS}")
if(HDF5_FOUND)                                                     
	message("HDF5 version    = ${HDF5_VERSION}")                
else()                                                          
	message("HDF5 not found")                            
endif()                                                                                                                                            
message("\n")

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
