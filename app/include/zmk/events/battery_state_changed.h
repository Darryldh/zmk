/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr.h>
#include <zmk/event_manager.h>

struct battery_state_changed {

    struct zmk_event_header header;

    /* Current cell voltage in units of 1.25/16mV */
    struct sensor_value voltage_sv;

    /* Average current in units of 1.5625uV / Rsense */
    struct sensor_value current;

    /* Remaining capacity as a %age */
    uint16_t state_of_charge;

    /* Internal temperature in units of 1/256 degrees C */
    struct sensor_value int_temp;

    /* Full charge capacity in 5/Rsense uA */
    struct sensor_value full_charge_capacity;

    /* Remaining capacity in 5/Rsense uA */
    struct sensor_value remaining_charge_capacity;

    /* Time to empty in seconds */
    struct sensor_value time_till_empty;

    /* Time to full in seconds */
    struct sensor_value time_till_full;

    /* Cycle count in 1/100ths (number of charge/discharge cycles) */
    uint16_t chargeCyles;

    /* Design capacity in 5/Rsense uA */
    struct sensor_value nominal_capacity;

    /* Standby current in mA? uA? */
    struct sensor_value current_standby;

    /* Maximum Load Current in mA? uA? */
    struct sensor_value current_max_load;

    /* State of Health */
    int16_t state_of_health;

    /* Design voltage of cell in mV */
    struct sensor_value designed_voltage;

    /* Desired voltage of cell in mV */
    struct sensor_value desired_voltage;

    /* Desired charging current in mA */
	struct sensor_value desired_charge_current;

    /* Average power consumption in mA? uA? */
    struct sensor_value avg_power;

};

ZMK_EVENT_DECLARE(zmk_battery_state_changed);