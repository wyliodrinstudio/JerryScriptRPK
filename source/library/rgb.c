#include "rgb_led.h"
#include <stdbool.h>
#include "board.h"
#include "jerryscript.h"

char rgb = 0;

void init_rgb()
{
	if (rgb == 0)
	{
		if (Init_rpk_rgb_led() == 0)
		{
			rgb = 1;
		}
	}
}

// astea ar trebui sa fie declarate statice, nu externe. Daca pui extern, inseamna ca le iei de undeva
static uint8_t currentBrightness = -1;
static uint8_t currentColor = -1;

static jerry_value_t
RGB_get_brightness_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();
	if (currentBrightness != -1)
	{
		jerry_release_value(ret_val);
		ret_val = jerry_create_number(currentBrightness);
	}

	return ret_val;
}

static jerry_value_t
RGB_get_color_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();
	if (currentColor != -1)
	{
		jerry_release_value(ret_val);
		ret_val = jerry_create_number(currentColor);
	}

	return ret_val;
}

static jerry_value_t
RGB_set_brightness_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
   	jerry_value_t ret_val = jerry_create_undefined();

	uint8_t brightness;
   	if (args_cnt > 0)
   	{
	   brightness = jerry_get_number_value(args_p[0]);

	   if (RGB_Led_Set_State(brightness, currentColor) == 0)
	   {
		   currentBrightness = brightness;
	   }

	}
	else
   	{	
	
   	}
	return ret_val;
}

static jerry_value_t
RGB_set_color_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
   	jerry_value_t ret_val = jerry_create_undefined();

   	uint8_t color;
   	if (args_cnt > 0)
  	{
	   color = jerry_get_number_value(args_p[0]);

	   if (RGB_Led_Set_State(currentBrightness, color) == 0)
	   {
		   currentColor = color;
	   }
   }
   else
   {

   }
	return ret_val;
}

static jerry_value_t
RGB_set_state_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
    jerry_value_t ret_val = jerry_create_undefined();

    uint8_t brightness;
    uint8_t color;
    if (args_cnt == 2)
    {
        brightness = jerry_get_number_value(args_p[0]);
        color = jerry_get_number_value(args_p[1]);

        if (RGB_Led_Set_State(brightness, color) == 0)
        {
			currentBrightness = brightness;
			currentColor = color;
        }
	}
    else
    {

    }

	return ret_val;
}

jerry_value_t setup_RGB ()
{
	// TODO should be undefined
	jerry_value_t RGB = -1;

	RGB = jerry_create_undefined();

	if (jerry_value_is_undefined(RGB))
	{
		// aici vine initializat LED-ul RGB, daca merge, faci obiectul de js, altfel intorci undefined-ul
		init_rgb();

		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(RGB);
			RGB = object;

			jerry_value_t prop_name;
			jerry_value_t prop_value;

		/* getBrightness */
			jerry_value_t get_brightness = jerry_create_external_function (RGB_get_brightness_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getBrightness");
			jerry_release_value (jerry_set_property (RGB, prop_name, get_brightness));
			jerry_release_value (prop_name);
			jerry_release_value (get_brightness);

		/* getColor */
			jerry_value_t get_color = jerry_create_external_function (RGB_get_color_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getColor");
			jerry_release_value (jerry_set_property (RGB, prop_name, get_color));
			jerry_release_value (prop_name);
			jerry_release_value (get_color);

		/* setBrightness */
			jerry_value_t set_brightness = jerry_create_external_function (RGB_set_brightness_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "setBrightness");
			jerry_release_value (jerry_set_property (RGB, prop_name, set_brightness));
			jerry_release_value (prop_name);
			jerry_release_value (set_brightness);

		/* setColor */
			jerry_value_t set_color = jerry_create_external_function (RGB_set_color_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "setColor");
			jerry_release_value (jerry_set_property (RGB, prop_name, set_color));
			jerry_release_value (prop_name);
			jerry_release_value (set_color);

		/* setState */
			jerry_value_t set_state = jerry_create_external_function (RGB_set_state_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "setState");
			jerry_release_value (jerry_set_property (RGB, prop_name, set_state));
			jerry_release_value (prop_name);
			jerry_release_value (set_state);

			jerry_value_t color = jerry_create_object();
			if (!jerry_value_is_error(color)) {

				prop_name = jerry_create_string ((const jerry_char_t *) "RED");
				prop_value = jerry_create_number (0);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "GREEN");
				prop_value = jerry_create_number (1);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "BLUE");
				prop_value = jerry_create_number (2);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "WHITE");
				prop_value = jerry_create_number (3);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "YELLOW");
				prop_value = jerry_create_number (4);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "CYAN");
				prop_value = jerry_create_number (5);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "PURPLE");
				prop_value = jerry_create_number (6);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "BLACK");
				prop_value = jerry_create_number (7);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);
			}
			prop_name = jerry_create_string ((const jerry_char_t *) "color");
			jerry_release_value (jerry_set_property (RGB, prop_name, color));
			jerry_release_value (prop_name);
			jerry_release_value (color);

			jerry_value_t brightness = jerry_create_object();
			if (!jerry_value_is_error(brightness)) {

				prop_name = jerry_create_string ((const jerry_char_t *) "OFF");
				prop_value = jerry_create_number (0);
				jerry_release_value (jerry_set_property (brightness, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);
			
				prop_name = jerry_create_string ((const jerry_char_t *) "LOW");
				prop_value = jerry_create_number (1);
				jerry_release_value (jerry_set_property (brightness, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "MEDIUM");
				prop_value = jerry_create_number (2);
				jerry_release_value (jerry_set_property (brightness, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "HIGH");
				prop_value = jerry_create_number (3);
				jerry_release_value (jerry_set_property (brightness, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

			}
			prop_name = jerry_create_string ((const jerry_char_t *) "brightness");
			jerry_release_value (jerry_set_property (RGB, prop_name, brightness));
			jerry_release_value (prop_name);
			jerry_release_value (brightness);
		}
	}

	return RGB;
}
