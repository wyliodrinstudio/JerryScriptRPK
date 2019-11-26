#include "jerryscript.h"
#include "sensors.h"
#include "fxos8700.h"
#include "FunctionLib.h"

char power = 0;

void init_pow()
{
	if (power == 0) {
		if (Init_battery_sensor() == 0)
		{
			power = 1;
		}
	}

}
static jerry_value_t
BATTERY_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
    jerry_value_t BATTERY = jerry_create_object();

    uint8_t batPercentLevel;
    uint8_t batChargingState;

    if (BatterySensor_GetState(&batPercentLevel, &batChargingState) == 0)
    {
    
        if(!jerry_value_is_error(BATTERY))
        {
            jerry_value_t prop_name;

            jerry_value_t percentage = jerry_create_number(batPercentLevel);

            jerry_value_t state = jerry_create_number(batChargingState);

            prop_name = jerry_create_string ((const jerry_char_t *) "percentage");
            jerry_release_value (jerry_set_property (BATTERY, prop_name, percentage));
            jerry_release_value (prop_name);
            jerry_release_value (percentage);

            prop_name = jerry_create_string ((const jerry_char_t *) "state");
            jerry_release_value (jerry_set_property (BATTERY, prop_name, state));
            jerry_release_value (prop_name);
            jerry_release_value (state);

        }

    }
    return BATTERY;
}

jerry_value_t setup_BATTERY ()
{
	// TODO should be undefined
	jerry_value_t BATTERY = -1;
	BATTERY = jerry_create_undefined();
	if (jerry_value_is_undefined(BATTERY))
	{
		init_pow();
		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(BATTERY);
			BATTERY = object;

			jerry_value_t prop_name;

		/* printSensor */

			jerry_value_t get_sensor = jerry_create_external_function (BATTERY_get_sensor_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (BATTERY, prop_name, get_sensor));
			jerry_release_value (prop_name);
			jerry_release_value (get_sensor);
		}
	}

	return BATTERY;
}
