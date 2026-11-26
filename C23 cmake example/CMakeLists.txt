cmake_minimum_required(VERSION 4.5)

project(hello_world_c LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Only needed if this targeting MSVC or clang-cl on Windows.
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_executable(hello_world_c
    src/main.c
)

target_include_directories(hello_world_c PRIVATE include)

# GCC style warnings: supported by GCC and Clang not MSVC
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(hello_world_c PRIVATE
        -Wall
        #-Werror
        -Wextra
        -Wpedantic
        -Wshadow
        -Wcast-align
        -Wconversion
        -Wdouble-promotion
        -Wformat=2
        -Wnull-dereference
    )
endif()

set_target_properties(hello_world_c PROPERTIES
    OUTPUT_NAME "Hello-world-c"
)

install(TARGETS hello_world_c
    RUNTIME DESTINATION bin
)