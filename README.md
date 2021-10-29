# CMake ENVIRONMENT_MODIFICATION

demo CMake 3.22 ENVIRONMENT_MODIFICATION test property.

CMake 3.22.0-rc1 would [segfault](https://gitlab.kitware.com/cmake/cmake/-/issues/22796).
Cmake 3.22.0-rc2 is
[overwriting instead of appending](https://gitlab.kitware.com/cmake/cmake/-/issues/22819).

These tests fail:

```
PrintVar_path_append
PrintVar_list_append
PrintVar_string_append
```

because we expect for ENVIRONMENT_MODIFICATION test property:

* cmake_list_append: expect /opt/hello;/opt/goodbye
* path_list_append: expect /opt/hello:/opt/goodbye (on Unix-like)
* string_append: exptect /opt/hello/opt/goodbye
