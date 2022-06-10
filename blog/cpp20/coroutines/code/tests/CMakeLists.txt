cmake_minimum_required(VERSION 3.16.0)

project(cpp20-coro-tests)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        GTest::gtest

        cpp20-coro
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /ignore:4099 # warning LNK4099: PDB '.pdb' was not found ...
        >
)

add_test(NAME coro-tests COMMAND ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER tests)
