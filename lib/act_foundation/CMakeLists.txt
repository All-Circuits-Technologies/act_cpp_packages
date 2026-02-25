# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_foundation - Base classes and patterns
# -----------------------------------------------------------------------------
# Foundational types and design patterns used across all modules.
# Provides base classes, constants, and common patterns (singleton, RAII).
# This module has no internal dependencies.
# -----------------------------------------------------------------------------

# Header-only library
add_library(act_foundation INTERFACE)

# Public headers are exposed via include/<module_name>/
target_include_directories(act_foundation
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++20 required
target_compile_features(act_foundation INTERFACE cxx_std_20)

# Install targets
install(TARGETS act_foundation DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
