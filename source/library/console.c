#include "library.h"
#include "GUI.h"
#include <stdlib.h>
#include "ble_shell.h"

extern void* ioBase;

// console
/* console.error */
static jerry_value_t
console_error_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	//RGB_Led_Set_State(3, 0);
	GUI_DispStringHCenterAt("error", 88, 50);
	return jerry_create_undefined();
}

/* console.log */
static jerry_value_t
console_log_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	if (args_cnt > 0)
	{
		jerry_value_t str_val;
		if (jerry_value_is_symbol (args_p[0]))
		{
			str_val = jerry_get_symbol_descriptive_string (args_p[0]);
		} else {
			str_val = jerry_acquire_value (args_p[0]);
		}

		char * str = getString(str_val);

		if (str != NULL)
		{
			unsigned char *s = strdup ("\n\r");
			USB_VcomWriteBlocking(ioBase, (unsigned char *) str, strlen(str));
			USB_VcomWriteBlocking(ioBase, (unsigned char *) s, strlen (s));
			free (s);
		}
		jerry_release_value (str_val);
	}

	return jerry_create_undefined();
}

/* console.read */
static jerry_value_t
console_read_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	unsigned char *ch = (unsigned char *) calloc(2, sizeof(unsigned char));
	int size = 1;

	USB_VcomReadBlocking(ioBase, ch, size);

	jerry_value_t ret_val = jerry_create_string((const jerry_char_t *) ch);

	free(ch);

	return ret_val;
}

jerry_value_t setup_console ()
{
	// TODO should be undefined
	jerry_value_t console = -1;

	console = jerry_create_undefined();

	if (jerry_value_is_undefined(console))
	{
		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(console);
			console = object;

			jerry_value_t prop_name;

			/* log */
			jerry_value_t log = jerry_create_external_function (console_log_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "log");
			jerry_release_value (jerry_set_property (console, prop_name, log));
			jerry_release_value (prop_name);
			jerry_release_value (log);

			/* error */
			jerry_value_t error = jerry_create_external_function (console_error_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "error");
			jerry_release_value (jerry_set_property (console, prop_name, error));
			jerry_release_value (prop_name);
			jerry_release_value (error);

			/* read */
			jerry_value_t read = jerry_create_external_function (console_read_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "read");
			jerry_release_value (jerry_set_property (console, prop_name, read));
			jerry_release_value (prop_name);
			jerry_release_value (read);
		}
	}
	return console;
}
