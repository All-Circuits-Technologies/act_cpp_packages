# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_misc - Utility and helper library
# -----------------------------------------------------------------------------
# Base utilities module providing common helpers, threading utilities,
# file operations, string manipulation, and other miscellaneous functionalities.
# This module has no internal dependencies.
# -----------------------------------------------------------------------------

add_library(act_misc STATIC
    # Helpers
    src/helpers/action_delayer.cpp
    src/helpers/restartable_timer.cpp

    # Managers
    src/managers/system_manager.cpp

    # Models
    src/models/ext_file.cpp

    # Threading
    src/threading/reusable_thread.cpp

    # Utilities
    src/utilities/csv_util.cpp
    src/utilities/date_time_util.cpp
    src/utilities/file_util.cpp
    src/utilities/string_util.cpp
    src/utilities/vector_string_util.cpp
)

# Public headers are exposed via include/<module_name>/
target_include_directories(act_misc
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++20 required for std::ranges and other features
target_compile_features(act_misc PUBLIC cxx_std_20)

# Dependencies
# Note: act_misc depends on act_logger for the AbsLogger interface
# This is intentional - logger abstractions are in act_logger

# Link pthread for threading support
find_package(Threads REQUIRED)
target_link_libraries(act_misc
    PUBLIC
    act_logger
    PRIVATE
    Threads::Threads
)

# Install targets
install(TARGETS act_misc DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
