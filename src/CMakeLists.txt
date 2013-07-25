include_directories(${PROJECT_SOURCE_DIR}/deps/include/)
link_directories(${PROJECT_SOURCE_DIR}/deps/libs/)

#add_executable(interview_problems 
#	basic_algorithms.cpp 
#	interview_problems.cpp
#	cracking_problems.cpp
#	utils.cpp
#	utils.h) 

#target_link_libraries(interview_problems gtest)
#set_target_properties(interview_problems PROPERTIES DEBUG_POSTFIX "_d")

#install(TARGETS interview_problems RUNTIME DESTINATION bin/) 

add_executable(leetcode_solutions
    leetcode_solutions.cpp
    utils.cpp
    utils.h)

install(TARGETS leetcode_solutions RUNTIME DESTINATION bin/) 

# install GTEST dll to bin directory
install(DIRECTORY ${PROJECT_SOURCE_DIR}/deps/bin/ DESTINATION bin/)
