# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_system - System-level utilities
# -----------------------------------------------------------------------------
# System-level utilities including multi-process critical sections
# using flock-based locking for safe cross-process synchronization.
#
# Dependencies: act_foundation, act_logger, act_threading, act_text
# -----------------------------------------------------------------------------

add_library(act_system STATIC
    src/abs_system_manager.cpp
)

if(WIN32)
    target_sources(act_system PRIVATE
        src/win/win_system_critical_section.cpp
        src/win/win_system_manager.cpp
    )
else()
    target_sources(act_system PRIVATE
        src/linux/linux_system_critical_section.cpp
        src/linux/linux_system_manager.cpp
    )
endif()

target_include_directories(act_system
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(act_system PUBLIC cxx_std_20)

target_link_libraries(act_system
    PUBLIC
    act_foundation
    act_logger
    act_text
    act_threading
)

install(TARGETS act_system DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
