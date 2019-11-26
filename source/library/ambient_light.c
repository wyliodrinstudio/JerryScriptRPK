#include "sensors.h"
#include "ambient_light.h"
#include "library.h"

char light = 0;

void init_light()
{
	if (light == 0)
	{
		if (Init_ambient_light() == 0)
		{
			light = 1;
		}
	}
}

static jerry_value_t
ambient_light_get_value_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	float ambient_light = 0;
	uint8_t ambient_light_size = sizeof(float);

	if (get_ambient_light((uint8_t*) &ambient_light, &ambient_light_size) == 0) {
		jerry_release_value (ret_val);
		ret_val = jerry_create_number (ambient_light);
	}

	return ret_val;
}

jerry_value_t setup_ambient_light() {
	// TODO should be undefined
	jerry_value_t ambient_light = 0;

	ambient_light = jerry_create_undefined();

	if (jerry_value_is_undefined(ambient_light)) {

		init_light();

		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object)) {
			//initial values

			jerry_release_value(ambient_light);
			ambient_light = object;

			jerry_value_t prop_name;

			/* get ambient light value */
			jerry_value_t getValue = jerry_create_external_function (ambient_light_get_value_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (ambient_light, prop_name, getValue));
			jerry_release_value (prop_name);
			jerry_release_value (getValue);

		}
	}

	return ambient_light;
}
