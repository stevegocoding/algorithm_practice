add_executable(ms100_01 ms100_01.cpp ../data/ms100_01.in)
add_executable(ms100_16 ms100_16.cpp ../data/ms100_16.in)
install(TARGETS ms100_01 RUNTIME DESTINATION bin/)
install(TARGETS ms100_16 RUNTIME DESTINATION bin/)