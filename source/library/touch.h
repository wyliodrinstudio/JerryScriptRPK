#ifndef TOUCH_H
#define TOUCH_H

#include <stdint.h>
#include "jerryscript.h"

static jerry_value_t
TOUCH_get_value_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt); /**< number of function arguments */

jerry_value_t setup_TOUCH ();

#endif
