/* DO NOT EDIT: Automatically generated from IArray.idl by idl */

#ifndef IArray_FWD_DEFINED
# define IArray_FWD_DEFINED
typedef struct IArray IArray;
#endif

#ifndef IARRAY_H_IDL_
# define IARRAY_H_IDL_

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
# include <Odin/IObject.h>

/* IArray version 0.0 */

# ifndef __IArray_INTERFACE_DEFINED__
#  define __IArray_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IArray interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IArray


DECLARE_INTERFACE_(IArray, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IArray */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IArray_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IArray_retain(__this) __this->lpVtbl->retain(__this)
#   define IArray_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IArray_INTERFACE_DEFINED__*/


/* IID_IArray = {839ee1e2-f329-459d-8f03-2b8c88a4b242} */
UUID_DEFINE(IID_IArray, 0x83, 0x9e, 0xe1, 0xe2,  0xf3, 0x29, 0x45, 0x9d, 0x8f, 0x03, 0x2b, 0x8c, 0x88, 0xa4, 0xb2, 0x42);

#endif /*!IARRAY_H_IDL_*/
