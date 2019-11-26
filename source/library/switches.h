#ifndef SWITCHES_H
#define SWITCHES_H

#include "jerryscript.h"

static jerry_value_t
SWITCHES_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt); /**< number of function arguments */

jerry_value_t setup_SWITCHES();

#endif