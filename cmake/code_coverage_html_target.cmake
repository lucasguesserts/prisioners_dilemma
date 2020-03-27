# Include this script after including all the subprojects
# because of the dependencies.

if(NOT DEFINED SUB_PROJECTS_ADDED)
	message(FATAL_ERROR "Include the 'gcovr_html' target after including the sub-projects.")
else()
	setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_coverage_html
		EXECUTABLE ${CMAKE_CTEST_COMMAND}
		DEPENDENCIES ${CODE_COVERAGE_DEPENDENCIES}
	)
endif()	
