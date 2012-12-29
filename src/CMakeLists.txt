include_directories(${PROJECT_SOURCE_DIR}/deps/include/)
link_directories(${PROJECT_SOURCE_DIR}/deps/libs/)

add_executable(basic_algorithms basis_algorithms.cpp ../data/basis_algorithms.in)
target_link_libraries(basic_algorithms gtest)
set_target_properties(basic_algorithms PROPERTIES DEBUG_POSTFIX "_d")
install(TARGETS basic_algorithms RUNTIME DESTINATION bin/)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/deps/bin/ DESTINATION bin/)



add_executable(ms100_01 ms100_01.cpp ../data/ms100_01.in)
add_executable(ms100_03 ms100_03.cpp ../data/ms100_03.in)
add_executable(ms100_04 ms100_04.cpp ../data/ms100_04.in)
add_executable(ms100_05 ms100_05.cpp ../data/ms100_05.in)
add_executable(ms100_08-3 ms100_08-3.cpp ../data/ms100_08-3.in)
add_executable(ms100_16 ms100_16.cpp ../data/ms100_16.in)
install(TARGETS ms100_01 RUNTIME DESTINATION bin/)
install(TARGETS ms100_03 RUNTIME DESTINATION bin/)
install(TARGETS ms100_04 RUNTIME DESTINATION bin/)
install(TARGETS ms100_05 RUNTIME DESTINATION bin/)
install(TARGETS ms100_08-3 RUNTIME DESTINATION bin/)
install(TARGETS ms100_16 RUNTIME DESTINATION bin/)