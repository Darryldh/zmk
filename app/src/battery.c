/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/sensor.h>
#include <bluetooth/services/bas.h>
#include <stdio.h>

#include <logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>

const struct device *battery;


static void zmk_battery_update(const struct device *battery) {

    struct sensor_value voltage, current, state_of_charge, full_charge_capacity, remaining_charge_capacity, 
        avg_power, int_temp, current_standby, current_max_load, state_of_health, int_ttempty, int_ttfull, 
        chargeCyles, nominal_capacity, designed_voltage, desired_voltage, desired_charge_current;

    int status = 0;

    while (1) {

        /* use sensor API to request data from the battery */
        status = sensor_sample_fetch(battery);

        if (status != 0) {
            LOG_DBG("Failed to fetch battery data from sensor");
        }


        /* define new event */
        struct battery_state_changed *ev = new_battery_state_changed();


        /* ---------- get channel data for State of Charge ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_STATE_OF_CHARGE, &state_of_charge);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery state of charge: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: State of Charge");

        } else {
            LOG_DBG("Setting BAS GATT battery level to %d%%", state_of_charge.val1);

            /* set BAS GATT battery level so it can be displayed at the host */
            status = bt_bas_set_battery_level(state_of_charge.val1);

            if (status != 0) {
                LOG_WRN("Failed to set BAS GATT battery level (err %d)", status);
            }
            /* append this value to the event */
            ev->state_of_charge = state_of_charge.val1;
            LOG_DBG("-----> battery State of Charge: %d%%", state_of_charge.val1);
 
        }
        


        /* ---------- get channel data for Voltage ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_VOLTAGE, &voltage);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery voltage: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Voltage");
        } else {
            /* append this value to the event */
            ev->voltage_sv = voltage;
            LOG_DBG("-----> battery voltage: %d.%dV", voltage.val1, voltage.val2);
        }
        


        /* ---------- get channel data for Average Current ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_AVG_CURRENT, &current);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Average Current: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Average Current");
        } else {
            /* append this value to the event */
            ev->current = current;
            LOG_DBG("-----> battery Average Current: %d.%dmA", current.val1, current.val2);
        }
        


        /* ---------- get channel data for Full Charge Capacity ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_FULL_CHARGE_CAPACITY, &full_charge_capacity);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Full Charge Capacity: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Full Charge Capacity");
        } else {
            /* append this value to the event */
            ev->full_charge_capacity = full_charge_capacity;
            LOG_DBG("-----> battery Full Charge Capacity: %d.%dmA", full_charge_capacity.val1, full_charge_capacity.val2);
        }
        


        /* ---------- get channel data for Remaining Charge Capacity ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_REMAINING_CHARGE_CAPACITY, &remaining_charge_capacity);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Remaining Charge Capacity: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Remaining Charge Capacity");
        } else {
            /* append this value to the event */
            ev->remaining_charge_capacity = remaining_charge_capacity;
            LOG_DBG("-----> battery Remaining Charge Capacity: %d.%dmA", remaining_charge_capacity.val1, remaining_charge_capacity.val2);
        }
        


        /* ---------- get channel data for Average Power Usage ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_AVG_POWER, &avg_power);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Average Power Usage: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Average Power Usage");
        } else {
            /* append this value to the event */
            ev->avg_power = avg_power;
            LOG_DBG("-----> battery Average Power Usage: %d.%dmW", avg_power.val1, avg_power.val2);
        }
        


        /* ---------- get channel data for Internal IC Temperature ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_TEMP, &int_temp);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get Internal IC Temperature: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Internal IC Temperature");
        } else {
            /* append this value to the event */
            ev->int_temp = int_temp;
            LOG_DBG("-----> battery Internal IC Temperature: %d.%d C", int_temp.val1, int_temp.val2);
        }
        


        /* ---------- get channel data for Standby Current ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_STDBY_CURRENT, &current_standby);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Standby Current: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Standby Current");
        } else {
            /* append this value to the event */
            ev->current_standby = current_standby;
            LOG_DBG("-----> battery Standby Current: %d.%dA", current_standby.val1, current_standby.val2);
        }
        


        /* ---------- get channel data for Maximum Load Current ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_MAX_LOAD_CURRENT, &current_max_load);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Maximum Load Current: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Maximum Load Current");
        } else {
            /* append this value to the event */
            ev->current_max_load = current_max_load;
            LOG_DBG("-----> battery Maximum Load Current: %d.%dA", current_max_load.val1, current_max_load.val2);
        }
        


        /* ---------- get channel data for State of Health ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_STATE_OF_HEALTH, &state_of_health);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery State of Health: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: State of Health");
        } else {
            /* append this value to the event */
            ev->state_of_health = state_of_health.val1;
            LOG_DBG("-----> battery State of Health: %d%%", state_of_health.val1);
        }
        


        /* ---------- get channel data for Time To Empty ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_TIME_TO_EMPTY, &int_ttempty);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Time To Empty: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Time To Empty");
        } else {
            /* append this value to the event */
            ev->time_till_empty = int_ttempty;
            LOG_DBG("-----> battery Time To Empty: %d.%dS", int_ttempty.val1, int_ttempty.val2);
        }
        


        /* ---------- get channel data for Time To Full ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_TIME_TO_FULL, &int_ttfull);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Time To Full: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Time To Full");
        } else {
            /* append this value to the event */
            ev->time_till_full = int_ttfull;
            LOG_DBG("-----> battery Time To Full: %d.%dS", int_ttfull.val1, int_ttfull.val2);
        }
         


        /* ---------- get channel data for Charge Cycle Count ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_CYCLE_COUNT, &chargeCyles);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Charge Cycle Count: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Charge Cycle Count");
        } else {
            /* append this value to the event */
            ev->chargeCyles = chargeCyles.val1 + chargeCyles.val2;
            LOG_DBG("-----> battery Charge Cycle Count: %d", chargeCyles.val1);
        }
         


        /* ---------- get channel data for Nominal Available Capacity ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_NOM_AVAIL_CAPACITY, &nominal_capacity);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery Nominal Available Capacity: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: Nominal Available Capacity");
        } else {
            /* append this value to the event */
            ev->nominal_capacity = nominal_capacity;
            LOG_DBG("-----> battery Nominal Available Capacity: %d.%dmAh", nominal_capacity.val1, nominal_capacity.val2);
        }
          


        /* ---------- get channel data for System Designed Voltage ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_DESIGN_VOLTAGE, &designed_voltage);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery System Designed Voltage: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: System Designed Voltage");
        } else {
            /* append this value to the event */
            ev->designed_voltage = designed_voltage;
            LOG_DBG("-----> battery System Designed Voltage: %d.%dV", designed_voltage.val1, designed_voltage.val2);
        }
          


        /* ---------- get channel data for System Desired Voltage ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_DESIRED_VOLTAGE, &desired_voltage);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery System Desired Voltage: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: System Desired Voltage");
        } else {
            /* append this value to the event */
            ev->desired_voltage = desired_voltage;
            LOG_DBG("-----> battery System Desired Voltage: %d.%dV", desired_voltage.val1, desired_voltage.val2);
        }
          


        /* ---------- get channel data for System Desired Charging Current ---------- */
        status = sensor_channel_get(battery, SENSOR_CHAN_GAUGE_DESIRED_CHARGING_CURRENT, &desired_charge_current);

        if (status != 0 && status != -ENOTSUP) {
            LOG_DBG("Failed to get battery System Desired Charging Current: %d", status);
        }
        if (status == -ENOTSUP) {
            LOG_DBG("The battery sensor does not support the channel: System Desired Charging Current");
        } else {
            /* append this value to the event */
            ev->desired_charge_current = desired_charge_current;
            LOG_DBG("-----> battery System Desired Charging Current: %d.%dmAh", desired_charge_current.val1, desired_charge_current.val2);
        }


        /* trigger event to notify of battery sensor value changes */
        ZMK_EVENT_RAISE(ev);


        /* Delay 1 minute before the next loop */
        k_sleep(K_MSEC(60000));

    }
}



static int zmk_battery_init(const struct device *_arg) {

    battery = device_get_binding("BATTERY");

    if (!battery) {
        LOG_DBG("No device labelled 'BATTERY' found; did initialization fail?");
        return 0;
    }

    zmk_battery_update(battery);

    return 0;
}

SYS_INIT(zmk_battery_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);