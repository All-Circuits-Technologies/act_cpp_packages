# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_text - Text and string processing
# -----------------------------------------------------------------------------
# String manipulation, parsing, and text formatting utilities.
# Provides string utilities, vector string operations, and CSV parsing.
#
# Dependencies: act_foundation, act_logger
# -----------------------------------------------------------------------------

add_library(act_text STATIC
    src/string_util.cpp
    src/vector_string_util.cpp
    src/csv_util.cpp
)

# Public headers are exposed via include/<module_name>/
target_include_directories(act_text
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++20 required
target_compile_features(act_text PUBLIC cxx_std_20)

# Dependencies
target_link_libraries(act_text
    PUBLIC
    act_files
    act_foundation
    act_logger
)

# Install targets
install(TARGETS act_text DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
