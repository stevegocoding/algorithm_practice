cmake_minimum_required(VERSION 2.8)
project(algorithm_practice)

if( MSVC ) # VS2012 doesn't support correctly the tuples yet
	add_definitions( /D _VARIADIC_MAX=10 )
endif()

add_subdirectory(data)
add_subdirectory(src)
