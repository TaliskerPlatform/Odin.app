/* DO NOT EDIT: Automatically generated from IObject.idl by idl */

#ifndef IObject_FWD_DEFINED
# define IObject_FWD_DEFINED
typedef struct IObject IObject;
#endif

#ifndef IOBJECT_H_IDL_
# define IOBJECT_H_IDL_

/* Odin: The Talisker nanokernel */

/* Copyright 2015 Mo McRoberts.
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
# include <Odin/Interfaces.h>
# include <Odin/Errors.h>

/* IObject version 0.0 */

# ifndef __IObject_INTERFACE_DEFINED__
#  define __IObject_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IObject


DECLARE_INTERFACE(IObject)
{
	BEGIN_INTERFACE

	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IObject_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IObject_retain(__this) __this->lpVtbl->retain(__this)
#   define IObject_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IObject_INTERFACE_DEFINED__*/


/* IID_IObject = {00000000-0000-0000-c000-000000000046} */
UUID_DEFINE(IID_IObject, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#endif /*!IOBJECT_H_IDL_*/
