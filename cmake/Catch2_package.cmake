if(NOT DEFINED Catch2_ROOT)
	set(Catch2_ROOT "$ENV{HOME}/libs/catch2/lib/cmake/Catch2/")
endif()
find_package(Catch2 "2.11.1" REQUIRED)
