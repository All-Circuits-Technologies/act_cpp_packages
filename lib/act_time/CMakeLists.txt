# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_time - Date, time, and timing utilities
# -----------------------------------------------------------------------------
# Time handling, delays, timers, and scheduling utilities.
# Provides date/time operations, restartable timers, and action delays.
#
# Dependencies: act_foundation, act_logger, act_threading
# -----------------------------------------------------------------------------

add_library(act_time STATIC
    src/action_delayer.cpp
    src/date_time_util.cpp
    src/restartable_timer.cpp
)

# Public headers are exposed via include/<module_name>/
target_include_directories(act_time
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++20 required
target_compile_features(act_time PUBLIC cxx_std_20)

# Dependencies
target_link_libraries(act_time
    PUBLIC
    act_foundation
    act_logger
    act_threading
)

# Install targets
install(TARGETS act_time DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
