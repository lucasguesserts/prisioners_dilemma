#[===================================================================[.markdown:
# @CMAKE_PROJECT_NAME@ - find_package Module mode - Findprisoners_dilemma

Find prisoners_dilemma include dirs and libraries.

## Invoking

Use this module by invoking find_package with the form
(as documented on the
[cmake find_package documentation page](https://cmake.org/cmake/help/latest/command/find_package.html)):

```
find_package(
	prisoners_dilemma     # Package name
	[version] [EXACT]  # Minimum or EXACT version e.g. major[.minor[.patch[.tweak]]]
	[REQUIRED]         # Fail with error if prisoners_dilemma is not found
	[MODULE]           # If specified, disable the Cofig mode
)
```

For debug messages, set the variable `prisoners_dilemma_DEBUG_MESSAGES` to `TRUE`.

The command above has two modes by which it searches for packages:
“Module” mode (preferred by CMake) and “Config” mode.

### Module mode:

CMake will look for this file (so please add its path to the
CMake variable `CMAKE_MODULE_PATH`) and call it.

Set the variable `prisoners_dilemma_ROOT` to the location where
the package was installed.

According to the CMake documentation, this is its preferred
mode. If CMake fails to find this file, it will fallback to
the Config mode. Disable the fallback by specifying `MODULE`
in the `find_package` call.

### Config mode:

The CMake `find_package` command will look for a file named
`prisoners_dilemmaConfig.cmake` or `prisoners_dilemma-config.cmake`.
Once found, CMake will load it.
If the library was not installed in a default directory
(e.g. system directory) please set the CMake variable
`prisoners_dilemma_ROOT` to the directory where it
can find one of the above configuration files.

The project prisoners_dilemma is configured to be used
and installed using CMake. Therefore, once correctly installed,
the config files above will be available in the top
level installation directory (e.g. the path to
which `CMAKE_INSTALL_PREFIX` was set when the project
was installed).

Set the CMake variable `CMAKE_FIND_PACKAGE_PREFER_CONFIG`
to `TRUE` in order to use this as the preferred find method.
Otherwise, CMake will fallback to Config mode only if the
Module mode fails. That fallback behavior is disabled if one
specifies `MODULE` in the `find_package` call.

## Package Variables

Once called, the following variable will be defined:

	`prisoners_dilemma_FOUND`            - True if headers and libraries were found.
	                                    If the files were not found, then the variables below
	                                    below will not be set.
	`prisoners_dilemma_INCLUDE_DIRS`     - prisoners_dilemma include directories.
	`prisoners_dilemma_LIBRARIES`        - prisoners_dilemma component libraries to be linked.
	`prisoners_dilemma_VERSION`          - prisoners_dilemma version number in x.y.z format.
	`prisoners_dilemma_VERSION_MAJOR`    - prisoners_dilemma major version number (X in X.y.z).
	`prisoners_dilemma_VERSION_MINOR`    - prisoners_dilemma minor version number (Y in x.Y.z).
	`prisoners_dilemma_VERSION_PATCH`    - prisoners_dilemma subminor version number (Z in x.y.Z).

#]===================================================================]

# TODO: define the search deppending on the version
# in any quite smart way.

# Setup
set(PACKAGE_NAME prisoners_dilemma)
set(${PACKAGE_NAME}_LIBRARY_COMPONENTS
	UtilsLib
	StrategyLib
	PlayerLib
	ChampionshipLib
	PrisonersDilemmaFileLib
)
set(${PACKAGE_NAME}_INCLUDE_FILE Strategy.hpp)

# Find libraries
foreach(LIBRARY_NAME ${${PACKAGE_NAME}_LIBRARY_COMPONENTS})
	find_library(
		${PACKAGE_NAME}_${LIBRARY_NAME}
		${LIBRARY_NAME}
		HINTS ${prisoners_dilemma_ROOT}/lib
		DOC "The file that corresponds to the library ${LIBRARY_NAME}."
	)
	mark_as_advanced(${PACKAGE_NAME}_${LIBRARY_NAME})
	list(APPEND ${PACKAGE_NAME}_LIBRARIES ${${PACKAGE_NAME}_${LIBRARY_NAME}})
endforeach()
set(${PACKAGE_NAME}_LIBRARIES ${${PACKAGE_NAME}_LIBRARIES} CACHE STRING "${PACKAGE_NAME} libraries.")

# Find include path
find_path(
	${PACKAGE_NAME}_INCLUDE_DIRS
	${${PACKAGE_NAME}_INCLUDE_FILE}
	HINTS include
	DOC "The path to the directory that contains the package header file $${${PACKAGE_NAME}_INCLUDE_FILE}."
)

# External Dependencies
include(CMakeFindDependencyMacro)
## Filesystem
list(APPEND ${PACKAGE_NAME}_LIBRARIES stdc++fs)
## Catch2
if(NOT DEFINED Catch2_ROOT)
	set(Catch2_ROOT "$ENV{HOME}/libs/catch2/lib/cmake/Catch2/")
endif()
find_dependency(Catch2 2.11.1 REQUIRED)
list(APPEND ${PACKAGE_NAME}_LIBRARIES Catch2::Catch2)
## HDF5
if(NOT DEFINED HDF5_ROOT)
	set(HDF5_ROOT "$ENV{HOME}/libs/hdf5/")
endif()
find_dependency(HDF5 1.10.3 REQUIRED COMPONENTS CXX)
list(APPEND ${PACKAGE_NAME}_INCLUDE_DIRS ${HDF5_INCLUDE_DIRS})
list(APPEND ${PACKAGE_NAME}_LIBRARIES ${HDF5_LIBRARIES})

# Version
include(${prisoners_dilemma_ROOT}/share/cmake/${PACKAGE_NAME}/version.cmake)

# Debug messages
if(prisoners_dilemma_DEBUG_MESSAGES)
	message("")
	message("Module mode selected for package '${PACKAGE_NAME}'.")
	message("${PACKAGE_NAME}_ROOT = ${${PACKAGE_NAME}_ROOT}")
	message("${PACKAGE_NAME}_LIBRARY_COMPONENTS = ${${PACKAGE_NAME}_LIBRARY_COMPONENTS}")
	message("${PACKAGE_NAME}_INCLUDE_FILE = ${${PACKAGE_NAME}_INCLUDE_FILE}")
	message("${PACKAGE_NAME}_VERSION = ${${PACKAGE_NAME}_VERSION}")
	message("${PACKAGE_NAME}_INCLUDE_DIRS = ${${PACKAGE_NAME}_INCLUDE_DIRS}")
	message("${PACKAGE_NAME}_LIBRARIES = ${${PACKAGE_NAME}_LIBRARIES}")
	message("")
endif()

set(${PACKAGE_NAME}_LIBRARIES ${${PACKAGE_NAME}_LIBRARIES} CACHE STRING "${PACKAGE_NAME} libraries.")

# Check if found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
	${PACKAGE_NAME}
	REQUIRED_VARS ${PACKAGE_NAME}_LIBRARIES ${PACKAGE_NAME}_INCLUDE_DIRS
	VERSION_VAR ${PACKAGE_NAME}_VERSION
)

# Final
unset(PACKAGE_NAME)
