/* DO NOT EDIT: Automatically generated from ITask.idl by idl */

#ifndef ITask_FWD_DEFINED
# define ITask_FWD_DEFINED
typedef struct ITask ITask;
#endif

#ifndef ITASK_H_IDL_
# define ITASK_H_IDL_

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

/* ITask version 0.0 */

# ifndef __ITask_INTERFACE_DEFINED__
#  define __ITask_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The ITask interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE ITask


DECLARE_INTERFACE_(ITask, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ITask */
	STDMETHOD_(int*, personality)(THIS_ const uuid_t riid, void **inst) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define ITask_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define ITask_retain(__this) __this->lpVtbl->retain(__this)
#   define ITask_release(__this) __this->lpVtbl->release(__this)
#   define ITask_personality(__this, riid, inst) __this->lpVtbl->personality(__this, riid, inst)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__ITask_INTERFACE_DEFINED__*/


/* IID_ITask = {411b8599-1940-4674-8a95-19da9bb45cc3} */
UUID_DEFINE(IID_ITask, 0x41, 0x1b, 0x85, 0x99,  0x19, 0x40, 0x46, 0x74, 0x8a, 0x95, 0x19, 0xda, 0x9b, 0xb4, 0x5c, 0xc3);

#endif /*!ITASK_H_IDL_*/
