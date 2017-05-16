/* DO NOT EDIT: Automatically generated from IMutableKernel.idl by idl */

#ifndef IMutableKernel_FWD_DEFINED
# define IMutableKernel_FWD_DEFINED
typedef struct IMutableKernel IMutableKernel;
#endif

#ifndef IMUTABLEKERNEL_H_IDL_
# define IMUTABLEKERNEL_H_IDL_

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
# include <Odin/IKernel.h>
# include <Odin/IMutableTask.h>
# include <Odin/IConsole.h>

/* IMutableKernel version 0.0 */

# ifndef __IMutableKernel_INTERFACE_DEFINED__
#  define __IMutableKernel_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IMutableKernel interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IMutableKernel


DECLARE_INTERFACE_(IMutableKernel, IKernel)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IKernel */
	STDMETHOD_(int, mm)(THIS_ IMemoryManager **intf) PURE;
	STDMETHOD_(int, allocator)(THIS_ IAllocator **intf) PURE;
# endif /*!__cplusplus*/

	/* IMutableKernel */
	STDMETHOD_(int, panic)(THIS_ const char *message) PURE;
	STDMETHOD_(int, console)(THIS_ IConsole **cons) PURE;
	STDMETHOD_(int, createTask)(THIS_ IMutableTask **task) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IMutableKernel_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IMutableKernel_retain(__this) __this->lpVtbl->retain(__this)
#   define IMutableKernel_release(__this) __this->lpVtbl->release(__this)
#   define IMutableKernel_mm(__this, intf) __this->lpVtbl->mm(__this, intf)
#   define IMutableKernel_allocator(__this, intf) __this->lpVtbl->allocator(__this, intf)
#   define IMutableKernel_panic(__this, message) __this->lpVtbl->panic(__this, message)
#   define IMutableKernel_console(__this, cons) __this->lpVtbl->console(__this, cons)
#   define IMutableKernel_createTask(__this, task) __this->lpVtbl->createTask(__this, task)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IMutableKernel_INTERFACE_DEFINED__*/


/* IID_IMutableKernel = {876d8caf-8434-41e0-ab38-256dabb2d8dc} */
UUID_DEFINE(IID_IMutableKernel, 0x87, 0x6d, 0x8c, 0xaf,  0x84, 0x34, 0x41, 0xe0, 0xab, 0x38, 0x25, 0x6d, 0xab, 0xb2, 0xd8, 0xdc);

#endif /*!IMUTABLEKERNEL_H_IDL_*/
