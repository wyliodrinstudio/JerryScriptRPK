#include "jerryscript.h"
#include "sensors.h"
#include "fxos8700.h"
#include "FunctionLib.h"
#include <math.h>

char sens =  0;

void init_sens ()
{
	if (sens == 0)
	{
		if (Init_accel_mag() == 0)
		{
			sens = 1;
		}
	}
}

static jerry_value_t
ACCELEROMETER_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

    float AccelerometerValue[3] = {0};
    int AccelerometerSize = 3 * sizeof(float);

    // jerry_value_t object = jerry_create_object();

    if (get_acceleration((uint8_t *)AccelerometerValue, &AccelerometerSize) == 0)
    {
        jerry_value_t ACCELEROMETER = jerry_create_object();
        if (!jerry_value_is_error(ACCELEROMETER))
        {
            jerry_value_t prop_name;

        /* printSensor */

            jerry_value_t x = jerry_create_number(ceil(AccelerometerValue[0]*1000)/1000);
            jerry_value_t y = jerry_create_number(ceil(AccelerometerValue[1]*1000)/1000);
            jerry_value_t z = jerry_create_number(ceil(AccelerometerValue[2]*1000)/1000);
            
            
            prop_name = jerry_create_string ((const jerry_char_t *) "x");
            jerry_release_value (jerry_set_property (ACCELEROMETER, prop_name, x));
            jerry_release_value (prop_name);
            jerry_release_value (x);

            prop_name = jerry_create_string ((const jerry_char_t *) "y");
            jerry_release_value (jerry_set_property (ACCELEROMETER, prop_name, y));
            jerry_release_value (prop_name);
            jerry_release_value (y);
            
            prop_name = jerry_create_string ((const jerry_char_t *) "z");
            jerry_release_value (jerry_set_property (ACCELEROMETER, prop_name, z));
            jerry_release_value (z);
            jerry_release_value (prop_name);
            
            jerry_release_value (ret_val);
            ret_val = ACCELEROMETER;
        }
    }
    return ret_val;
}

jerry_value_t setup_ACCELEROMETER ()
{
	// TODO should be undefined
	jerry_value_t ACCELEROMETER = -1;

	ACCELEROMETER = jerry_create_undefined();

	if (jerry_value_is_undefined(ACCELEROMETER))
	{
	    init_sens ();
		// aici vine initializat LED-ul ACCELEROMETER, daca merge, faci obiectul de js, altfel intorci undefined-ul

	    jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(ACCELEROMETER);
			ACCELEROMETER = object;

			jerry_value_t prop_name;

		/* printSensor */

			jerry_value_t get_sensor = jerry_create_external_function (ACCELEROMETER_get_sensor_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (ACCELEROMETER, prop_name, get_sensor));
			jerry_release_value (prop_name);
			jerry_release_value (get_sensor);
		}

	}
	return ACCELEROMETER;
}
