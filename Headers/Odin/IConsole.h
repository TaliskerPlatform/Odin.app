/* DO NOT EDIT: Automatically generated from IConsole.idl by idl */

#ifndef IConsole_FWD_DEFINED
# define IConsole_FWD_DEFINED
typedef struct IConsole IConsole;
#endif

#ifndef ICONSOLE_H_IDL_
# define ICONSOLE_H_IDL_

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
# include <Odin/ISupports.h>

/* IConsole version 0.0 */

# ifndef __IConsole_INTERFACE_DEFINED__
#  define __IConsole_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IConsole interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IConsole


DECLARE_INTERFACE_(IConsole, ISupports)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ISupports */
# endif /*!__cplusplus*/

	/* IConsole */
	STDMETHOD_(int, puts)(THIS_ const char *string) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IConsole_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IConsole_retain(__this) __this->lpVtbl->retain(__this)
#   define IConsole_release(__this) __this->lpVtbl->release(__this)
#   define IConsole_puts(__this, string) __this->lpVtbl->puts(__this, string)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IConsole_INTERFACE_DEFINED__*/


/* IID_IConsole = {d992d94d-d298-4595-8f78-d4ff713d26af} */
UUID_DEFINE(IID_IConsole, 0xd9, 0x92, 0xd9, 0x4d,  0xd2, 0x98, 0x45, 0x95, 0x8f, 0x78, 0xd4, 0xff, 0x71, 0x3d, 0x26, 0xaf);

#endif /*!ICONSOLE_H_IDL_*/
