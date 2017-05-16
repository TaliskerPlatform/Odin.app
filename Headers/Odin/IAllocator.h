/* DO NOT EDIT: Automatically generated from IAllocator.idl by idl */

#ifndef IAllocator_FWD_DEFINED
# define IAllocator_FWD_DEFINED
typedef struct IAllocator IAllocator;
#endif

#ifndef IALLOCATOR_H_IDL_
# define IALLOCATOR_H_IDL_

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

/* IAllocator version 0.0 */

# ifndef __IAllocator_INTERFACE_DEFINED__
#  define __IAllocator_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IAllocator


DECLARE_INTERFACE_(IAllocator, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IAllocator */
	STDMETHOD_(void*, alloc)(THIS_ size_t nbytes) PURE;
	STDMETHOD_(void*, realloc)(THIS_ void *ptr, size_t nbytes) PURE;
	STDMETHOD_(void, free)(THIS_ void *ptr) PURE;
	STDMETHOD_(size_t, size)(THIS_ void *ptr) PURE;
	STDMETHOD_(int, didAlloc)(THIS_ void *ptr) PURE;
	STDMETHOD_(void, compact)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IAllocator_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IAllocator_retain(__this) __this->lpVtbl->retain(__this)
#   define IAllocator_release(__this) __this->lpVtbl->release(__this)
#   define IAllocator_alloc(__this, nbytes) __this->lpVtbl->alloc(__this, nbytes)
#   define IAllocator_realloc(__this, ptr, nbytes) __this->lpVtbl->realloc(__this, ptr, nbytes)
#   define IAllocator_free(__this, ptr) __this->lpVtbl->free(__this, ptr)
#   define IAllocator_size(__this, ptr) __this->lpVtbl->size(__this, ptr)
#   define IAllocator_didAlloc(__this, ptr) __this->lpVtbl->didAlloc(__this, ptr)
#   define IAllocator_compact(__this) __this->lpVtbl->compact(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IAllocator_INTERFACE_DEFINED__*/


/* IID_IAllocator = {00000002-0000-0000-c000-000000000046} */
UUID_DEFINE(IID_IAllocator, 0x00, 0x00, 0x00, 0x02,  0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#endif /*!IALLOCATOR_H_IDL_*/
