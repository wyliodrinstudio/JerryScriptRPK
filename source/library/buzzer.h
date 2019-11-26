#ifndef BUZZER_H
#define BUZZER_H

#include "jerryscript.h"

static jerry_value_t
BUZZER_set_state_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt); /**< number of function arguments */

jerry_value_t setup_BUZZER();

#endif
