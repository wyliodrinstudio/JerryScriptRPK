#include "jerryscript.h"
#include "sensors.h"
#include "fxos8700.h"
#include "FunctionLib.h"

char fall = 0;

void init_fall()
{
	if (fall == 0)
	{
		if (Init_FreefallDetect() == 0)
		{
			fall = 1;
		}
	}
}

static jerry_value_t
FREEFALL_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();
	jerry_value_t freeFall = jerry_create_number(freefall_detected());

	if (!jerry_value_is_error(freeFall))
	{
		jerry_release_value(ret_val);
		ret_val = freeFall;
	}
	jerry_release_value(freeFall);
    return ret_val;
}

jerry_value_t setup_FREEFALL ()
{
	// TODO should be undefined
	jerry_value_t FREEFALL = -1;

	FREEFALL = jerry_create_undefined();

	if (jerry_value_is_undefined(FREEFALL))
	{

		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(FREEFALL);
			FREEFALL = object;

			jerry_value_t prop_name;

		/* printSensor */

			jerry_value_t get_sensor = jerry_create_external_function (FREEFALL_get_sensor_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (FREEFALL, prop_name, get_sensor));
			jerry_release_value (prop_name);
			jerry_release_value (get_sensor);
		}
	}

	return FREEFALL;
}
