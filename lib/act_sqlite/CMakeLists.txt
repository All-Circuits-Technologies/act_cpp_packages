# SPDX-FileCopyrightText: 2026 All Circuits Technologies
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_sqlite - SQLite database management library
# -----------------------------------------------------------------------------
# Database abstraction layer providing SQLite database management,
# migrations, and logging integration.
#
# Dependencies: act_system, act_logger, act_misc
# External: SQLiteCpp (libsqlitecpp-dev)
# -----------------------------------------------------------------------------

find_package(SQLiteCpp REQUIRED)

add_library(act_sqlite STATIC
    src/abs_db_manager.cpp
    src/sqlite_db_manager.cpp
)

target_include_directories(act_sqlite
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(act_sqlite PUBLIC cxx_std_20)

target_link_libraries(act_sqlite
    PUBLIC
    act_misc
    act_logger
    act_system
    PRIVATE
    SQLiteCpp
)

install(TARGETS act_sqlite DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
