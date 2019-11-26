#ifndef POWER_H
#define POWER_H

#include "jerryscript.h"
#include "sensors.h"

jerry_value_t setup_BATTERY ();

static jerry_value_t
BATTERY_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt); /**< number of function arguments */

#endif
