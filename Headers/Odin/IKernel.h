/* DO NOT EDIT: Automatically generated from IKernel.idl by idl */

#ifndef IKernel_FWD_DEFINED
# define IKernel_FWD_DEFINED
typedef struct IKernel IKernel;
#endif

#ifndef IKERNEL_H_IDL_
# define IKERNEL_H_IDL_

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
# include <Odin/IObject.h>
# include <Odin/IMemoryManager.h>
# include <Odin/IAllocator.h>

/* IKernel version 0.0 */

# ifndef __IKernel_INTERFACE_DEFINED__
#  define __IKernel_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IKernel interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IKernel


DECLARE_INTERFACE_(IKernel, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IKernel */
	STDMETHOD_(int, mm)(THIS_ IMemoryManager **intf) PURE;
	STDMETHOD_(int, allocator)(THIS_ IAllocator **intf) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IKernel_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IKernel_retain(__this) __this->lpVtbl->retain(__this)
#   define IKernel_release(__this) __this->lpVtbl->release(__this)
#   define IKernel_mm(__this, intf) __this->lpVtbl->mm(__this, intf)
#   define IKernel_allocator(__this, intf) __this->lpVtbl->allocator(__this, intf)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IKernel_INTERFACE_DEFINED__*/


/* IID_IKernel = {22d03407-2fe7-4358-a95f-925f3ed83617} */
UUID_DEFINE(IID_IKernel, 0x22, 0xd0, 0x34, 0x07,  0x2f, 0xe7, 0x43, 0x58, 0xa9, 0x5f, 0x92, 0x5f, 0x3e, 0xd8, 0x36, 0x17);

#endif /*!IKERNEL_H_IDL_*/
