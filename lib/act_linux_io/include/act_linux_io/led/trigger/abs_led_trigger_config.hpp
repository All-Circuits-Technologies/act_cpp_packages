// SPDX-FileCopyrightText: 2026 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <string>
#include <vector>

/* # Forward declaration */
class LinuxLed;

/**
 * @brief Abstract Linux LED trigger interface
 *
 * Subclasses are tools useful to configure triggers onto LinuxLed instances
 */
class AbsLedTriggerConfig
{
    /* ## Types */
    /* ## Constructors */
  public:
    /**
     * @brief Constructor
     * @param name Name of the trigger, must match Linux LED trigger name
     */
    explicit AbsLedTriggerConfig(std::string name);

    /**
     * @brief Destructor
     */
    virtual ~AbsLedTriggerConfig() = default;

    /* ## Methods (members, then non-members) */
  public:
    /**
     * @brief Drive given LED to join current trigger configuration
     * @param led LED to configure
     * @param force If true, force re-selecting the trigger even if already selected
     *              If false and trigger is already selected, then it will be reconfigured
     *              and refired but not previously re-selected.
     * @return True on success, false on failure
     */
    [[nodiscard]] bool applyToLed(LinuxLed &led, bool force = false) const
    {
        return prepareLed(led, force) && fireOnLed(led);
    }

    /**
     * @brief Check if the trigger is currently applied to the given LED
     * @return True if the trigger is applied to the LED, false otherwise
     * @retval False upon issues reading LED state
     * @note Default implementation only compares trigger names, subclasses
     *       must call it and extend it to compare their arguments if any
     */
    [[nodiscard]] virtual bool isLedAlreadyConfigured(const LinuxLed &led) const;

    /**
     * @brief Ensure given LED has current trigger configuration
     * @param led LED to configure
     * @param force If true, force re-selecting the trigger even if already selected
     *              If false and trigger is already selected, then it will be reconfigured
     *              and refired but not previously re-selected.
     * @return True on success, false on failure
     * @retval True if it was already configured
     * @see applyToLed
     * @note Do nothing if LED already has current trigger configuration
     */
    [[nodiscard]] bool applyToLedIfNotAlreadyConfigured(LinuxLed &led, bool force = false) const
    {
        return isLedAlreadyConfigured(led) || applyToLed(led, force);
    }

    /**
     * @brief Drive given LEDs to join current trigger configuration
     * @param leds LEDs to configure
     * @param force If true, force re-selecting the trigger even if already selected
     *              If false and trigger is already selected, then it will be reconfigured
     *              and refired but not previously re-selected.
     * @return True on success, false on failure
     * @note Preparing the trigger may take time, so in order to increase syncness
     *       of driven LEDs, we first prepare them all, then we fire them all.
     */
    [[nodiscard]] bool applyToLeds(const std::vector<std::reference_wrapper<LinuxLed>> &leds,
                                   bool force = false) const;

    /**
     * @brief Configure LED to be ready for the trigger, without starting the trigger
     * @param led LED to configure
     * @param force If true, force re-selecting the trigger even if already selected
     *              If false and trigger is already selected, then it will be reprepared
     *              but not previously re-selected.
     * @return True on success, false on failure
     * @note Write trigger name to the LED and call subclass extra preparation
     */
    bool prepareLed(LinuxLed &led, bool force) const;

    /**
     * @brief Actually fire or fire again the trigger on the given LED
     * @param led LED to fire trigger onto
     * @return True if useless, True on success, false on failure
     * @note LED must have been previously prepared with @ref applyToLed or @ref prepareLed
     *       and must still be prepared. Especially its trigger must not have been changed
     *       or cleared directly or through explicit state/brightness setting.
     * @retval If current trigger has no "fire" action (ex: "heartbeat" or "timer" trigger),
     *         true is always returned.
     */
    virtual bool fireOnLed(LinuxLed &led) const = 0;

  protected:
    /**
     * @brief Configure trigger parameters onto LED, without starting the trigger
     * @param led LED to configure
     * @return True on success, false on failure
     * @note At this point, the trigger name has already been written to the LED
     * @note Since we better like to not start the trigger yet (for syncness reasons,
     *       see @ref applyToLeds), sub-classes may need to move some configurations
     *       to their @ref fireOnLed implementation.
     */
    virtual bool prepareLedExtra(LinuxLed &led) const = 0;

    /* ## Data members */
  private:
    // Configuration
    /** @brief Linux trigger name */
    const std::string m_name;
};
