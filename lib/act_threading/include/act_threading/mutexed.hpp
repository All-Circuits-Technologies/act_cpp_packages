// SPDX-FileCopyrightText: 2026 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include <mutex>
#include <utility>

namespace act::threading
{

/**
 * @brief Object holding a value and a mutex to protect it, with few helpers around
 *
 * @warning This class is not suitable for a pointer type T, only a value type T.
 *          A MutexedPtr class could be created if needed.
 */
template <typename T>
class Mutexed
{
    /* ## Types */
    /* ## Constructors */
  public:
    /**
     * @brief Constructor forwarding arguments to the value's constructor
     */
    template <typename... Args>
    explicit Mutexed(Args &&...args)
        : value(std::forward<Args>(args)...)
    {
        // Empty
    }

    /**
     * @brief Default destructor
     */
    ~Mutexed() = default;

    /* ## Methods (members, then non-members) */
  public:
    /**
     * @brief Overload of operator-> to access the value directly
     * @warning The mutex is NOT locked in this case, so the user must
     *          ensure proper locking if needed
     * @return Pointer to the protected value
     */
    [[nodiscard]] T *operator->()
    {
        return &value;
    }

    /**
     * @brief Overload of operator* to access the value directly
     * @warning The mutex is NOT locked in this case, so the user must
     *          ensure proper locking if needed
     * @return Reference to the protected value
     */
    [[nodiscard]] T &operator*()
    {
        return value;
    }

    /**
     * @brief Get a mutex holder, locking the mutex until it goes out of scope
     * @return Unique lock holding the mutex
     * @note The returned lock must be kept in scope to keep the mutex locked
     * @note std::lock_guard cannot be used here as it does not support
     *       being returned from a function (it cannot be moved nor copied).
     *       std::unique_lock supports being moved (not being copied).
     *       std::unique_lock is also more feature-full (manual unlock/relock, etc.),
     *       but caller is unlikely to need these features.
     *       Tt likely want to use it as simply as a std::lock_guard.
     */
    [[nodiscard]] std::unique_lock<std::mutex> lock() const
    {
        return std::unique_lock<std::mutex>(mtx);
    }

    /**
     * @brief Access the value with the mutex locked, executing the given function
     * @param f Function to execute, must have a single T& argument by which
     *          it accesses the protected value
     * @return The return value of the function
     */
    template <typename F>
    auto withLock(F &&f)
    {
        std::lock_guard<std::mutex> lock(mtx);
        return std::forward<F>(f)(value);
    }

    /**
     * @brief Equality operator comparing the protected values with proper locking
     * @param other Other Mutexed object to compare with
     * @return true if both protected values are equal, false otherwise
     */
    bool operator==(const Mutexed<T> &other) const
    {
        std::lock_guard<std::mutex> lock1(mtx);
        std::lock_guard<std::mutex> lock2(other.mtx);
        return value == other.value;
    }

    /**
     * @brief Inequality operator comparing the protected values with proper locking
     * @param other Other Mutexed object to compare with
     * @return true if both protected values are not equal, false otherwise
     */
    bool operator!=(const Mutexed<T> &other) const
    {
        return !(*this == other);
    };

    /* ## Constants */

    /* ## Data members */
  public:
    /**
     * @brief Value which should be protected by a mutex
     */
    T value;

    /**
     * @brief Mutex protecting the value
     */
    mutable std::mutex mtx;
};

} // namespace act::threading
