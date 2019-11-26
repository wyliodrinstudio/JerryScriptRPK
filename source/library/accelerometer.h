#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "jerryscript.h"
#include "sensors.h"

jerry_value_t setup_ACCELEROMETER ();

static jerry_value_t
ACCELEROMETER_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt); /**< number of function arguments */

#endif
