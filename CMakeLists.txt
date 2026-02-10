# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# =============================================================================
# ACT C++ Packages - Root CMakeLists.txt
# =============================================================================
#
# Modular C++ library collection:
#
#   - misc      : Base utilities (threading, file ops, string utils)
#   - logger    : Logging infrastructure and services
#   - system    : System-level utilities (critical sections)
#   - sqlite    : SQLite database management layer
#   - linux_io  : Linux-specific I/O (GPIO, LEDs)
#
# =============================================================================

cmake_minimum_required(VERSION 3.23)

project(act_cpp_packages
    VERSION 1.0.0
    DESCRIPTION "ACT C++ modular library packages"
    LANGUAGES CXX
)

# -----------------------------------------------------------------------------
# Build Options (DOCUMENTATION ONLY)
# -----------------------------------------------------------------------------

option(BUILD_DEMOS "Build demo applications" OFF)
option(BUILD_TESTS "Build tests" OFF)

# -----------------------------------------------------------------------------
# Library Modules
# -----------------------------------------------------------------------------

add_subdirectory(lib/act_misc)
add_subdirectory(lib/act_logger)
add_subdirectory(lib/act_system)
add_subdirectory(lib/act_sqlite)
add_subdirectory(lib/act_linux_io)

# -----------------------------------------------------------------------------
# Demo Applications (TODO)
# -----------------------------------------------------------------------------
# apps/
#   <demo_name>/
#     CMakeLists.txt
#     main.cpp

if(BUILD_DEMOS)
    message(STATUS "Demo applications not yet implemented")
    # add_subdirectory(apps)
endif()

# -----------------------------------------------------------------------------
# Tests (TODO)
# -----------------------------------------------------------------------------
# tests/
#   <module>_tests/
#     CMakeLists.txt
#     test_*.cpp

if(BUILD_TESTS)
    message(STATUS "Tests not yet implemented")
    # enable_testing()
    # add_subdirectory(tests)
endif()
