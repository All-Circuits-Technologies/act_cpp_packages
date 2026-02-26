#!/bin/bash
# SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
#
# SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

# Script to run clang-tidy locally on the project
# Usage: ./tools/run_clang_tidy.sh [--fix] [file1.cpp file2.cpp ...]
#
# Requirements:
#   - clang-tidy (version 21 preferred, matching CI)
#   - CMake build directory at ./build with compile_commands.json
#
# Options:
#   --fix    Apply clang-tidy suggested fixes automatically
#
# If no files are specified, all .cpp and .hpp files in lib/ are analyzed.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Detect clang-tidy binary (prefer versioned binary matching CI)
CLANG_TIDY=""
for candidate in clang-tidy-21 clang-tidy; do
    if command -v "$candidate" &>/dev/null; then
        CLANG_TIDY="$candidate"
        break
    fi
done

if [[ -z "$CLANG_TIDY" ]]; then
    echo -e "${RED}Error: clang-tidy not found. Install clang-tidy (version 21 recommended).${NC}"
    exit 1
fi

echo -e "${GREEN}Using: $CLANG_TIDY ($($CLANG_TIDY --version | head -1))${NC}"

# Ensure compile_commands.json exists
if [[ ! -f "${BUILD_DIR}/compile_commands.json" ]]; then
    echo -e "${YELLOW}compile_commands.json not found. Generating...${NC}"
    cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}"
fi

# Parse arguments
FIX_FLAG=""
FILES=()
for arg in "$@"; do
    if [[ "$arg" == "--fix" ]]; then
        FIX_FLAG="--fix"
    else
        FILES+=("$arg")
    fi
done

# If no files specified, find all source files in lib/
if [[ ${#FILES[@]} -eq 0 ]]; then
    while IFS= read -r -d '' file; do
        FILES+=("$file")
    done < <(find "${PROJECT_ROOT}/lib" \( -name '*.cpp' -o -name '*.hpp' \) -not -path '*/build/*' -print0 | sort -z)
fi

echo -e "${GREEN}Analyzing ${#FILES[@]} file(s)...${NC}"

# Run clang-tidy
WARNINGS=0
ERRORS=0

for file in "${FILES[@]}"; do
    echo -e "${YELLOW}Checking: ${file#"${PROJECT_ROOT}/"}${NC}"
    set +e
    OUTPUT=$($CLANG_TIDY \
        -p "${BUILD_DIR}" \
        --extra-arg="-std=c++20" \
        ${FIX_FLAG} \
        "$file" 2>&1)
    EXIT_CODE=$?
    set -e

    if [[ -n "$OUTPUT" ]]; then
        echo "$OUTPUT"
        # Count warnings
        FILE_WARNINGS=$(echo "$OUTPUT" | grep -c ': warning:' || true)
        FILE_ERRORS=$(echo "$OUTPUT" | grep -c ': error:' || true)
        WARNINGS=$((WARNINGS + FILE_WARNINGS))
        ERRORS=$((ERRORS + FILE_ERRORS))
    fi
done

echo ""
echo "============================================"
if [[ $WARNINGS -eq 0 && $ERRORS -eq 0 ]]; then
    echo -e "${GREEN}All checks passed! No warnings or errors found.${NC}"
    exit 0
else
    echo -e "${RED}Found ${WARNINGS} warning(s) and ${ERRORS} error(s).${NC}"
    exit 1
fi
