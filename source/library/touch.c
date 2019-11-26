#include "jerryscript.h"
#include "sensors.h"
#include "sx9500.h"
#include "GUI.h"

#define kUiTouchDn (1U << 4U)                    /*!< Single touch on down pad */
#define kUiTouchRt (1U << 5U)                    /*!< Single touch on right pad */
#define kUiTouchUp (1U << 6U)                    /*!< Single touch on up pad */
#define kUiTouchLt (1U << 7U)                    /*!< Single touch on left pad */

char touch = 0;

void init_touch()
{
	if (touch == 0)
	{
		if (Init_touchpad() == 0)
		{
			touch = 1;
		}
	}
}

static jerry_value_t
TOUCH_get_value_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	RegStat_t dir;
	RegIrqSrc_t irq;
	dir.octet = 0;
	if (SX9500_Read_Irq(&irq.octet) == 0)
	{
		if (irq.bits.close || irq.bits.far)
		{

			SX9500_Read_Proximity_Sensors(&dir.octet);

			dir.bits.compstat = 0;

			switch(dir.octet)
			{
				case kUiTouchUp:
					dir.octet = kUiTouchUp;

					jerry_release_value(ret_val);
					ret_val = jerry_create_number(1);

					break;

				case kUiTouchDn:
					dir.octet = kUiTouchDn;

					jerry_release_value(ret_val);
					ret_val = jerry_create_number(2);

					break;

				case kUiTouchLt:
					dir.octet = kUiTouchLt;

					jerry_release_value(ret_val);
					ret_val = jerry_create_number(3);

					break;

				case kUiTouchRt:
					dir.octet = kUiTouchRt;

					jerry_release_value(ret_val);
					ret_val = jerry_create_number(4);

					break;

				default:
					break;
			};
		}
	}
    return ret_val;
}

jerry_value_t setup_TOUCH ()
{
	jerry_value_t TOUCH = -1;

	TOUCH = jerry_create_undefined();

	if (jerry_value_is_undefined(TOUCH))
	{
		init_touch();

		jerry_release_value(TOUCH);
		TOUCH = jerry_create_object();
		if (!jerry_value_is_error(TOUCH))
		{
			jerry_value_t prop_name;
			jerry_value_t prop_value;
			/* get air TOUCH value */
			jerry_value_t val = jerry_create_external_function (TOUCH_get_value_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
			jerry_release_value (jerry_set_property (TOUCH, prop_name, val));
			jerry_release_value (prop_name);
			jerry_release_value (val);

			prop_name = jerry_create_string ((const jerry_char_t *) "UP");
			prop_value = jerry_create_number (1);
			jerry_release_value (jerry_set_property (TOUCH, prop_name, prop_value));
			jerry_release_value (prop_name);
			jerry_release_value (prop_value);

			prop_name = jerry_create_string ((const jerry_char_t *) "DOWN");
			prop_value = jerry_create_number (2);
			jerry_release_value (jerry_set_property (TOUCH, prop_name, prop_value));
			jerry_release_value (prop_name);
			jerry_release_value (prop_value);

			prop_name = jerry_create_string ((const jerry_char_t *) "LEFT");
			prop_value = jerry_create_number (3);
			jerry_release_value (jerry_set_property (TOUCH, prop_name, prop_value));
			jerry_release_value (prop_name);
			jerry_release_value (prop_value);

			prop_name = jerry_create_string ((const jerry_char_t *) "RIGHT");
			prop_value = jerry_create_number (4);
			jerry_release_value (jerry_set_property (TOUCH, prop_name, prop_value));
			jerry_release_value (prop_name);
			jerry_release_value (prop_value);

		}
	}

	return TOUCH;
}
