// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_misc/constants/def_soft.hpp"
#include "act_misc/events/keyed_callbacks_register.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <functional>
#include <string>

/* # Forward declaration */


/**
 * @brief This class helps registering and unregistering non-keyed callbacks.
 * @note A default global key is used to store all callbacks.
 * @tparam CallbackArgs Types of arguments of the callbacks
 */
template <typename... CallbackArgs>
class CallbacksRegister : public KeyedCallbacksRegister<std::string, CallbackArgs...>
{
  public:
    /**
     * @brief Constructor
     */
    explicit CallbacksRegister() = default;

    /**
     * @brief Destructor
     */
    ~CallbacksRegister() override = default;

  public:
    /**
     * @brief Register a callback
     * @param callback Callback to register
     * @param isFirstForKey Optional pointer to a boolean that will be set to true if this is the
     *                      first callback registered, false otherwise
     * @return A unique key to unregister the callback later
     */
    OBJ_PTR_AS_UNIQUE_KEY registerCallback(const std::function<void(CallbackArgs...)> &callback,
                                           bool *isFirstForKey = nullptr);

    /**
     * @brief Get all registered callbacks
     * @return Vector of callbacks if found, nullopt otherwise
     */
    std::optional<std::vector<const std::function<void(CallbackArgs...)> &>> getCallbacks() const;

    /**
     * @brief Call all registered callbacks
     * @param args Arguments to pass to the callbacks
     */
    void callCallbacks(CallbackArgs &&...args) const;

  private:
    /** @brief Global key for non-keyed callbacks */
    static inline const std::string GLOBAL_KEY = "GLOBAL";
};

template <typename... CallbackArgs>
inline OBJ_PTR_AS_UNIQUE_KEY CallbacksRegister<CallbackArgs...>::registerCallback(
    const std::function<void(CallbackArgs...)> &callback, bool *isFirstForKey)
{
    return this->registerKeyedCallback(GLOBAL_KEY, callback, isFirstForKey);
}

template <typename... CallbackArgs>
inline std::optional<std::vector<const std::function<void(CallbackArgs...)> &>> CallbacksRegister<
    CallbackArgs...>::getCallbacks() const
{
    return this->getCallbacksForKey(GLOBAL_KEY);
}

template <typename... CallbackArgs>
inline void CallbacksRegister<CallbackArgs...>::callCallbacks(CallbackArgs &&...args) const
{
    this->callCallbacksForKey(GLOBAL_KEY, std::forward<CallbackArgs>(args)...);
}

