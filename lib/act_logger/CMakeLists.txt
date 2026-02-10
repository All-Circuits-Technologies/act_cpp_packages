# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_logger - Logging service library
# -----------------------------------------------------------------------------
# Logging infrastructure providing logger managers, external loggers,
# console output, and helper utilities for consistent logging across modules.
#
# Dependencies: act_misc
# -----------------------------------------------------------------------------

add_library(act_logger STATIC
    # Helpers
    src/helpers/logger_helper.cpp
    src/helpers/logger_stream.cpp
    src/helpers/multi_external_logger.cpp
    src/helpers/sub_logger_helper.cpp

    # Printers
    src/printers/abs_external_logger.cpp
    src/printers/std_console_logger.cpp

    # Services
    src/services/abs_logger_manager.cpp
    src/services/logger_manager.cpp
)

# Public headers are exposed via include/<module_name>/
target_include_directories(act_logger
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++20 required (inherited from misc)
target_compile_features(act_logger PUBLIC cxx_std_20)

# Dependencies
target_link_libraries(act_logger
    PUBLIC
    act_misc
)

# Install targets
install(TARGETS act_logger DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
