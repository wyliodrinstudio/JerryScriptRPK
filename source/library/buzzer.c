#include "board.h"
#include "buzzer.h"

static int buzzState = 0;

static jerry_value_t
BUZZER_get_state_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	jerry_release_value(ret_val);
	ret_val = jerry_create_number(buzzState);

	return ret_val;
}

static jerry_value_t
BUZZER_set_state_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 0) {
        int state = jerry_get_number_value(args_p[0]);

        if (state == 0)
        {
            BUZZER_OFF;
            buzzState = 0;
        }
        else
        {
            BUZZER_ON;
            buzzState = 1;
        }
	}

	return ret_val;
}

jerry_value_t setup_BUZZER ()
{
	// TODO should be undefined
	jerry_value_t BUZZER = -1;
	BUZZER = jerry_create_undefined();
	if (jerry_value_is_undefined(BUZZER))
	{
    
        jerry_value_t object = jerry_create_object();
        if (!jerry_value_is_error(object))
        {
            jerry_release_value(BUZZER);
            BUZZER = object;

            jerry_value_t prop_name;
            jerry_value_t prop_value;
            
        /* printSensor */
        
            jerry_value_t set_state = jerry_create_external_function (BUZZER_set_state_handler);
            prop_name = jerry_create_string ((const jerry_char_t *) "setState");
            jerry_release_value (jerry_set_property (BUZZER, prop_name, set_state));
            jerry_release_value (prop_name);
            jerry_release_value (set_state);

            jerry_value_t get_state = jerry_create_external_function (BUZZER_get_state_handler);
            prop_name = jerry_create_string ((const jerry_char_t *) "getState");
            jerry_release_value (jerry_set_property (BUZZER, prop_name, get_state));
            jerry_release_value (prop_name);
            jerry_release_value (get_state);

            prop_name = jerry_create_string ((const jerry_char_t *) "OFF");
            prop_value = jerry_create_number (0);
            jerry_release_value (jerry_set_property (BUZZER, prop_name, prop_value));
            jerry_release_value (prop_name);
            jerry_release_value (prop_value);

            prop_name = jerry_create_string ((const jerry_char_t *) "ON");
            prop_value = jerry_create_number (1);
            jerry_release_value (jerry_set_property (BUZZER, prop_name, prop_value));
            jerry_release_value (prop_name);
            jerry_release_value (prop_value);
        }

	}
	return BUZZER;
}

