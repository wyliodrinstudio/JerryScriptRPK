#include "GUI.h"
#include "board.h"
#include "display.h"
#include "backlight.h"
#include "library.h"

char display = 0;

void init_display()
{
	if (display == 0)
	{
		Display_Connect();
		Init_backlight();
		display = 1;
	}
}

static jerry_value_t
GUI_display_clear_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	GUI_Clear();

	return ret_val;
}

static jerry_value_t
GUI_display_new_line_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	GUI_DispNextLine();

	return ret_val;
}

static jerry_value_t
GUI_display_string_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 0) {
		jerry_value_t str_val;
		
		if (jerry_value_is_symbol (args_p[0]))
		{
			str_val = jerry_get_symbol_descriptive_string(args_p[0]);
		}
		else if (jerry_value_is_boolean(args_p[0]))
		{
			str_val = jerry_get_boolean_value(args_p[0]);
		} 
		else
		{
			str_val = jerry_acquire_value(args_p[0]);
		}
		
		char* s = getString(str_val);

		if (s != NULL)
		{
			GUI_DispString(s);
			free(s);
		}
		
		jerry_release_value(str_val);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_string_at_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 2) {
		jerry_value_t str_val;
		
		if (jerry_value_is_symbol (args_p[0]))
		{
			str_val = jerry_get_symbol_descriptive_string(args_p[0]);
		}
		else if (jerry_value_is_boolean(args_p[0]))
		{
			str_val = jerry_get_boolean_value(args_p[0]);
		} 
		else
		{
			str_val = jerry_acquire_value(args_p[0]);
		}

		char* s = getString(str_val);
		int x = jerry_get_number_value(args_p[1]);
		int y = jerry_get_number_value(args_p[2]);

		if (s != NULL) 
		{
			GUI_DispStringAt(s, x, y);
			free(s);
		}
		
		jerry_release_value(str_val);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_line_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 3) {
		int x0 = jerry_get_number_value(args_p[0]);
		int y0 = jerry_get_number_value(args_p[1]);
		int x1 = jerry_get_number_value(args_p[2]);
		int y1 = jerry_get_number_value(args_p[3]);

		GUI_DrawLine(x0, y0, x1, y1);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_point_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 1) {
		int x = jerry_get_number_value(args_p[0]);
		int y = jerry_get_number_value(args_p[1]);
		GUI_DrawPoint(x, y);
	}

	return ret_val;
}


static jerry_value_t
GUI_display_draw_v_line_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 2) {
		int x0 = jerry_get_number_value(args_p[0]);
		int y0 = jerry_get_number_value(args_p[1]);
		int x1 = jerry_get_number_value(args_p[2]);

		GUI_DrawVLine(x0, y0, x1);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_h_line_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 2) {
		int x0 = jerry_get_number_value(args_p[0]);
		int y0 = jerry_get_number_value(args_p[1]);
		int x1 = jerry_get_number_value(args_p[2]);

		GUI_DrawHLine(x0, y0, x1);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_rect_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 3) {
		int x0 = jerry_get_number_value(args_p[0]);
		int y0 = jerry_get_number_value(args_p[1]);
		int x1 = jerry_get_number_value(args_p[2]);
		int y1 = jerry_get_number_value(args_p[3]);

		GUI_DrawRect(x0, y0, x1, y1);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_fill_rect_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 3) {
		int x0 = jerry_get_number_value(args_p[0]);
		int y0 = jerry_get_number_value(args_p[1]);
		int x1 = jerry_get_number_value(args_p[2]);
		int y1 = jerry_get_number_value(args_p[3]);

		GUI_FillRect(x0, y0, x1, y1);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_circle_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 2) {
		int x = jerry_get_number_value(args_p[0]);
		int y = jerry_get_number_value(args_p[1]);
		int r = jerry_get_number_value(args_p[2]);

		GUI_DrawCircle(x, y, r);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_fill_circle_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 2) {
		int x = jerry_get_number_value(args_p[0]);
		int y = jerry_get_number_value(args_p[1]);
		int r = jerry_get_number_value(args_p[2]);

		GUI_FillCircle(x, y, r);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_ellipse_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 3) {
		int x = jerry_get_number_value(args_p[0]);
		int y = jerry_get_number_value(args_p[1]);
		int rx = jerry_get_number_value(args_p[2]);
		int ry = jerry_get_number_value(args_p[3]);

		GUI_DrawEllipse(x, y, rx, ry);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_fill_ellipse_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 3) {
		int x = jerry_get_number_value(args_p[0]);
		int y = jerry_get_number_value(args_p[1]);
		int rx = jerry_get_number_value(args_p[2]);
		int ry = jerry_get_number_value(args_p[3]);

		GUI_FillEllipse(x, y, rx, ry);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_set_bk_color_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 0) {
		int colorIndex = jerry_get_number_value(args_p[0]);

		GUI_SetBkColor(GUI_MAKE_COLOR(colorIndex));
	}

	return ret_val;
}

