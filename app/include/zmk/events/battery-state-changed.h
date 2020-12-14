/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr.h>
#include <zmk/event-manager.h>

struct battery_state_changed {
    struct zmk_event_header header;

    /* Current cell voltage in units of 1.25/16mV */
    uint16_t voltage;
    char strVoltage;

    /* Average current in units of 1.5625uV / Rsense */
    int16_t current;

    /* Remaining capacity as a %age */
    uint16_t state_of_charge;

    /* Internal temperature in units of 1/256 degrees C */
    int16_t int_temp;

    /* Full charge capacity in 5/Rsense uA */
    uint16_t full_charge_capacity;

    /* Remaining capacity in 5/Rsense uA */
    uint16_t remaining_charge_capacity;

    /* Time to empty in seconds */
    uint16_t int_ttempty;

    /* Time to full in seconds */
    uint16_t int_ttfull;

    /* Cycle count in 1/100ths (number of charge/discharge cycles) */
    uint16_t chargeCyles;

    /* Design capacity in 5/Rsense uA */
    uint16_t nominal_capacity;

    /* Standby current in mA? uA? */
    int16_t current_standby;

    /* Maximum Load Current in mA? uA? */
    int16_t current_max_load;

    /* State of Health */
    int16_t state_of_health;

    /* Design voltage of cell in mV */
    uint16_t designed_voltage;

    /* Desired voltage of cell in mV */
    uint16_t desired_voltage;

    /* Desired charging current in mA */
	uint16_t desired_charge_current;

    /* Average power consumption in mA? uA? */
    int16_t avg_power;

};

ZMK_EVENT_DECLARE(battery_state_changed);