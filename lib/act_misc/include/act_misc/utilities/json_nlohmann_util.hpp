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
 * Nlohmann implementation of generic @ref HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define HAS_KEY_FROM_NLOHMANN_JSON_OR_RETURN_XXX(jsonKeyStr, logger, XXX)                          \
    HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonKeyStr, contains, logger, XXX)

/**
 * Nlohmann implementation of generic @ref ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_OBJ_FROM_NLOHMANN_JSON_OR_RETURN_XXX(jsonType,                                      \
                                                    jsonKey,                                       \
                                                    jsonConversion,                                \
                                                    logger,                                        \
                                                    XXX)                                           \
    ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType,                                           \
                                               jsonKey,                                            \
                                               contains,                                           \
                                               jsonConversion,                                     \
                                               logger,                                             \
                                               XXX)

/**
 * Nlohmann implementation of generic @ref ASSIGN_FUNDAMENTAL_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_FUNDAMENTAL_FROM_NLOHMANN_JSON_OR_RETURN_XXX(jsonType,                              \
                                                            jsonKey,                               \
                                                            defaultValue,                          \
                                                            jsonConversion,                        \
                                                            logger,                                \
                                                            XXX)                                   \
    ASSIGN_FUNDAMENTAL_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType,                                   \
                                                       jsonKey,                                    \
                                                       contains,                                   \
                                                       defaultValue,                               \
                                                       jsonConversion,                             \
                                                       logger,                                     \
                                                       XXX)

/**
 * Nlohmann implementation of generic @ref
 * ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_VALIDATED_TYPED_DATA_FROM_NLOHMANN_JSON_OR_RETURN_XXX(jsonConversion, logger, XXX)  \
    ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX(contains,                          \
                                                                jsonConversion,                    \
                                                                logger,                            \
                                                                XXX)

/**
 * Nlohmann implementation of generic @ref RETURN_VALIDATED_OR_NULLOPT_FROM_GENERIC_JSON
 */
#define RETURN_VALIDATED_OR_NULLOPT_FROM_NLOHMANN_JSON(CLASS, jsonConversion, logger)              \
    RETURN_VALIDATED_OR_NULLOPT_FROM_GENERIC_JSON(contains, CLASS, jsonConversion, logger)

/**
 * Nlohmann implementation of generic @ref UPDATE_RAW_FROM_GENERIC_JSON
 */
#define UPDATE_RAW_FROM_NLOHMANN_JSON(object,                                                      \
                                      CLASS,                                                       \
                                      VAR,                                                         \
                                      jsonKeyStr,                                                  \
                                      contains,                                                    \
                                      jsonConversion,                                              \
                                      logger)                                                      \
    UPDATE_RAW_FROM_GENERIC_JSON(object,                                                           \
                                 CLASS,                                                            \
                                 VAR,                                                              \
                                 jsonKeyStr,                                                       \
                                 jsonKeyExistsMethod,                                              \
                                 jsonConversion,                                                   \
                                 logger)