static jerry_value_t
GUI_display_set_backlight_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 0) {
		int backlight = jerry_get_number_value(args_p[0]);

		Backlight_SetLevel(backlight);
	}

	return ret_val;
}

static jerry_value_t
GUI_display_set_color_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt > 0) {
		int colorIndex = jerry_get_number_value(args_p[0]);

		GUI_SetColor(GUI_MAKE_COLOR(colorIndex));
	}

	return ret_val;
}

static jerry_value_t
GUI_display_draw_arrow_handler (const jerry_value_t func_value, /**< function object */
                const jerry_value_t this_value, /**< this arg */
                const jerry_value_t *args_p, /**< function arguments */
                const jerry_length_t args_cnt) /**< number of function arguments */
{
	jerry_value_t ret_val = jerry_create_undefined();

	if (args_cnt == 1)
	{
		if (jerry_get_number_value(args_p[0]) == 1)
		{
			GUI_POINT gSourceArrow[3] = {{20, 10}, {0, 10}, {10, 0}};
			GUI_POINT upsideArrowPoints[3];
			GUI_RotatePolygon(upsideArrowPoints, gSourceArrow, 3, 0);
			GUI_FillPolygon(upsideArrowPoints, 3, 75, 5);
		}
		if (jerry_get_number_value(args_p[0]) == 2)
		{
			GUI_POINT gSourceArrow[3] = {{20, 10}, {0, 10}, {10, 0}};
			GUI_POINT downsideArrowPoints[3];
			GUI_RotatePolygon(downsideArrowPoints, gSourceArrow, 3, 2*1.5707963268);
			GUI_FillPolygon(downsideArrowPoints, 3, 95, 170);
		}
		if (jerry_get_number_value(args_p[0]) == 3)
		{
			GUI_POINT gSourceArrow[3] = {{20, 10}, {0, 10}, {10, 0}};
			GUI_POINT leftArrowPoints[3];
			GUI_RotatePolygon(leftArrowPoints, gSourceArrow, 3, 1.5707963268);
			GUI_FillPolygon(leftArrowPoints, 3, 5, 95);
		}
		if (jerry_get_number_value(args_p[0]) == 4)
		{
			GUI_POINT gSourceArrow[3] = {{20, 10}, {0, 10}, {10, 0}};
			GUI_POINT rightArrowPoints[3];
			GUI_RotatePolygon(rightArrowPoints, gSourceArrow, 3, -1.5707963268);
			GUI_FillPolygon(rightArrowPoints, 3, 170, 75);
		}
	}

	return ret_val;
}

