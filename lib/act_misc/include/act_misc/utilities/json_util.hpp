// SPDX-FileCopyrightText: 2025 Ghislain Mangé <ghislain.mange@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <bits/exception.h>

/* # Forward declaration */

// NOTE (GMA): ideally migrate these macros to an abstract class

/**
 * @brief Validates that a required JSON key exists or returns a specified value
 *
 * This macro checks if a JSON object contains a required key. If the key is missing,
 * it logs an error message and returns the specified fallback value.
 * This is typically used at the beginning of JSON parsing functions to validate
 * that all required fields are present before attempting to parse them.
 *
 * @param jsonKeyStr The JSON key name as a string literal
 * @param jsonKeyExistsMethod method to check jsonKeyStr is set in jsonObject
 * @param logger The logger to use for logging
 * @param XXX The value to return if the key is missing
 *
 * @note Assumes a variable named 'jsonObject' is in scope
 * @note Use this before attempting to access JSON values to prevent exceptions
 */
#define HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonKeyStr, jsonKeyExistsMethod, logger, XXX)      \
    if (!jsonObject.jsonKeyExistsMethod(jsonKeyStr))                                               \
    {                                                                                              \
        logger.errorStream() << "Error: Missing field: " << jsonKeyStr;                            \
        return XXX;                                                                                \
    }

/**
 * Does the same thing as: @ref ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX but without
 * key existence check and variable creation
 */
#define PRIV_ASSIGN_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType,                                      \
                                                    jsonKey,                                       \
                                                    jsonConversion,                                \
                                                    logger,                                        \
                                                    XXX)                                           \
    {                                                                                              \
        std::optional<jsonType> opt##jsonKey;                                                      \
        /* Try JSON conversion */                                                                  \
        try                                                                                        \
        {                                                                                          \
            opt##jsonKey = jsonObject[#jsonKey].jsonConversion();                                  \
        }                                                                                          \
        catch (const std::exception &e)                                                            \
        {                                                                                          \
            logger.errorStream() << e.what();                                                      \
            return XXX;                                                                            \
        }                                                                                          \
        if (opt##jsonKey.has_value())                                                              \
        {                                                                                          \
            (jsonKey) = opt##jsonKey.value();                                                      \
        }                                                                                          \
    }

/**
 * @anchor ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX
 * @brief Extracts and assigns a raw value from JSON with error handling
 *
 * This macro safely extracts a value from a JSON object, performs type conversion,
 * and assigns it to a local variable. It includes comprehensive error handling
 * for missing keys and conversion failures. The macro first checks if the key
 * exists, then attempts the conversion in a try-catch block.
 *
 * @param jsonType The C++ type to convert the JSON value to
 * @param jsonKey The JSON key name (used both as string and variable name)
 * @param jsonConversion The JSON conversion method
 * (e.g., i(), s(), d() for the Crow implementation)
 * @param logger The logger to use for logging
 * @param XXX The value to return on any error (missing key or conversion failure)
 *
 * @note Creates a local variable named `jsonKey` of type `jsonType`
 * @note Uses HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX internally for key validation
 * @note Handles JSON conversion exceptions gracefully
 * @note Assumes 'jsonObject' variable is in scope
 * @note If the json type needs a default value, it is better to use
 *       the macro: ASSIGN_FUNDAMENTAL_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType,                                       \
                                                   jsonKey,                                        \
                                                   jsonKeyExistsMethod,                            \
                                                   jsonConversion,                                 \
                                                   logger,                                         \
                                                   XXX)                                            \
    HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX(#jsonKey, jsonKeyExistsMethod, logger, XXX)            \
    jsonType jsonKey;                                                                              \
    PRIV_ASSIGN_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType, jsonKey, jsonConversion, logger, XXX)

/**
 * See documentation here: @ref ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX
 *
 * @param defaultValue The default value to assign if the key is missing
 *
 * @note If the json type doesn't need a default value, it is better to use
 *       the macro: ASSIGN_OBJ_FROM_GENERIC_JSON_OR_RETURN_XXX
 */
#define ASSIGN_FUNDAMENTAL_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType,                               \
                                                           jsonKey,                                \
                                                           jsonKeyExistsMethod,                    \
                                                           defaultValue,                           \
                                                           jsonConversion,                         \
                                                           logger,                                 \
                                                           XXX)                                    \
    HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX(#jsonKey, jsonKeyExistsMethod, logger, XXX)            \
    jsonType jsonKey{defaultValue};                                                                \
    PRIV_ASSIGN_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonType, jsonKey, jsonConversion, logger, XXX)

