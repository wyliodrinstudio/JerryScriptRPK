#ifndef LIBRARY_H
#define LIBRARY_H

#include "jerryscript.h"

#define JERRY_MAX_STRING 500

char * getString (const jerry_value_t string_value);
jerry_value_t jerryx_handler_register_global (const jerry_char_t *name_p, /**< name of the function */
                                jerry_external_handler_t handler_p); /**< function callback */
void jerry_setup ();
void jerry_execute (const char *source);
void jerry_unsetup ();

#endif
