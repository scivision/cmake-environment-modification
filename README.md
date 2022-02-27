# CMake ENVIRONMENT_MODIFICATION

Demonstrates CMake 3.22 [ENVIRONMENT_MODIFICATION](https://cmake.org/cmake/help/latest/prop_test/ENVIRONMENT_MODIFICATION.html) test property.

```sh
cmake -B build
cmake --build build
ctest --test-dir build -V
```

ENVIRONMENT_MODIFICATION can only handle single path additions.
To add multiple paths, use the syntax of the test "multiple_path_append" like:

```cmake
${var}=path_list_append:${val2};${var}=path_list_append:${val3}
```