/**
 * @brief Extracts, converts, and validates typed optData from JSON
 *
 * This macro extracts a value from JSON, converts it to the appropriate C++ type,
 * and validates it using a class's ToType method. It's designed for use within
 * type-safe wrapper classes that need to validate JSON input against their
 * internal validation rules.
 *
 * @param jsonKeyExistsMethod method to check jsonKeyStr is set in jsonObject
 * @param jsonConversion The JSON conversion method
 * (e.g., i(), s(), d() for the Crow implementation)
 * @param logger The logger to use for logging
 * @param XXX The value to return on error (missing key, conversion, or validation failure)
 *
 * @note Assumes 'jsonObject' and 'jsonKeyStr' variables are in scope
 * @note Requires a static ToType method that returns std::optional<Type>
 * @note Creates a local 'optData' variable of type std::optional<Type>
 * @note Used internally by type-safe model classes for JSON parsing
 */
#define ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonKeyExistsMethod,           \
                                                                    jsonConversion,                \
                                                                    logger,                        \
                                                                    XXX)                           \
    HAS_KEY_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonKeyStr, jsonKeyExistsMethod, logger, XXX)          \
    std::optional<Type> optData;                                                                   \
    /* Try JSON conversion */                                                                      \
    try                                                                                            \
    {                                                                                              \
        optData = ToType(jsonObject[jsonKeyStr].jsonConversion(), logger);                         \
    }                                                                                              \
    catch (const std::exception &e)                                                                \
    {                                                                                              \
        logger.errorStream() << e.what();                                                          \
        return XXX;                                                                                \
    }

// NOTE (GMA):migrate this macro to an abstract class

/**
 * @brief Complete JSON validation and class instantiation workflow
 *
 * This macro combines JSON extraction, validation, and class construction into
 * a single operation. It uses ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX
 * to get validated optData, then constructs and returns a class instance if successful,
 * or std::nullopt if validation fails.
 *
 * @param jsonKeyExistsMethod method to check jsonKeyStr is set in jsonObject
 * @param CLASS The type-safe wrapper class to instantiate
 * @param jsonConversion The JSON conversion method
 * (e.g., i(), s(), d() for the Crow implementation)
 * @param logger The logger to use for logging
 *
 * @note Designed for use in static FromJsonObject factory methods
 * @note Returns std::optional<CLASS> - either valid instance or std::nullopt
 * @note Logs detailed error messages for debugging
 * @note Assumes proper ToType validation method exists in the class
 */
#define RETURN_VALIDATED_OR_NULLOPT_FROM_GENERIC_JSON(jsonKeyExistsMethod,                         \
                                                      CLASS,                                       \
                                                      jsonConversion,                              \
                                                      logger)                                      \
    ASSIGN_VALIDATED_TYPED_DATA_FROM_GENERIC_JSON_OR_RETURN_XXX(jsonKeyExistsMethod,               \
                                                                jsonConversion,                    \
                                                                logger,                            \
                                                                std::nullopt)                      \
    if (!optData.has_value())                                                                      \
    {                                                                                              \
        logger.errorStream() << "Error: Invalid value for JSON key: " << jsonKeyStr;               \
        return std::nullopt;                                                                       \
    }                                                                                              \
    return CLASS(optData.value());

