# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_db_sqlite - SQLite database management library
# -----------------------------------------------------------------------------
# Database abstraction layer providing SQLite database management,
# migrations, and logging integration.
#
# Dependencies: act_foundation, act_logger, act_system, act_db_core
# External: SQLiteCpp (libsqlitecpp-dev)
# -----------------------------------------------------------------------------

if(NOT TARGET SQLiteCpp)
    find_package(SQLiteCpp REQUIRED)
endif()

add_library(act_db_sqlite STATIC
    src/sqlite_db_manager.cpp
)

target_include_directories(act_db_sqlite
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(act_db_sqlite PUBLIC cxx_std_20)

target_link_libraries(act_db_sqlite
    PUBLIC
    act_db_core
    act_foundation
    act_logger
    act_system
    SQLiteCpp
)

install(TARGETS act_db_sqlite DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
