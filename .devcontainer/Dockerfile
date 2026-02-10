# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

FROM debian:trixie

# =============================================================================
# Toolchain setup
# =============================================================================

# Install base dependencies
RUN apt-get update && apt-get install -y \
    # Build essentials
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    git \
    curl \
    wget \
    unzip \
    xz-utils \
    file \
    # C/C++ tools
    gcc \
    g++ \
    gdb \
    # Additional utilities
    sudo \
    locales \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Set locale
RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# Download and install clang
RUN echo "deb [trusted=yes] http://apt.llvm.org/noble/ llvm-toolchain-noble-21 main" | tee /etc/apt/sources.list.d/llvm.list \
    && echo "deb-src [trusted=yes] http://apt.llvm.org/noble/ llvm-toolchain-noble-21 main" | tee -a /etc/apt/sources.list.d/llvm.list \
    && apt-get update \
    && apt-get install -y \
    clang-21 \
    clangd-21 \
    clang-tidy-21 \
    clang-format-21

# =============================================================================
# User setup
# =============================================================================
ARG USERNAME=dev

RUN useradd -m $USERNAME \
    && echo "$USERNAME ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && usermod -a -G dialout,plugdev $USERNAME

USER $USERNAME
ENV SHELL=/bin/bash

# Set default shell
SHELL ["/bin/bash", "-c"]

# Verify installations
RUN echo "=== Development Environment ===" \
    && echo "GCC: $(gcc --version | head -1)" \
    && echo "CMake: $(cmake --version | head -1)" \
    && echo "Ninja: $(ninja --version)" \
    && echo "================================"

# Default command
CMD ["/bin/bash"]
