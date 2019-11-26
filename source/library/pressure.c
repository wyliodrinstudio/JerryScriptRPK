#include "sensors.h"
#include "ambient_light.h"
#include "library.h"

char press = 0;

void init_press ()
{
	if (press == 0)
	{
		if (Init_pressure() == 0)
		{
			press = 1;
		}
	}
}
static jerry_value_t
pressure_get_value_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

    int pressure = 0;
    uint8_t pressure_size = sizeof(int);

    if (get_pressure((uint8_t *)&pressure, &pressure_size) ==  0)
    {
    	jerry_release_value (ret_val);
    	ret_val = jerry_create_number (pressure);
    }

	return ret_val;
}

jerry_value_t setup_pressure() {
	// TODO should be undefined
	jerry_value_t pressure = 0;

	pressure = jerry_create_undefined();

	if (jerry_value_is_undefined(pressure)) {

		init_press();
		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object)) {
			//initial values

			jerry_release_value(pressure);
			pressure = object;

			jerry_value_t prop_name;

			/* get pressure value */
			jerry_value_t getValue = jerry_create_external_function (pressure_get_value_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (pressure, prop_name, getValue));
			jerry_release_value (prop_name);
			jerry_release_value (getValue);
		}
	}

	return pressure;
}
