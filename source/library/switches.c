#include "jerryscript.h"
#include "board.h"
#include "GUI.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

gpio_pin_config_t gpio_input_cfg = {
    kGPIO_DigitalInput, 1,
};

char switches = 0;

void init_switches()
{
	if (switches == 0)
	{
		GPIO_PinInit(BOARD_INITPINS_USER_SW1_GPIO, BOARD_INITPINS_USER_SW1_GPIO_PIN, &gpio_input_cfg);
		GPIO_PinInit(BOARD_INITPINS_USER_SW2_GPIO, BOARD_INITPINS_USER_SW2_GPIO_PIN, &gpio_input_cfg);
		GPIO_PinInit(BOARD_INITPINS_USER_SW3_GPIO, BOARD_INITPINS_USER_SW3_GPIO_PIN, &gpio_input_cfg);
		GPIO_PinInit(BOARD_INITPINS_USER_SW4_GPIO, BOARD_INITPINS_USER_SW4_GPIO_PIN, &gpio_input_cfg);

		switches = 1;
	}
}

static jerry_value_t
SWITCHES_get_sensor_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
    jerry_value_t ret_val = jerry_create_undefined();

	if (GPIO_PinRead(BOARD_INITPINS_USER_SW1_GPIO, BOARD_INITPINS_USER_SW1_GPIO_PIN) == 0U)
	{
		jerry_release_value(ret_val);
		ret_val = jerry_create_number(1);
	}
	if (GPIO_PinRead(BOARD_INITPINS_USER_SW2_GPIO, BOARD_INITPINS_USER_SW2_GPIO_PIN) == 0U)
	{
		jerry_release_value(ret_val);
		ret_val = jerry_create_number(2);
	}
	if (GPIO_PinRead(BOARD_INITPINS_USER_SW3_GPIO, BOARD_INITPINS_USER_SW3_GPIO_PIN) == 0U)
	{
		jerry_release_value(ret_val);
		ret_val = jerry_create_number(3);
	}
	if (GPIO_PinRead(BOARD_INITPINS_USER_SW4_GPIO, BOARD_INITPINS_USER_SW4_GPIO_PIN) == 0U)
	{
		jerry_release_value(ret_val);
		ret_val = jerry_create_number(4);
	}

    return ret_val;
}

jerry_value_t setup_SWITCHES ()
{
    
    jerry_value_t SWITCHES = -1;

    SWITCHES = jerry_create_undefined();

    if (jerry_value_is_undefined(SWITCHES))
	{
		// aici vine initializat LED-ul SWITCHES, daca merge, faci obiectul de js, altfel intorci undefined-ul

        init_switches();

        jerry_value_t object = jerry_create_object();
        if (!jerry_value_is_error(object))
        {
            jerry_release_value(SWITCHES);
            SWITCHES = object;

            jerry_value_t prop_name;
            jerry_value_t prop_value;
        /* printSensor */
        
            jerry_value_t get_sensor = jerry_create_external_function (SWITCHES_get_sensor_handler);
            prop_name = jerry_create_string ((const jerry_char_t *) "getValue");
            jerry_release_value (jerry_set_property (SWITCHES, prop_name, get_sensor));
            jerry_release_value (prop_name);
            jerry_release_value (get_sensor);

            prop_name = jerry_create_string ((const jerry_char_t *) "SW1");
            prop_value = jerry_create_number (1);
            jerry_release_value (jerry_set_property (SWITCHES, prop_name, prop_value));
            jerry_release_value (prop_name);
            jerry_release_value (prop_value);
        
            prop_name = jerry_create_string ((const jerry_char_t *) "SW2");
            prop_value = jerry_create_number (2);
            jerry_release_value (jerry_set_property (SWITCHES, prop_name, prop_value));
            jerry_release_value (prop_name);
            jerry_release_value (prop_value);

            prop_name = jerry_create_string ((const jerry_char_t *) "SW3");
            prop_value = jerry_create_number (3);
            jerry_release_value (jerry_set_property (SWITCHES, prop_name, prop_value));
            jerry_release_value (prop_name);
            jerry_release_value (prop_value);

            prop_name = jerry_create_string ((const jerry_char_t *) "SW4");
            prop_value = jerry_create_number (4);
            jerry_release_value (jerry_set_property (SWITCHES, prop_name, prop_value));
            jerry_release_value (prop_name);
            jerry_release_value (prop_value);
        }
    }

	return SWITCHES;
}
