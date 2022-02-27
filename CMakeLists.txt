cmake_minimum_required(VERSION 3.22...3.23)
project(envPrint LANGUAGES CXX)

enable_testing()

set(var CMAKE_TEST_MODVAR1)

set(val1 /opt/hello)
set(val2 /opt/goodbye)
set(val3 /opt/farewell)

set(path_sep $<IF:$<BOOL:${WIN32}>,$<SEMICOLON>,:>)

message(STATUS "CMake ${CMAKE_VERSION}")

add_compile_options($<IF:$<BOOL:${MSVC}>,/WX,-Werror>)

add_executable(envPrint main.cpp)
target_compile_features(envPrint PRIVATE cxx_std_11)
target_compile_definitions(envPrint PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

set(names reset path_append list_append string_append multiple_path_append)

add_test(NAME reset COMMAND envPrint ${var} ${val1})
add_test(NAME path_append COMMAND envPrint ${var} ${val1}${path_sep}${val2})
add_test(NAME list_append COMMAND envPrint ${var} ${val1}\;${val2})
add_test(NAME string_append COMMAND envPrint ${var} ${val1}${val2})
add_test(NAME multiple_path_append COMMAND envPrint ${var} ${val1}${path_sep}${val2}${path_sep}${val3})

set_tests_properties(${names} PROPERTIES
ENVIRONMENT "${var}=${val1}"
TIMEOUT 5
)

set_tests_properties(path_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=path_list_append:${val2}"
)

set_tests_properties(list_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=cmake_list_append:${val2}"
)

set_tests_properties(string_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=string_append:${val2}"
)

set_tests_properties(reset PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=reset:${val1}"
)

set_tests_properties(multiple_path_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=path_list_append:${val2};${var}=path_list_append:${val3}"
)
