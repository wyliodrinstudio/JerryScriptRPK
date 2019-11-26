#ifndef MOTION_H
#define MOTION_H

#include "jerryscript.h"
#include "sensors.h"

jerry_value_t setup_MOTION ();

static jerry_value_t
MOTION_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt); /**< number of function arguments */

#endif
