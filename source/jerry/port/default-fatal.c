/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "jerryscript-port.h"
#include "rgb_led.h"

/**
 * Default implementation of jerry_port_fatal. Calls 'abort' if exit code is
 * non-zero and "abort-on-fail" behaviour is enabled, 'exit' otherwise.
 *
 * Note:
 *      The "abort-on-fail" behaviour is only available if the port
 *      implementation library is compiled without the DISABLE_EXTRA_API macro.
 */
void jerry_port_fatal (jerry_fatal_code_t code) /**< cause of error */
{
  RGB_Led_Set_State(3,2);
} /* jerry_port_fatal */
