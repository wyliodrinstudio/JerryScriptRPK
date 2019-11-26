#include <string.h>
#include <stdlib.h>
#include "jerryscript.h"
#include "rgb_led.h"
#include "ui_manager.h"
#include "GUI.h"
#include "library.h"
#include "display.h"
#include "ambient_light.h"
#include "air_quality.h"
#include "pressure.h"
#include "temperature.h"
#include "ble.h"

char GUI_SETUP = 0;

extern char *src;

char * getString (const jerry_value_t string_value)
{
    char *s = NULL;
    jerry_value_t str_val = jerry_value_to_string (string_value);
    jerry_size_t string_size = jerry_get_string_size (str_val);
	s = (char*)malloc (string_size+1);
	if (s!=NULL)
	{
		int n = jerry_substring_to_char_buffer(str_val, 0, string_size, (jerry_char_t*)s, string_size);
		s[n] = '\0';
	}

    jerry_release_value(str_val);
    return s;
}

jerry_value_t jerryx_handler_register_global (const jerry_char_t *name_p, /**< name of the function */
                                jerry_external_handler_t handler_p) /**< function callback */
{
  jerry_value_t global_obj_val = jerry_get_global_object ();
  jerry_value_t function_name_val = jerry_create_string (name_p);
  jerry_value_t function_val = jerry_create_external_function (handler_p);

  jerry_value_t result_val = jerry_set_property (global_obj_val, function_name_val, function_val);

  jerry_release_value (function_val);
  jerry_release_value (function_name_val);
  jerry_release_value (global_obj_val);

  return result_val;
} /* jerryx_handler_register_global */

jerry_value_t jerryx_handler_require (const jerry_value_t func_obj_val, /**< function object */
                       const jerry_value_t this_p, /**< this arg */
                       const jerry_value_t args_p[], /**< function arguments */
                       const jerry_length_t args_cnt) /**< number of function arguments */
{
	char *library_name = NULL;
    jerry_value_t ret_val = jerry_create_undefined ();
    //GUI_DispStringHCenterAt("require", 50, 50);
    if (args_cnt > 0)
    {
    	if (jerry_value_is_string(args_p[0]))
    	{
    		library_name = getString (args_p[0]);
    		if (library_name != NULL)
    		{
    			if (strncmp (library_name, "console", JERRY_MAX_STRING) == 0)
    			{
    				jerry_release_value(ret_val);
    				ret_val = setup_console ();
    			}
				if (strncmp (library_name, "RGB", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_RGB ();
				}
				if (strncmp (library_name, "GUI", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_GUI(GUI_SETUP);
    				GUI_SETUP = 1;
				}
				if (strncmp (library_name, "accelerometer", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_ACCELEROMETER ();
				}
				if (strncmp (library_name, "gyroscope", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_GYROSCOPE ();
				}
				if (strncmp (library_name, "battery", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_BATTERY ();
				}
				if (strncmp (library_name, "motion", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_MOTION ();
				}
				if (strncmp (library_name, "freeFall", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_FREEFALL ();
				}
				if (strncmp (library_name, "ambientLight", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_ambient_light();
				}
				if (strncmp (library_name, "airQuality", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_air_quality();
				}
				if (strncmp (library_name, "pressure", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_pressure();
				}
				if (strncmp (library_name, "temperature", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
    				ret_val = setup_temperature();
				}				
				if (strncmp (library_name, "buzzer", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
					ret_val = setup_BUZZER();
				}
				if (strncmp (library_name, "touchscreen", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
					ret_val = setup_TOUCH();
				}
				if (strncmp (library_name, "switches", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
					ret_val = setup_SWITCHES();
				}
				if (strncmp (library_name, "BLE", JERRY_MAX_STRING) == 0)
				{
					jerry_release_value(ret_val);
					ret_val = setup_BLE();
				}
				free (library_name);
    		}
    	}
    }
    return ret_val;
}

jerry_value_t jerryx_handler_sleep (const jerry_value_t func_obj_val, /**< function object */
                       const jerry_value_t this_p, /**< this arg */
                       const jerry_value_t args_p[], /**< function arguments */
                       const jerry_length_t args_cnt) /**< number of function arguments */
{
    jerry_value_t ret_val = jerry_create_undefined ();
    if (args_cnt > 0)
    {
    	int wait_time = jerry_get_number_value(args_p[0]);
		App_WaitMsec(wait_time);
	}
    return ret_val;
}

//extern char* src;

static jerry_value_t
vm_exec_stop_callback (void *user_p)
{
	if (src == NULL) {
		return jerry_create_undefined ();
	}

	return jerry_create_string ((const jerry_char_t *) "Abort script");

}

void jerry_setup ()
{

	jerry_init(JERRY_INIT_EMPTY);
	jerry_set_vm_exec_stop_callback (vm_exec_stop_callback, NULL, 1);

	jerry_value_t glob_obj_val = jerry_get_global_object ();

	jerryx_handler_register_global ((const jerry_char_t *) "require", jerryx_handler_require);
	jerryx_handler_register_global ((const jerry_char_t *) "sleep", jerryx_handler_sleep);

	jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) "console");
	jerry_value_t console = setup_console();
	jerry_release_value (jerry_set_property (glob_obj_val, prop_name, console));
	jerry_release_value (prop_name);
	jerry_release_value (console);
	jerry_release_value (glob_obj_val);
}

void jerry_unsetup ()
{
	jerry_cleanup ();
	GUI_SETUP = 0;
}

void jerry_execute (const char *source)
{
	jerry_release_value (jerry_eval (source, strlen (source) - 1, JERRY_PARSE_NO_OPTS));
}
