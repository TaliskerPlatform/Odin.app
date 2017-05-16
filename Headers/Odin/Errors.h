/* DO NOT EDIT: Automatically generated from Errors.idl by idl */

#ifndef ERRORS_H_IDL_
# define ERRORS_H_IDL_

/* Odin: The Talisker nanokernel */

/* Copyright 2017 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef __cplusplus
# include <stdbool.h>
#endif
#include <sys/types.h>
#include <uuid/uuid.h>
#include "Odin/_decl.h"

/* Errors version 0.0 */

# ifndef __Errors_INTERFACE_DEFINED__
#  define __Errors_INTERFACE_DEFINED__
#  define E_SUCCESS 0
#  define E_PERM 1
#  define E_ACCESS 2
#  define E_NOMEM 3
#  define E_IO 4
#  define E_NOENT 5
#  define E_USER 255
#  define E_MAX 4095
#  undef INTERFACE
# endif /*!__Errors_INTERFACE_DEFINED__*/


#endif /*!ERRORS_H_IDL_*/