jerry_value_t setup_GUI(char setup) {
	// TODO should be undefined
	static jerry_value_t GUI = -1;

	if (setup == 0) GUI = jerry_create_undefined();

	if (jerry_value_is_undefined(GUI)) {

		init_display();

		jerry_value_t object = jerry_create_object();
		if (!jerry_value_is_error(object)) {
			//initial values
			Backlight_SetLevel(BLIGHT_LEVEL_HIGH);
			GUI_SetBkColor(GUI_BLACK);
			GUI_SetColor(GUI_WHITE);

			jerry_release_value(GUI);
			GUI = object;

			jerry_value_t prop_name;
			jerry_value_t prop_value;

			/* display clear */
			jerry_value_t displayClear = jerry_create_external_function (GUI_display_clear_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "displayClear");
			jerry_release_value (jerry_set_property (GUI, prop_name, displayClear));
			jerry_release_value (prop_name);
			jerry_release_value (displayClear);

			/* new line */
			jerry_value_t displayNewLine = jerry_create_external_function (GUI_display_new_line_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "displayNewLine");
			jerry_release_value (jerry_set_property (GUI, prop_name, displayNewLine));
			jerry_release_value (prop_name);
			jerry_release_value (displayNewLine);

			/* display string */
			jerry_value_t displayString = jerry_create_external_function (GUI_display_string_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "displayString");
			jerry_release_value (jerry_set_property (GUI, prop_name, displayString));
			jerry_release_value (prop_name);
			jerry_release_value (displayString);

			/* display string at */
			jerry_value_t displayStringAt = jerry_create_external_function (GUI_display_string_at_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "displayStringAt");
			jerry_release_value (jerry_set_property (GUI, prop_name, displayStringAt));
			jerry_release_value (prop_name);
			jerry_release_value (displayStringAt);

			/* display draw point */
			jerry_value_t drawPoint = jerry_create_external_function (GUI_display_draw_point_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawPoint");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawPoint));
			jerry_release_value (prop_name);
			jerry_release_value (drawPoint);

			/* display draw line */
			jerry_value_t drawLine = jerry_create_external_function (GUI_display_draw_line_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawLine");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawLine));
			jerry_release_value (prop_name);
			jerry_release_value (drawLine);

			/* display draw vertical line */
			jerry_value_t drawVLine = jerry_create_external_function (GUI_display_draw_v_line_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawVLine");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawVLine));
			jerry_release_value (prop_name);
			jerry_release_value (drawVLine);

			/* display draw horizontal line */
			jerry_value_t drawHLine = jerry_create_external_function (GUI_display_draw_h_line_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawHLine");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawHLine));
			jerry_release_value (prop_name);
			jerry_release_value (drawHLine);

			/* display draw rect */
			jerry_value_t drawRect = jerry_create_external_function (GUI_display_draw_rect_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawRect");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawRect));
			jerry_release_value (prop_name);
			jerry_release_value (drawRect);

			/* display fill rect */
			jerry_value_t fillRect = jerry_create_external_function (GUI_display_fill_rect_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "fillRect");
			jerry_release_value (jerry_set_property (GUI, prop_name, fillRect));
			jerry_release_value (prop_name);
			jerry_release_value (fillRect);

			/* display draw circle*/
			jerry_value_t drawCircle = jerry_create_external_function (GUI_display_draw_circle_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawCircle");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawCircle));
			jerry_release_value (prop_name);
			jerry_release_value (drawCircle);

			/* display fill circle*/
			jerry_value_t fillCircle = jerry_create_external_function (GUI_display_fill_circle_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "fillCircle");
			jerry_release_value (jerry_set_property (GUI, prop_name, fillCircle));
			jerry_release_value (prop_name);
			jerry_release_value (fillCircle);

			/* display draw ellipse*/
			jerry_value_t drawEllipse = jerry_create_external_function (GUI_display_draw_ellipse_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawEllipse");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawEllipse));
			jerry_release_value (prop_name);
			jerry_release_value (drawEllipse);

			/* display fill ellipse*/
			jerry_value_t fillEllipse = jerry_create_external_function (GUI_display_fill_ellipse_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "fillEllipse");
			jerry_release_value (jerry_set_property (GUI, prop_name, fillEllipse));
			jerry_release_value (prop_name);
			jerry_release_value (fillEllipse);

			/* display set background color*/
			jerry_value_t setBkColor = jerry_create_external_function (GUI_display_set_bk_color_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "setBkColor");
			jerry_release_value (jerry_set_property (GUI, prop_name, setBkColor));
			jerry_release_value (prop_name);
			jerry_release_value (setBkColor);

			/* display set color*/
			jerry_value_t setColor = jerry_create_external_function (GUI_display_set_color_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "setColor");
			jerry_release_value (jerry_set_property (GUI, prop_name, setColor));
			jerry_release_value (prop_name);
			jerry_release_value (setColor);

			/* display set backlight*/
			jerry_value_t setBacklight = jerry_create_external_function (GUI_display_set_backlight_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "setBacklight");
			jerry_release_value (jerry_set_property (GUI, prop_name, setBacklight));
			jerry_release_value (prop_name);
			jerry_release_value (setBacklight);

			/*gui properties */
			//color
			jerry_value_t color = jerry_create_object();
			if (!jerry_value_is_error(color)) {
				//GUI_BLUE
				prop_name = jerry_create_string ((const jerry_char_t *) "blue");
				prop_value = jerry_create_number (0x00FF00000);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_GREEN
				prop_name = jerry_create_string ((const jerry_char_t *) "green");
				prop_value = jerry_create_number (0x0000FF00);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_RED
				prop_name = jerry_create_string ((const jerry_char_t *) "red");
				prop_value = jerry_create_number (0x000000FF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_CYAN
				prop_name = jerry_create_string ((const jerry_char_t *) "cyan");
				prop_value = jerry_create_number (0x00FFFF00);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_MAGENTA
				prop_name = jerry_create_string ((const jerry_char_t *) "magenta");
				prop_value = jerry_create_number (0x00FF00FF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_YELLOW
				prop_name = jerry_create_string ((const jerry_char_t *) "yellow");
				prop_value = jerry_create_number (0x0000FFFF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_LIGHTBLUE
				prop_name = jerry_create_string ((const jerry_char_t *) "lightblue");
				prop_value = jerry_create_number (0x00FF8080);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_LIGHTGREEN
				prop_name = jerry_create_string ((const jerry_char_t *) "lightgreen");
				prop_value = jerry_create_number (0x0080FF80);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_LIGHTRED
				prop_name = jerry_create_string ((const jerry_char_t *) "lightred");
				prop_value = jerry_create_number (0x008080FF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_LIGHTCYAN
				prop_name = jerry_create_string ((const jerry_char_t *) "lightcyan");
				prop_value = jerry_create_number (0x00FFFF80);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_LIGHTYELLOW
				prop_name = jerry_create_string ((const jerry_char_t *) "lightyellow");
				prop_value = jerry_create_number (0x0080FFFF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKBLUE
				prop_name = jerry_create_string ((const jerry_char_t *) "darkblue");
				prop_value = jerry_create_number (0x00800000);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKGREEN
				prop_name = jerry_create_string ((const jerry_char_t *) "darkgreen");
				prop_value = jerry_create_number (0x00008000);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKRED
				prop_name = jerry_create_string ((const jerry_char_t *) "darkred");
				prop_value = jerry_create_number (0x00000080);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKCYAN
				prop_name = jerry_create_string ((const jerry_char_t *) "darkcyan");
				prop_value = jerry_create_number (0x00808000);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKMAGENTA
				prop_name = jerry_create_string ((const jerry_char_t *) "darkmagenta");
				prop_value = jerry_create_number (0x00800080);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKYELLOW
				prop_name = jerry_create_string ((const jerry_char_t *) "darkyellow");
				prop_value = jerry_create_number (0x00008080);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_WHITE
				prop_name = jerry_create_string ((const jerry_char_t *) "white");
				prop_value = jerry_create_number (0x00FFFFFF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_LIGHTGRAY
				prop_name = jerry_create_string ((const jerry_char_t *) "lightgray");
				prop_value = jerry_create_number (0x00D3D3D3);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_GRAY
				prop_name = jerry_create_string ((const jerry_char_t *) "gray");
				prop_value = jerry_create_number (0x00808080);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_DARKGRAY
				prop_name = jerry_create_string ((const jerry_char_t *) "darkgray");
				prop_value = jerry_create_number (0x00404040);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_BLACK
				prop_name = jerry_create_string ((const jerry_char_t *) "black");
				prop_value = jerry_create_number (0x00000000);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_BROWN
				prop_name = jerry_create_string ((const jerry_char_t *) "brown");
				prop_value = jerry_create_number (0x002A2AA5);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_ORANGE
				prop_name = jerry_create_string ((const jerry_char_t *) "orange");
				prop_value = jerry_create_number (0x0000A5FF);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				//GUI_TRANSPARENT
				prop_name = jerry_create_string ((const jerry_char_t *) "transparent");
				prop_value = jerry_create_number (0xFF000000);
				jerry_release_value (jerry_set_property (color, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);
			}

			prop_name = jerry_create_string ((const jerry_char_t *) "color");
			jerry_release_value (jerry_set_property (GUI, prop_name, color));
			jerry_release_value (prop_name);
			jerry_release_value (color);

			//backlight
			jerry_value_t backlight = jerry_create_object();
			if (!jerry_value_is_error(backlight)) {
				prop_name = jerry_create_string ((const jerry_char_t *) "OFF");
				prop_value = jerry_create_number (0);
				jerry_release_value (jerry_set_property (backlight, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "LOW");
				prop_value = jerry_create_number (1);
				jerry_release_value (jerry_set_property (backlight, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "MEDIUM");
				prop_value = jerry_create_number (2);
				jerry_release_value (jerry_set_property (backlight, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "HIGH");
				prop_value = jerry_create_number (3);
				jerry_release_value (jerry_set_property (backlight, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);
			}

			prop_name = jerry_create_string ((const jerry_char_t *) "backlight");
			jerry_release_value (jerry_set_property (GUI, prop_name, backlight));
			jerry_release_value (prop_name);
			jerry_release_value (backlight);

			jerry_value_t drawArrow = jerry_create_external_function (GUI_display_draw_arrow_handler);
			prop_name = jerry_create_string ((const jerry_char_t *) "drawArrow");
			jerry_release_value (jerry_set_property (GUI, prop_name, drawArrow));
			jerry_release_value (prop_name);
			jerry_release_value (drawArrow);

			jerry_value_t arrow = jerry_create_object();
			if (!jerry_value_is_error(arrow)) {
				prop_name = jerry_create_string ((const jerry_char_t *) "UP");
				prop_value = jerry_create_number (1);
				jerry_release_value (jerry_set_property (arrow, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "DOWN");
				prop_value = jerry_create_number (2);
				jerry_release_value (jerry_set_property (arrow, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "LEFT");
				prop_value = jerry_create_number (3);
				jerry_release_value (jerry_set_property (arrow, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);

				prop_name = jerry_create_string ((const jerry_char_t *) "RIGHT");
				prop_value = jerry_create_number (4);
				jerry_release_value (jerry_set_property (arrow, prop_name, prop_value));
				jerry_release_value (prop_name);
				jerry_release_value (prop_value);
			}

			prop_name = jerry_create_string ((const jerry_char_t *) "arrow");
			jerry_release_value (jerry_set_property (GUI, prop_name, arrow));
			jerry_release_value (prop_name);
			jerry_release_value (arrow);

		}
	}

	return GUI;
}
