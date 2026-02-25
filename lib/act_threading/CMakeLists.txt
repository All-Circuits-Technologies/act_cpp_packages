# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_threading - Threading utilities
# -----------------------------------------------------------------------------
# Thread management, synchronization, and concurrent programming utilities.
# Provides reusable thread abstractions and thread-safe wrappers.
#
# Dependencies: act_foundation, act_logger
# -----------------------------------------------------------------------------

add_library(act_threading STATIC
    src/reusable_thread.cpp
)

# Public headers are exposed via include/<module_name>/
target_include_directories(act_threading
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++20 required
target_compile_features(act_threading PUBLIC cxx_std_20)

# Dependencies
find_package(Threads REQUIRED)
target_link_libraries(act_threading
    PUBLIC
    act_foundation
    act_logger
    PRIVATE
    Threads::Threads
)

# Install targets
install(TARGETS act_threading DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
