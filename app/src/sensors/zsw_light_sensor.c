/*
 * This file is part of ZSWatch project <https://github.com/jakkra/ZSWatch/>.
 * Copyright (c) 2023 Jakob Krantz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#include "sensors/zsw_light_sensor.h"

static const struct device *const apds9306 = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(apds9306));

int zsw_light_sensor_fetch(float *light)
{
    struct sensor_value light_sensor_val;

    if ((!device_is_ready(apds9306))) {
        return -ENODEV;
    }

    if (sensor_sample_fetch(apds9306) != 0) {
        return -ENODATA;
    }

    sensor_channel_get(apds9306, SENSOR_CHAN_LIGHT, &light_sensor_val);
    *light = sensor_value_to_float(&light_sensor_val);

    return 0;
}