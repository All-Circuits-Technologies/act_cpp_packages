// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include "act_foundation/not_copiable_not_movable.hpp"

namespace act::foundation
{

/** @brief Singletons shared behavior */
template <typename T>
class Singleton : private NotCopiableNotMovable
{
  protected:
    /** @brief Constructor is only accessible to subclasses
     * @note Only subclass T::CreateInstance can create a T instance
     */
    Singleton() = default;

    /// @brief Destructor is only accessible to subclasses
    virtual ~Singleton() = default;
};

} // namespace act::foundation

// Note that superclass can not provide static members to its subclasses.
// Here are some #define to help you call creating singleton subclasses.

#define SINGLETON_PROTO_INSTANCE_CREATOR_VOID(T) static bool CreateInstance()
#define SINGLETON_PROTO_INSTANCE_GETTER(T) static T &Instance()
#define SINGLETON_PROTO_INSTANCE_POINTER(T) static T *_Instance
#define SINGLETON_IMPL_INSTANCE_POINTER(T) T *T::_Instance = nullptr
