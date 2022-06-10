macro(run_conan)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

    # Download automatically, you can also just copy the conan.cmake file.
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
        )
    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_configure(
        REQUIRES
            gtest/cci.20210126
        GENERATORS
            cmake_find_package_multi
    )

    set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})

    foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
        conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})
        conan_cmake_install(
            PATH_OR_REFERENCE .
            BUILD missing
            REMOTE conancenter
            SETTINGS ${settings}
        )
    endforeach()

    find_package(GTest CONFIG)
endmacro()
