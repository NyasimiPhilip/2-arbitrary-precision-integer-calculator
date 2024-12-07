# Create test executables
add_executable(test_arbitraryint test_arbitraryint.c)
target_link_libraries(test_arbitraryint calculator_lib)

add_executable(test_base_conversion test_base_conversion.c)
target_link_libraries(test_base_conversion calculator_lib)

add_executable(test_operations test_operations.c)
target_link_libraries(test_operations calculator_lib)

add_executable(test_main test_main.c)
target_link_libraries(test_main calculator_lib)

add_executable(test_parser test_parser.c)
target_link_libraries(test_parser calculator_lib)

# Add tests
add_test(NAME test_arbitraryint COMMAND test_arbitraryint)
add_test(NAME test_base_conversion COMMAND test_base_conversion)
add_test(NAME test_operations COMMAND test_operations)
add_test(NAME test_main COMMAND test_main)
add_test(NAME test_parser COMMAND test_parser)