cmake_minimum_required(VERSION 3.23)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Qisumi/vcpkg/scripts/buildsystems/vcpkg.cmake")

PROJECT(KLFZ_MiniCCompiler)

    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

    find_package(fmt CONFIG REQUIRED)
    include_directories(KLFZ_MiniCLex)

    add_subdirectory(KLFZ_MiniCLex)