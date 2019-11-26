#include "sensors.h"
#include "ambient_light.h"
#include "library.h"

char air = 0;

void init_air()
{
	if (air == 0)
	{
		if (Init_air_quality() == 0)
		{
			air = 1;
		}
	}
}

static jerry_value_t
air_quality_get_value_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

    int air_quality = 0;
    uint8_t air_quality_size = sizeof(int);

    if (get_air_quality((uint8_t *)&air_quality, &air_quality_size) ==  0)
    {
    	jerry_release_value (ret_val);
    	ret_val = jerry_create_number (air_quality);
    }

	return ret_val;
}

jerry_value_t setup_air_quality() {
	// TODO should be undefined
	jerry_value_t air_quality = 0;

	air_quality = jerry_create_undefined();

	if (jerry_value_is_undefined(air_quality)) {
		init_air();
		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object)) {
			//initial values

			jerry_release_value(air_quality);
			air_quality = object;

			jerry_value_t prop_name;

			/* get air quality value */
			jerry_value_t getValue = jerry_create_external_function (air_quality_get_value_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (air_quality, prop_name, getValue));
			jerry_release_value (prop_name);
			jerry_release_value (getValue);
		}
	}

	return air_quality;
}
