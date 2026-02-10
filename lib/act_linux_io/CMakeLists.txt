# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# -----------------------------------------------------------------------------
# act_linux_io - Linux I/O library
# -----------------------------------------------------------------------------
# Platform-specific library for Linux I/O operations including GPIO control
# and LED management via sysfs and libgpiod.
#
# Dependencies: act_misc, act_logger
# External: libgpiod v2.x (libgpiod-dev)
# -----------------------------------------------------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGPIOD libgpiodcxx)

add_library(act_linux_io STATIC
    src/gpio/linux_gpio.cpp
    src/led/linux_led.cpp
    src/led/trigger/abs_led_trigger_config.cpp
    src/led/trigger/oneshot_led_trigger_config.cpp
    src/led/trigger/pattern_led_trigger_config.cpp
    src/led/trigger/simple_led_trigger_config.cpp
)

target_include_directories(act_linux_io
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    ${LIBGPIOD_INCLUDE_DIRS}
)

target_compile_features(act_linux_io PUBLIC cxx_std_20)

target_link_libraries(act_linux_io
    PUBLIC
    act_misc
    act_logger
    PRIVATE
    ${LIBGPIOD_LIBRARIES}
)

install(TARGETS act_linux_io DESTINATION lib)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.hpp"
)
