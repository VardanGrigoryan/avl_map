cmake_minimum_required(VERSION 2.6)

project(test)

set(binary_name "randomized_stress_test${binary_ext}")

file(GLOB HEADER_FILES "*.h" "*.hpp")
file(GLOB SOURCE_FILES "*.cpp")

set(HEADER_FILES ${TOP_HEADER_FILES} ${HEADER_FILES})
set(SOURCE_FILES ${TOP_SOURCE_FILES} ${SOURCE_FILES})

set(inc_dir ${root_dir}
	    ${CMAKE_CURRENT_SOURCE_DIR} 
)

include_directories(${inc_dir})

add_executable(${binary_name} ${SOURCE_FILES} ${HEADER_FILES})
set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
