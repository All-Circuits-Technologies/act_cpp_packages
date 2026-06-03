# SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_db_core - Contains core database management classes
# -----------------------------------------------------------------------------
# Database abstraction layer providing database management, migrations, and
# logging integration.
#
# Dependencies: act_foundation, act_logger, act_system
# -----------------------------------------------------------------------------

add_library(act_db_core STATIC
    # Services
    src/services/abs_db_manager.cpp
    src/db_transaction.cpp
)

target_include_directories(act_db_core
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(act_db_core PUBLIC cxx_std_20)

target_link_libraries(act_db_core
    PUBLIC
    act_foundation
    act_logger
    act_system
)

install(TARGETS act_db_core DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
