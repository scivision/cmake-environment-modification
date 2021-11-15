cmake_minimum_required(VERSION 3.22)
project(envPrint LANGUAGES C)

enable_testing()

set(var CMAKE_TEST_MODVAR1)

set(val1 /opt/hello)
set(val2 /opt/goodbye)

if(WIN32)
  set(path_sep "\;")
else()
  set(path_sep ":")
endif()

message(STATUS "CMake ${CMAKE_VERSION}")

add_compile_options(
$<$<C_COMPILER_ID:Clang,GNU>:-Werror-implicit-function-declaration>
$<$<C_COMPILER_ID:IntelLLVM>:-Werror>
$<$<C_COMPILER_ID:Intel>:$<IF:$<BOOL:${WIN32}>,/WX,-Werror>>
)
# MSVC and Intel Windows icl don't throw error for implicit function

add_executable(envPrint main.c)
target_compile_definitions(envPrint PRIVATE _CRT_SECURE_NO_WARNINGS)

add_test(NAME PrintVar_reset COMMAND envPrint ${var})
add_test(NAME PrintVar_path_append COMMAND envPrint ${var})
add_test(NAME PrintVar_list_append COMMAND envPrint ${var})
add_test(NAME PrintVar_string_append COMMAND envPrint ${var})

set_tests_properties(PrintVar_reset PrintVar_path_append PrintVar_list_append PrintVar_string_append PROPERTIES
ENVIRONMENT "${var}=${val1}"
TIMEOUT 5
)

set_tests_properties(PrintVar_path_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=path_list_append:${val2}"
PASS_REGULAR_EXPRESSION "^${val1}${path_sep}${val2}"
)

set_tests_properties(PrintVar_list_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=cmake_list_append:${val2}"
PASS_REGULAR_EXPRESSION "^${val1}\;${val2}"
)

set_tests_properties(PrintVar_string_append PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=string_append:${val2}"
PASS_REGULAR_EXPRESSION "^${val1}${val2}"
)

set_tests_properties(PrintVar_reset PROPERTIES
ENVIRONMENT_MODIFICATION "${var}=reset:${val1}"
PASS_REGULAR_EXPRESSION "^${val1}"
)