/**
 * @brief Parses and validates a type-safe object from JSON with error handling
 *
 * This macro calls a type-safe class's FromJsonObject factory method to parse
 * a JSON value, validates the result, and assigns it to a local variable.
 * If parsing fails or returns std::nullopt, it logs an error and returns
 * the specified fallback value.
 *
 * @param CLASS The type-safe wrapper class with FromJsonObject method
 * @param VAR The name for the local variable to create
 * @param jsonKeyStr The JSON key name as a string literal
 * @param logger The logger to use for logging
 * @param XXX The value to return if parsing/validation fails
 *
 * @note Creates a local variable named `VAR` of type `CLASS&`
 * @note Requires CLASS to have a static FromJsonObject method
 * @note Used for parsing complex type-safe objects from JSON requests
 * @note Assumes 'jsonObject' variable is in scope
 */
#define ASSIGN_VALIDATED_FROM_JSON_OR_RETURN_XXX(CLASS, VAR, jsonKeyStr, logger, XXX)              \
    std::optional<const CLASS> opt##VAR = CLASS::FromJsonObject(jsonObject, jsonKeyStr, logger);   \
    if (!opt##VAR.has_value())                                                                     \
    {                                                                                              \
        logger.errorStream() << "Error: Invalid value from JSON required key: " << jsonKeyStr;     \
        return XXX;                                                                                \
    }                                                                                              \
    const CLASS &VAR = opt##VAR.value();

/**
 * Requires CLASS to have a static FromJsonObject method
 * Requires a variable named 'jsonObject' is in scope
 */
#define UPDATE_RAW_FROM_GENERIC_JSON(object,                                                       \
                                     CLASS,                                                        \
                                     VAR,                                                          \
                                     jsonKeyStr,                                                   \
                                     jsonKeyExistsMethod,                                          \
                                     jsonConversion,                                               \
                                     logger)                                                       \
    if (!jsonObject.jsonKeyExistsMethod(jsonKeyStr))                                               \
    {                                                                                              \
        logger.errorStream() << "Error: Missing field: " << jsonKeyStr;                            \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        try                                                                                        \
        {                                                                                          \
            object->set##VAR(jsonObject[jsonKeyStr].jsonConversion());                             \
        }                                                                                          \
        catch (const std::exception &e)                                                            \
        {                                                                                          \
            logger.errorStream() << "Error: JSON field '" << jsonKeyStr                            \
                                 << "' convertion: " << e.what();                                  \
        }                                                                                          \
    }

/**
 * @brief Validates and converts configuration manager data to a type-safe class instance
 *
 * This macro is designed for use in static FromConfManager factory methods of type-safe
 * wrapper classes. It takes raw configuration data, validates it using the class's ToType
 * method, and returns either a constructed class instance or std::nullopt on validation failure.
 * The macro assumes a 'data' variable is already in scope containing the raw configuration value.
 *
 * @param CLASS The type-safe wrapper class to instantiate (e.g., Rs485BaudRateType)
 * @param logger The logger to use for logging
 *
 * @note Assumes a variable named 'data' is in scope with the raw configuration value
 * @note Requires a static ToType(data) method that returns std::optional<Type>
 * @note Creates a local 'value' variable of type std::optional<Type>
 * @note Returns std::optional<CLASS> - either validated instance or std::nullopt
 * @note Used exclusively in FromConfManager factory methods for configuration integration
 */
#define RETURN_VALIDATED_FROM_DATA(CLASS, logger)                                                  \
    std::optional<const Type> optData = ToType(data, logger);                                      \
    if (!optData.has_value())                                                                      \
    {                                                                                              \
        logger.errorStream() << "Error: Invalid value from data: " << data;                        \
        return std::nullopt;                                                                       \
    }                                                                                              \
    return CLASS(optData.value());
