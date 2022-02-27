cmake_minimum_required(VERSION 3.22...3.23)
project(envPrint LANGUAGES C)

enable_testing()

set(var CMAKE_TEST_MODVAR1)

set(val1 /opt/hello)
set(val2 /opt/goodbye)

set(path_sep $<IF:$<BOOL:${WIN32}>,$<SEMICOLON>,:>)

message(STATUS "CMake ${CMAKE_VERSION}")

add_compile_options(
$<$<C_COMPILER_ID:Clang,GNU>:-Werror-implicit-function-declaration>
$<$<C_COMPILER_ID:IntelLLVM>:-Werror>
$<$<C_COMPILER_ID:Intel>:$<IF:$<BOOL:${WIN32}>,/WX,-Werror>>
)
# MSVC and Intel Windows icl don't throw error for implicit function

add_executable(envPrint main.c)
target_compile_definitions(envPrint PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

add_test(NAME reset COMMAND envPrint ${var})
add_test(NAME path_append COMMAND envPrint ${var})
add_test(NAME list_append COMMAND envPrint ${var})
add_test(NAME string_append COMMAND envPrint ${var})

set_tests_properties(reset path_append list_append string_append PROPERTIES
ENVIRONMENT "${var}=${val1}"
TIMEOUT 5
)

set_tests_properties(path_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=path_list_append:${val2}"
PASS_REGULAR_EXPRESSION "^${val1}${path_sep}${val2}"
)

set_tests_properties(list_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=cmake_list_append:${val2}"
PASS_REGULAR_EXPRESSION "^${val1}\;${val2}"
)

set_tests_properties(string_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=string_append:${val2}"
PASS_REGULAR_EXPRESSION "^${val1}${val2}"
)

set_tests_properties(reset PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=reset:${val1}"
PASS_REGULAR_EXPRESSION "^${val1}"
)
