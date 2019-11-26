#include "library.h"
#include "ble_shell.h"

extern hValueBLEWyliodrinProtocol1byte;
extern hValueBLEWyliodrinProtocol2bytes;
extern hValueBLEWyliodrinProtocol4bytes;


volatile int int8_ble_var;
volatile int int16_ble_var;
volatile int int32_ble_var;

static jerry_value_t
ble_write_int8_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	if (args_cnt > 0) {
        int nr = jerry_get_number_value(args_p[0]);
        nr &= 0xFF;

        int8_ble_var = nr;

        uint8_t *value = calloc(1, sizeof(uint8_t));
        value[0] = nr;

        BleApp_Notify(hValueBLEWyliodrinProtocol1byte, value, 1);
        free(value);

        App_WaitMsec(150);
    }

    return jerry_create_undefined();
}

static jerry_value_t
ble_write_int16_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	if (args_cnt > 0) {
        int nr = jerry_get_number_value(args_p[0]);
        nr &= 0xFFFF;

        int16_ble_var = nr;

        uint8_t *value = calloc(2, sizeof(uint8_t));
        value[0] = nr >> 8;
        value[1] = nr;

        BleApp_Notify(hValueBLEWyliodrinProtocol2bytes, value, 2);
        free(value);

        App_WaitMsec(150);
    }

    return jerry_create_undefined();
}

static jerry_value_t
ble_write_int32_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	if (args_cnt > 0) {
        int nr = jerry_get_number_value(args_p[0]);

        int32_ble_var = nr;

        uint8_t *value = calloc(4, sizeof(uint8_t));
        value[3] = nr;
        value[2] = nr >> 8;
        value[1] = nr >> 16;
        value[0] = nr >> 24;

        BleApp_Notify(hValueBLEWyliodrinProtocol4bytes, value, 4);
        free(value);

        App_WaitMsec(150);
    }

    return jerry_create_undefined();
}

static jerry_value_t
ble_read_int8_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_number (int8_ble_var);

    return ret_val;
}

static jerry_value_t
ble_read_int16_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_number (int16_ble_var);

    return ret_val;
}

static jerry_value_t
ble_read_int32_handler (const jerry_value_t func_value, /**< function object */
                 const jerry_value_t this_value, /**< this arg */
                 const jerry_value_t *args_p, /**< function arguments */
                 const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_number (int32_ble_var);

    return ret_val;
}

jerry_value_t setup_BLE ()
{
	// TODO should be undefined
	jerry_value_t BLE = -1;

	BLE = jerry_create_undefined();

	if (jerry_value_is_undefined(BLE))
	{
		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object))
		{
			jerry_release_value(BLE);
			BLE = object;

			jerry_value_t prop_name;

			/* int8 */
			jerry_value_t wint8 = jerry_create_external_function (ble_write_int8_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "writeInt8");
			jerry_release_value (jerry_set_property (BLE, prop_name, wint8));
			jerry_release_value (prop_name);
			jerry_release_value (wint8);

            /* int16 */
			jerry_value_t wint16 = jerry_create_external_function (ble_write_int16_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "writeInt16");
			jerry_release_value (jerry_set_property (BLE, prop_name, wint16));
			jerry_release_value (prop_name);
			jerry_release_value (wint16);

            /* int32 */
			jerry_value_t wint32 = jerry_create_external_function (ble_write_int32_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "writeInt32");
			jerry_release_value (jerry_set_property (BLE, prop_name, wint32));
			jerry_release_value (prop_name);
			jerry_release_value (wint32);

            /* int8 */
			jerry_value_t rint8 = jerry_create_external_function (ble_read_int8_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "readInt8");
			jerry_release_value (jerry_set_property (BLE, prop_name, rint8));
			jerry_release_value (prop_name);
			jerry_release_value (rint8);

            /* int8 */
			jerry_value_t rint16 = jerry_create_external_function (ble_read_int16_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "readInt16");
			jerry_release_value (jerry_set_property (BLE, prop_name, rint16));
			jerry_release_value (prop_name);
			jerry_release_value (rint16);

            /* int32 */
			jerry_value_t rint32 = jerry_create_external_function (ble_read_int32_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "readInt32");
			jerry_release_value (jerry_set_property (BLE, prop_name, rint32));
			jerry_release_value (prop_name);
			jerry_release_value (rint32);
		}
	}
	return BLE;
}
