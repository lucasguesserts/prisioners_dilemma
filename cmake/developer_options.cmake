# TODO: add some sort of documentation / esplanation
# of what this file is.

# Options
option(BUILD_SHARED_LIBS               "If ON, build shared libs. Build static libs otherwise."                        ON)
option(DEVELOPER_USE_ALL_WARNINGS      "Whether to use all the warnings defined by the developer or not."              ON)
option(DEVELOPER_SINGLE_ERROR          "Whether to cancel the compilation at the first error or not (-fmax-errors=1)." ON)
option(DEVELOPER_WARNING_CAUSES_ERROR  "Whether warnings cause error or not (-Werror)."                                ON)
option(DEVELOPER_SHOW_COMPILE_WARNINGS "Whether to display enabled compile warnings or not."                           ON)

# Developer Options

## Compile Warnings
unset(DEVELOPER_COMPILE_WARNINGS)
if(DEVELOPER_SINGLE_ERROR)
	set(DEVELOPER_COMPILE_WARNINGS ${DEVELOPER_COMPILE_WARNINGS} -fmax-errors=1)
endif()
if(DEVELOPER_WARNING_CAUSES_ERROR)
	set(DEVELOPER_COMPILE_WARNINGS ${DEVELOPER_COMPILE_WARNINGS} -Werror)
endif()
if(DEVELOPER_USE_ALL_WARNINGS)
	set(DEVELOPER_COMPILE_WARNINGS ${DEVELOPER_COMPILE_WARNINGS} -Wall -Wextra -Wpedantic -pedantic-errors -Wnull-dereference -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wunsafe-loop-optimizations -Wundef -Wunused-macros -Wcast-qual -Wcast-align -Wzero-as-null-pointer-constant -Wdangling-else -Wuseless-cast -Wlogical-op -Wmissing-declarations -Winline -Wvla -Wdisabled-optimization -Wconversion -Wsign-conversion -Wshadow=local)
	if (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 8.3.0)
		set(DEVELOPER_COMPILE_WARNINGS ${DEVELOPER_COMPILE_WARNINGS} -Wcast-align=strict -Wextra-semi)
	endif()
endif()
