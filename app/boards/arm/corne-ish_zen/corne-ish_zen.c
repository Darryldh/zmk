/*
 * Copyright (c) 2020 Darryl deHaan
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <sys/printk.h>


static void max17055_show_values(const char *type, struct sensor_value value)
{
	if ((value.val2 < 0) && (value.val1 >= 0)) {
		value.val2 = -(value.val2);
		printk("%s: -%d.%06d\n", type, value.val1, value.val2);
	} else if ((value.val2 > 0) && (value.val1 < 0)) {
		printk("%s: %d.%06d\n", type, value.val1, value.val2);
	} else if ((value.val2 < 0) && (value.val1 < 0)) {
		value.val2 = -(value.val2);
		printk("%s: %d.%06d\n", type, value.val1, value.val2);
	} else {
		printk("%s: %d.%06d\n", type, value.val1, value.val2);
	}
}


static void getSensorData(const struct device *dev) {

      // get sensor channels and values
    struct sensor_value voltage, current, state_of_charge,
		full_charge_capacity, remaining_charge_capacity, avg_power,
		int_temp, current_standby, current_max_load, state_of_health, int_ttempty,
        int_ttfull, chargeCyles, nominal_capacity, designed_voltage, desired_voltage,
        desired_charge_current;

    printk("---> dev passed in: %s\n", dev->name);

    int status = 0;

    while (1) {

        status = sensor_sample_fetch(dev);

        printk("---> Current status: %i\n", status);
        
        if (status < 0) {
			printk("---X Unable to fetch the samples from sensor\n");
		}else{
            printk("---> Sensor samples found!\n");
        } 

        // voltage
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_VOLTAGE, &voltage);
		if (status < 0) {
			printk("---X Unable to get the voltage value\n");
		}else{
            printk("---> Voltage: %d.%06dV\n", voltage.val1, voltage.val2);
        }



        // average current
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_AVG_CURRENT, &current);

		if (status < 0) {
			printk("---X Unable to get the average current value\n");
		}else{
            //printk("---> Avg Current in Amps: %d\n", current);
            max17055_show_values("---> Avg Current in Amps", current);
        }
		
        


        // standby current
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_STDBY_CURRENT, &current_standby);
		if (status < 0) {
			printk("---X Unable to get the standby current value\n");
		}else{
            //printk("---> Standby Current in Amps: %d\n", current_standby);
            max17055_show_values("---> Standby Current in Amps", current_standby);
        }
		
        


        // maximum load current
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_MAX_LOAD_CURRENT, &current_max_load);
		if (status < 0) {
			printk("---X Unable to get the max load current value\n");
		}else{
            //printk("---> Max Load Current in Amps: %d\n", current_max_load);
            max17055_show_values("---> Max Load Current in Amps", current_max_load);
        }
		
        


        // State of Charge
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_STATE_OF_CHARGE, &state_of_charge);
		if (status < 0) {
			printk("---X Unable to get state of charge\n");
		}else{
            printk("---> State of charge: %d%%\n", state_of_charge.val1);
        }
		


        // state of health
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_STATE_OF_HEALTH, &state_of_health);
		if (status < 0) {
			printk("---X Unable to get state of health\n");
		}else{
            printk("---> State of health: %d%%\n", state_of_health.val1);
        }
		


        // Average Power Use
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_AVG_POWER, &avg_power);
		if (status < 0) {
			printk("---X Unable to get avg power\n");
		}else{
            //printk("---> Average Power Usage in Watts: %d\n", avg_power);
            max17055_show_values("---> Avg Power in Watts", avg_power);
        }
		
         


        // Full charge capacity
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_FULL_CHARGE_CAPACITY, &full_charge_capacity);
		if (status < 0) {
			printk("---X Unable to get full charge capacity\n");
		}else{
            printk("---> Full charge capacity: %d.%06dAh\n", full_charge_capacity.val1, full_charge_capacity.val2);
        }
		


        // Remaining charge capacity
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_REMAINING_CHARGE_CAPACITY, &remaining_charge_capacity);
		if (status < 0) {
			printk("---X Unable to get remaining charge capacity\n");
		}else{
            printk("---> Remaining charge capacity: %d.%06dAh\n", remaining_charge_capacity.val1, remaining_charge_capacity.val2);
        }
		


        // Gauge internal temperature
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_TEMP, &int_temp);
		if (status < 0) {
			printk("---X Unable to read internal temperature\n");
		}else{
            printk("---> Gauge Internal Temperature: %d.%06d C\n", int_temp.val1, int_temp.val2);
        }
		


        // Time to Empty
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_TIME_TO_EMPTY, &int_ttempty);
        if (status < 0) {
			printk("---X Unable to get Time Till Empty\n");
		}else{
            //printk("---> Time Till Empty: %d\n", int_ttempty);
            max17055_show_values("---> Time Till Empty", int_ttempty);
        }


        // Time to Full
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_TIME_TO_FULL, &int_ttfull);
        if (status < 0) {
			printk("---X Unable to get Time Till Full\n");
		}else{
            //printk("---> Time Till Full: %d\n", int_ttfull);
            max17055_show_values("---> Time Till Full", int_ttfull);
        }


        // charge cycle count
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_CYCLE_COUNT, &chargeCyles);
        if (status < 0) {
			printk("---X Unable to get Charge Cycle Count\n");
		}else{
            //printk("---> Charge Cycle Count: %d\n", chargeCyles);
            max17055_show_values("---> Charge Cycle Count", chargeCyles);
        }


        // nominal available capacity
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_NOM_AVAIL_CAPACITY, &nominal_capacity);
        if (status < 0) {
			printk("---X Unable to get Nominal Capacity\n");
		}else{
            //printk("---> Nominal Capacity: %d\n", nominal_capacity);
            max17055_show_values("---> Nominal Capacity", nominal_capacity);
        }


        // system designed voltage
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_DESIGN_VOLTAGE, &designed_voltage);
        if (status < 0) {
			printk("---X Unable to get System Designed Voltage\n");
		}else{
            //printk("---> System Designed Voltage: %d\n", designed_voltage);
            max17055_show_values("---> System Designed Voltage", designed_voltage);
        }


        // System Desired Voltage
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_DESIRED_VOLTAGE, &desired_voltage);
        if (status < 0) {
			printk("---X Unable to get System Desired Voltage\n");
		}else{
            //printk("---> System Desired Voltage: %d\n", desired_voltage);
            max17055_show_values("---> System Desired Voltage", desired_voltage);
        }


        // system desired charging current
        status = sensor_channel_get(dev, SENSOR_CHAN_GAUGE_DESIRED_CHARGING_CURRENT, &desired_charge_current);
        if (status < 0) {
			printk("---X Unable to get System Desired Charging Current\n");
		}else{
            //printk("---> System Desired Charging Current: %d\n", desired_charge_current);
            max17055_show_values("---> System Desired Charging Current", desired_charge_current);
        }




         printk("------------------------------------------------\n");
        k_sleep(K_MSEC(10000));


    }
}


static int max17055_init(const struct device *dev) {

    // get device and ensure it is bound
    dev = device_get_binding(DT_LABEL(DT_INST(0, maxim_max17055)));

	if (!dev) {

        printk("---> No device \"%s\" found; did initialization fail?\n", "max17055");
        return 0;

    }

	printk("---> Device is %p, name is %s\n", dev, dev->name);
  
    getSensorData(dev);

    return 0;
}

SYS_INIT(max17055_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

/* Current cell voltage in units of 1.25/16mV */
//uint16_t voltage;
/* Average current in units of 1.5625uV / Rsense */
//int16_t avg_current;
/* Remaining capacity as a %age */
//uint16_t state_of_charge;
/* Internal temperature in units of 1/256 degrees C */
//int16_t internal_temp;
/* Full charge capacity in 5/Rsense uA */
//uint16_t full_cap;
/* Remaining capacity in 5/Rsense uA */
//uint16_t remaining_cap;
/* Time to empty in seconds */
//uint16_t time_to_empty;
/* Time to full in seconds */
//uint16_t time_to_full;
/* Cycle count in 1/100ths (number of charge/discharge cycles) */
//uint16_t cycle_count;
/* Design capacity in 5/Rsense uA */
//uint16_t design_cap;