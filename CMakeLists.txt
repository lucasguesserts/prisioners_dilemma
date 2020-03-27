CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Specified build type")

project(prisoners_dilemma
	VERSION 0.0.0
	DESCRIPTION "Simulations of the Prisoner's Dilemma problem."
	HOMEPAGE_URL "https://github.com/lucasguesserts/prisoners_dilemma"
	LANGUAGES CXX)

# Compiler Setup
include(cmake/check_compiler.cmake)

# User Setup
include(cmake/developer_options.cmake)

# C++ Standard
include(cmake/cxx_standard.cmake)

# Output Directories
include(cmake/main_project_config.cmake)

# External Packages
## TODO: isolate Catch2, make it optional. stdc++fs as well.
include(cmake/Catch2_package.cmake)
include(cmake/HDF5_package.cmake)

# Code Coverage - gcov
include(cmake/code_coverage_setup.cmake)

# Install Setup
include(cmake/install_setup.cmake)

# Libraries
include(cmake/sub_projects.cmake)

# Apps
include(cmake/apps.cmake)

# Code Coverage HTML Targets
include(cmake/code_coverage_html_target.cmake)

# Messages
include(cmake/final_message.cmake)
