/* DO NOT EDIT: Automatically generated from IMutableTask.idl by idl */

#ifndef IMutableTask_FWD_DEFINED
# define IMutableTask_FWD_DEFINED
typedef struct IMutableTask IMutableTask;
#endif

#ifndef IMUTABLETASK_H_IDL_
# define IMUTABLETASK_H_IDL_

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
# include <Odin/ITask.h>
# include <Odin/IMutableThread.h>

/* IMutableTask version 0.0 */

# ifndef __IMutableTask_INTERFACE_DEFINED__
#  define __IMutableTask_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IMutableTask interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IMutableTask


DECLARE_INTERFACE_(IMutableTask, ITask)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
# if !defined(__cplusplus)
# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ISupports */
# endif /*!__cplusplus*/

	/* ITask */
	STDMETHOD_(int, subsystem)(THIS_ const uuid_t riid, void **inst) PURE;
# endif /*!__cplusplus*/

	/* IMutableTask */
	STDMETHOD_(int, createThread)(THIS_ IMutableThread **thread) PURE;
	STDMETHOD_(int, descriptorFor)(THIS_ void *object, const uuid_t iid) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IMutableTask_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IMutableTask_retain(__this) __this->lpVtbl->retain(__this)
#   define IMutableTask_release(__this) __this->lpVtbl->release(__this)
#   define IMutableTask_subsystem(__this, riid, inst) __this->lpVtbl->subsystem(__this, riid, inst)
#   define IMutableTask_createThread(__this, thread) __this->lpVtbl->createThread(__this, thread)
#   define IMutableTask_descriptorFor(__this, object, iid) __this->lpVtbl->descriptorFor(__this, object, iid)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IMutableTask_INTERFACE_DEFINED__*/


/* IID_IMutableTask = {a92aa5ad-8c2d-4e59-928d-c0173af5c1c2} */
UUID_DEFINE(IID_IMutableTask, 0xa9, 0x2a, 0xa5, 0xad,  0x8c, 0x2d, 0x4e, 0x59, 0x92, 0x8d, 0xc0, 0x17, 0x3a, 0xf5, 0xc1, 0xc2);

#endif /*!IMUTABLETASK_H_IDL_*/
