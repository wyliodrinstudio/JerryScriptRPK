#include "jerryscript.h"
#include "sensors.h"

char gyro =  0;

void init_gyro()
{
	if (gyro== 0)
	{
		if (Init_rotation_speed() == 0)
		{
			gyro = 1;
		}
	}
}

static jerry_value_t
GYROSCOPE_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

    int16_t GyroscopeValue[3]   = {0};
    uint8_t GyroscopeSize       = 6;

	if (get_rotation_speed((uint8_t *)GyroscopeValue, &GyroscopeSize) == 0)
    {

        jerry_value_t GYROSCOPE = jerry_create_object();

        if (!jerry_value_is_error(GYROSCOPE))
        {
            jerry_value_t prop_name;

        /* printSensor */
            

            jerry_value_t x = jerry_create_number(GyroscopeValue[0]);
            jerry_value_t y = jerry_create_number(GyroscopeValue[1]);
            jerry_value_t z = jerry_create_number(GyroscopeValue[2]);

            prop_name = jerry_create_string ((const jerry_char_t *) "x");
            jerry_release_value (jerry_set_property (GYROSCOPE, prop_name, x));
            jerry_release_value(x);
            jerry_release_value (prop_name);

            prop_name = jerry_create_string ((const jerry_char_t *) "y");
            jerry_release_value (jerry_set_property (GYROSCOPE, prop_name, y));
            jerry_release_value(y);
            jerry_release_value (prop_name);
            
            prop_name = jerry_create_string ((const jerry_char_t *) "z");
            jerry_release_value (jerry_set_property (GYROSCOPE, prop_name, z));
            jerry_release_value(z);
            jerry_release_value (prop_name);
            
            jerry_release_value(ret_val);
            ret_val = GYROSCOPE;
        }
    }
    return ret_val;
}

jerry_value_t setup_GYROSCOPE ()
{
	// TODO should be undefined
	jerry_value_t GYROSCOPE = -1;

	GYROSCOPE = jerry_create_undefined();

	if (jerry_value_is_undefined(GYROSCOPE))
	{
		init_gyro();
		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(GYROSCOPE);
			GYROSCOPE = object;

			jerry_value_t prop_name;

		/* getSensor */

			jerry_value_t get_sensor = jerry_create_external_function (GYROSCOPE_get_sensor_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (GYROSCOPE, prop_name, get_sensor));
			jerry_release_value (prop_name);
			jerry_release_value (get_sensor);

		}
	}

	return GYROSCOPE;
}
