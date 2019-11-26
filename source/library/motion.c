#include "jerryscript.h"
#include "sensors.h"
#include "fxos8700.h"
#include "FunctionLib.h"

char motion = 0;

void init_motion()
{
	if (motion == 0)
	{
		if (Init_MotionDetect() == 0)
		{
			motion = 1;
		}
	}
}

static jerry_value_t
MOTION_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
    jerry_value_t ret_val = jerry_create_undefined();
	jerry_value_t motions = jerry_create_number(motion_detected());

	if (!jerry_value_is_error(motions))
	{
		jerry_release_value(ret_val);
		ret_val = motions;
	}
	jerry_release_value(motions);
    return ret_val;
}

jerry_value_t setup_MOTION ()
{
	// TODO should be undefined
	jerry_value_t MOTION = -1;

	MOTION = jerry_create_undefined();

	if (jerry_value_is_undefined(MOTION))
	{
		//init_motion();
		if (Init_MotionDetect() == 0)
		{
			jerry_value_t object = jerry_create_object();
			if (!jerry_value_is_error(object))
			{
				jerry_release_value(MOTION);
				MOTION = object;

				jerry_value_t prop_name;

			/* printSensor */

				jerry_value_t get_sensor = jerry_create_external_function (MOTION_get_sensor_handler);
				prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
				jerry_release_value (jerry_set_property (MOTION, prop_name, get_sensor));
				jerry_release_value (prop_name);
				jerry_release_value (get_sensor);
			}
		}
	}

	return MOTION;
}
