cmake_minimum_required(VERSION 3.0)
set(CMAKE_VERBOSE_MAKEFILE True)

project(KBRogue)

find_package(Curses REQUIRED)

set(SOURCES_DIR src)
aux_source_directory(${PROJECT_SOURCE_DIR}/${SOURCES_DIR} SOURCES)

add_executable(KBRogue ${SOURCES})
target_include_directories(KBRogue PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_include_directories(KBRogue PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(KBRogue ${CURSES_LIBRARIES})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set_target_properties(KBRogue PROPERTIES OUTPUT_NAME KBRogue-debug)
	target_compile_definitions(KBRogue PRIVATE DEBUG)
	target_compile_options(KBRogue PRIVATE -Wall -Wextra -ansi -pedantic -pthread -O0 -std=c++14)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	target_compile_definitions(KBRogue PRIVATE RELEASE)
	target_compile_options(KBRogue PRIVATE -Wall -Wextra -ansi -pedantic -pthread -O3 -std=c++14)
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(KBROGUE_VERSION_TYPE "\"develop\"")
set(KBROGUE_VERSION_MAJOR 0)
set(KBROGUE_VERSION_MINOR 0)
configure_file("${PROJECT_SOURCE_DIR}/include/KBRogueConfig.h.in" "${PROJECT_SOURCE_DIR}/include/KBRogueConfig.h")
configure_file("${PROJECT_SOURCE_DIR}/include/curses_include.h.in" "${PROJECT_SOURCE_DIR}/include/curses_include.h")
