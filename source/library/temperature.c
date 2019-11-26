#include "sensors.h"
#include "ambient_light.h"
#include "library.h"

char temp = 0;

void init_temp()
{
	if (temp == 0)
	{
		if(Init_air_humidity_temp() == 0)
		{
			temp = 1;
		}
	}
}

static jerry_value_t
temperature_get_value_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

    float temperature = 0;
    uint8_t temperature_size = sizeof(float);

    if (get_temperature((uint8_t *)&temperature, &temperature_size) ==  0)
    {
    	jerry_release_value (ret_val);
    	ret_val = jerry_create_number (temperature);
    }

	return ret_val;
}

jerry_value_t setup_temperature() {
	// TODO should be undefined
	jerry_value_t temperature = 0;

	temperature = jerry_create_undefined();

	if (jerry_value_is_undefined(temperature)) {

		init_temp();

		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object)) {
			//initial values

			jerry_release_value(temperature);
			temperature = object;

			jerry_value_t prop_name;

			/* get air temperature value */
			jerry_value_t getValue = jerry_create_external_function (temperature_get_value_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (temperature, prop_name, getValue));
			jerry_release_value (prop_name);
			jerry_release_value (getValue);
		}
	}

	return temperature;
}
