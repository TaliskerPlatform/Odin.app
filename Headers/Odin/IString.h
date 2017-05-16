/* DO NOT EDIT: Automatically generated from IString.idl by idl */

#ifndef IString_FWD_DEFINED
# define IString_FWD_DEFINED
typedef struct IString IString;
#endif

#ifndef ISTRING_H_IDL_
# define ISTRING_H_IDL_

/* Copyright 2015-2017 Mo McRoberts.
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
# include <Odin/IObject.h>

/* IString version 0.0 */

# ifndef __IString_INTERFACE_DEFINED__
#  define __IString_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IString interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IString


DECLARE_INTERFACE_(IString, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IString */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IString_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IString_retain(__this) __this->lpVtbl->retain(__this)
#   define IString_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IString_INTERFACE_DEFINED__*/


/* IID_IString = {ca170af7-7c84-4350-9dfb-436bd71b5e9d} */
UUID_DEFINE(IID_IString, 0xca, 0x17, 0x0a, 0xf7,  0x7c, 0x84, 0x43, 0x50, 0x9d, 0xfb, 0x43, 0x6b, 0xd7, 0x1b, 0x5e, 0x9d);

#endif /*!ISTRING_H_IDL_*/
