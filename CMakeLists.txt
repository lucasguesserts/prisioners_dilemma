CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -ansi -pedantic")

project(prisioner_dilemma)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

enable_testing()

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version		= ${VERSION}")
message("C++ compiler	= ${CMAKE_CXX_COMPILER}")
message("Compiler flags	= ${CMAKE_CXX_FLAGS}")
message("\n")

add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(StrategyLib)
add_subdirectory(StrategyLibTest)
add_subdirectory(PlayerLib)
add_subdirectory(PlayerLibTest)
