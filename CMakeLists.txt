cmake_minimum_required(VERSION 3.16)
project(cad-dwg LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(caddwg src/version.c)
target_include_directories(caddwg PUBLIC include)

add_executable(version_test tests/version_test.c)
target_link_libraries(version_test PRIVATE caddwg)

enable_testing()
add_test(NAME version COMMAND version_test)
