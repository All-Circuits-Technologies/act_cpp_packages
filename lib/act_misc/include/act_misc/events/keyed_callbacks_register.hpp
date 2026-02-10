// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_misc/constants/def_soft.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <functional>
#include <map>
#include <optional>

/* # Forward declaration */


/**
 * @brief This class helps registering and unregistering callbacks associated with keys.
 * @tparam K Type of keys
 * @tparam CallbackArgs Types of arguments of the callbacks
 */
template <typename K, typename... CallbackArgs>
class KeyedCallbacksRegister
{
  public:
    /**
     * @brief Constructor
     */
    explicit KeyedCallbacksRegister() = default;

    /**
     * @brief Destructor
     */
    virtual ~KeyedCallbacksRegister();

  public:
    /**
     * @brief Register a callback for a given key
     * @param key Key to register the callback for
     * @param callback Callback to register
     * @param isFirstForKey Optional pointer to a boolean that will be set to true if this is the
     *                     first callback registered for the given key, false otherwise
     * @return A unique key to unregister the callback later
     */
    OBJ_PTR_AS_UNIQUE_KEY registerKeyedCallback(
        const K &key,
        const std::function<void(CallbackArgs...)> &callback,
        bool *isFirstForKey = nullptr);

    /**
     * @brief Unregister a callback using its unique key
     * @note If the key is not found, nothing is done
     * @param callbackKey Unique key of the callback to unregister
     * @param isLastForKey Optional pointer to a boolean that will be set to true if this was the
     *                     last callback registered for the given key, false otherwise
     */
    void unregisterCallback(OBJ_PTR_AS_UNIQUE_KEY callbackKey, bool *isLastForKey = nullptr);

    /**
     * @brief Unregister all callbacks associated with a given key
     * @param key Key to unregister all callbacks for
     */
    void unregisterAllKeyedCallbacks(const K &key);

    /**
     * @brief Unregister all callbacks
     */
    void unregisterAllCallbacks();

    /**
     * @brief Get all keys that have registered callbacks
     * @return Vector of keys
     */
    std::vector<K> getAllKeys() const;

    /**
     * @brief Get a callback using its unique key
     * @param callbackKey Unique key of the callback to get
     * @return Pointer to the callback if found, nullptr otherwise
     */
    const std::function<void(CallbackArgs...)> *getCallback(
        OBJ_PTR_AS_UNIQUE_KEY callbackKey) const;

    /**
     * @brief Get all callbacks associated with a given key
     * @param key Key to get the callbacks for
     * @return Vector of callbacks if found, nullopt otherwise
     */
    std::optional<std::vector<const std::function<void(CallbackArgs...)> &>> getCallbacksForKey(
        const K &key) const;

    /**
     * @brief Call all callbacks associated with a given key
     * @param key Key to call the callbacks for
     * @param args Arguments to pass to the callbacks
     */
    void callCallbacksForKey(const K &key, CallbackArgs... args) const;

    /**
     * @brief Call all callbacks for keys matching a given predicate
     * @param keyPred Predicate to test keys
     * @param args Arguments to pass to the callbacks
     */
    void callCallbacksOnPred(const std::function<bool(const K &)> &keyPred,
                             CallbackArgs... args) const;

  private:
    /** @brief Registered callbacks */
    std::map<K, std::map<OBJ_PTR_AS_UNIQUE_KEY, std::function<void(CallbackArgs...)> *>>
        m_callbacks;
};

template <typename K, typename... CallbackArgs>
inline KeyedCallbacksRegister<K, CallbackArgs...>::~KeyedCallbacksRegister()
{
    unregisterAllCallbacks();
}

template <typename K, typename... CallbackArgs>
inline OBJ_PTR_AS_UNIQUE_KEY KeyedCallbacksRegister<K, CallbackArgs...>::registerKeyedCallback(
    const K &key, const std::function<void(CallbackArgs...)> &callback, bool *isFirstForKey)
{
    auto callbackPtr = new std::function<void(CallbackArgs...)>(callback);

    auto &callbacksMap = m_callbacks[key];
    if (isFirstForKey != nullptr)
    {
        *isFirstForKey = callbacksMap.empty();
    }

    callbacksMap[callbackPtr] = callbackPtr;
    return callbackPtr;
}

