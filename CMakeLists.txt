cmake_minimum_required(VERSION 2.6)

project(map)

set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/bin)

if("${ARC}" STREQUAL "x64")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        # ***NOTE: -m32 flag dosen't work on Raspbian 4.9.3-14 with gcc version 4.9.3.
        #          *In order to build it for 32 bit platform on the other unix system one should uncomment the 
        #          *line below and comment the line above from given note.
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -std=c++11")
endif()

if(DEFINED OS)
	if("${OS}" STREQUAL "_UNIX_")
                # Switching off nrvo in case of debug build and adding debug symbols.
                if("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
                        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-elide-constructors -ggdb")
                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -ggdb")
                endif()
		add_definitions(-D_UNIX_)
		set(binary_ext "")
	elseif()
		set(binary_ext "exe")
	endif()
endif()

if(DEFINED _LIMIT_)
	add_definitions(-D_LIMIT_=${_LIMIT_})
endif()

file(GLOB TOP_HEADER_FILES "*.h" "*.hpp")
file(GLOB TOP_SOURCE_FILES "*.cpp")

add_subdirectory(test)
