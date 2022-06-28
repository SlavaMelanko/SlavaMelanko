cmake_minimum_required(VERSION 3.16.0)

project(cpp20-coro
    VERSION 0.0.1
    DESCRIPTION "My First Coroutines"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_TESTS "Enable unit tests" ON)

include(cmake/Conan.cmake)
run_conan()

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    PRIVATE
        include/Awaiter.h
        include/Coroutine.h
        include/Promise.h
        include/Task.h
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include
)

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()
