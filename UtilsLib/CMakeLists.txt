project(UtilsLib)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEFAULT_COMPILE_WARNINGS})

add_coverage(${PROJECT_NAME})
