// SPDX-FileCopyrightText: 2025 Ghislain Mangé <ghislain.mange@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_misc/utilities/json_util.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

/* # Forward declaration */

/**
 * Crow implementation of generic @ref HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define HAS_KEY_FROM_JSON_OR_RETURN_XXX(jsonKeyStr, logger, XXX)                                   \
    HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonKeyStr, has, logger, XXX)

/**
 * Crow implementation of generic @ref ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_OBJ_FROM_JSON_OR_RETURN_XXX(jsonType, jsonKey, jsonConversion, logger, XXX)         \
    ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType, jsonKey, has, jsonConversion, logger, XXX)

/**
 * Crow implementation of generic @ref ASSIGN_FUNDAMENTAL_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_FUNDAMENTAL_FROM_JSON_OR_RETURN_XXX(jsonType,                                       \
                                                   jsonKey,                                        \
                                                   defaultValue,                                   \
                                                   jsonConversion,                                 \
                                                   logger,                                         \
                                                   XXX)                                            \
    ASSIGN_FUNDAMENTAL_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType,                                   \
                                                       jsonKey,                                    \
                                                       has,                                        \
                                                       defaultValue,                               \
                                                       jsonConversion,                             \
                                                       logger,                                     \
                                                       XXX)

/**
 * Crow implementation of generic @ref ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_VALIDATED_TYPED_DATA_FROM_JSON_OR_RETURN_XXX(jsonConversion, logger, XXX)           \
    ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX(has, jsonConversion, logger, XXX)

/**
 * Crow implementation of generic @ref RETURN_VALIDATED_OR_NULLOPT_FROM_GENERIC_JSON
 */
#define RETURN_VALIDATED_OR_NULLOPT_FROM_JSON(CLASS, jsonConversion, logger)                       \
    RETURN_VALIDATED_OR_NULLOPT_FROM_GENERIC_JSON(has, CLASS, jsonConversion, logger)

/**
 * Crow implementation of generic @ref UPDATE_RAW_FROM_GENERIC_JSON
 */
#define UPDATE_RAW_FROM_JSON(object, CLASS, VAR, jsonKeyStr, has, jsonConversion, logger)          \
    UPDATE_RAW_FROM_GENERIC_JSON(object,                                                           \
                                 CLASS,                                                            \
                                 VAR,                                                              \
                                 jsonKeyStr,                                                       \
                                 jsonKeyExistsMethod,                                              \
                                 jsonConversion,                                                   \
                                 logger)