template <typename K, typename... CallbackArgs>
inline void KeyedCallbacksRegister<K, CallbackArgs...>::unregisterCallback(
    OBJ_PTR_AS_UNIQUE_KEY callbackKey, bool *isLastForKey)
{
    if (isLastForKey != nullptr)
    {
        *isLastForKey = false;
    }

    for (auto &keyedCallbacks : m_callbacks)
    {
        auto &callbacksMap = keyedCallbacks.second;
        auto it = callbacksMap.find(callbackKey);
        if (it != callbacksMap.end())
        {
            delete it->second;
            callbacksMap.erase(it);

            if (isLastForKey != nullptr && callbacksMap.empty())
            {
                *isLastForKey = true;
            }

            // The pointer is unique, we can leave the function now
            break;
        }
    }
}

template <typename K, typename... CallbackArgs>
inline void KeyedCallbacksRegister<K, CallbackArgs...>::unregisterAllKeyedCallbacks(const K &key)
{
    auto it = m_callbacks.find(key);
    if (it == m_callbacks.end())
    {
        // Nothing more to do
        return;
    }

    auto &callbacksMap = it->second;
    for (auto &callbackPair : callbacksMap)
    {
        // Remove each callback pointer
        delete callbackPair.second;
    }

    m_callbacks.erase(it);
}

template <typename K, typename... CallbackArgs>
inline void KeyedCallbacksRegister<K, CallbackArgs...>::unregisterAllCallbacks()
{
    for (auto &keyedCallbacks : m_callbacks)
    {
        auto &callbacksMap = keyedCallbacks.second;
        for (auto &callbackPair : callbacksMap)
        {
            // Remove each callback pointer
            delete callbackPair.second;
        }
    }

    m_callbacks.clear();
}

template <typename K, typename... CallbackArgs>
inline const std::function<void(CallbackArgs...)> *KeyedCallbacksRegister<K, CallbackArgs...>::
    getCallback(OBJ_PTR_AS_UNIQUE_KEY callbackKey) const
{
    for (const auto &keyedCallbacks : m_callbacks)
    {
        const auto &callbacksMap = keyedCallbacks.second;
        auto it = callbacksMap.find(callbackKey);
        if (it != callbacksMap.end())
        {
            return it->second;
        }
    }

    return nullptr;
}

template <typename K, typename... CallbackArgs>
inline std::optional<std::vector<const std::function<void(CallbackArgs...)> &>>
KeyedCallbacksRegister<K, CallbackArgs...>::getCallbacksForKey(const K &key) const
{
    auto it = m_callbacks.find(key);
    if (it == m_callbacks.end())
    {
        return std::nullopt;
    }

    const auto &callbacksMap = it->second;
    std::vector<const std::function<void(CallbackArgs...)> &> callbacks;
    for (const auto &callbackPair : callbacksMap)
    {
        callbacks.push_back(*(callbackPair.second));
    }

    return callbacks;
}

template <typename K, typename... CallbackArgs>
inline void KeyedCallbacksRegister<K, CallbackArgs...>::callCallbacksForKey(
    const K &key, CallbackArgs... args) const
{
    auto it = m_callbacks.find(key);
    if (it == m_callbacks.end())
    {
        // No callbacks for this key
        return;
    }

    const auto &callbacksMap = it->second;
    for (const auto &callbackPair : callbacksMap)
    {
        // We know the function can't be null here
        const auto &callback = *callbackPair.second;
        callback(args...);
    }
}

template <typename K, typename... CallbackArgs>
inline void KeyedCallbacksRegister<K, CallbackArgs...>::callCallbacksOnPred(
    const std::function<bool(const K &)> &keyPred, CallbackArgs... args) const
{
    auto citer = m_callbacks.cbegin();
    while (citer != m_callbacks.cend())
    {
        const K &key = citer->first;
        const auto &callbacksMap = citer->second;
        ++citer;

        if (!keyPred(key))
        {
            // Key does not match the predicate
            continue;
        }

        for (const auto &callbackPair : callbacksMap)
        {
            // We know the function can't be null here
            const auto &callback = *callbackPair.second;
            callback(args...);
        }
    }
}

