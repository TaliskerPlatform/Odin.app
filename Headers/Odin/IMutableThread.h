/* DO NOT EDIT: Automatically generated from IMutableThread.idl by idl */

#ifndef IMutableThread_FWD_DEFINED
# define IMutableThread_FWD_DEFINED
typedef struct IMutableThread IMutableThread;
#endif

#ifndef IMUTABLETHREAD_H_IDL_
# define IMUTABLETHREAD_H_IDL_

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
# include <Odin/IThread.h>

/* IMutableThread version 0.0 */

# ifndef __IMutableThread_INTERFACE_DEFINED__
#  define __IMutableThread_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IMutableThread interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IMutableThread


DECLARE_INTERFACE_(IMutableThread, IThread)
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

	/* IThread */
# endif /*!__cplusplus*/

	/* IMutableThread */
	STDMETHOD_(int, resume)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IMutableThread_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IMutableThread_retain(__this) __this->lpVtbl->retain(__this)
#   define IMutableThread_release(__this) __this->lpVtbl->release(__this)
#   define IMutableThread_resume(__this) __this->lpVtbl->resume(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IMutableThread_INTERFACE_DEFINED__*/


/* IID_IMutableThread = {e95e3ddd-e143-420b-96e6-53d0a840665e} */
UUID_DEFINE(IID_IMutableThread, 0xe9, 0x5e, 0x3d, 0xdd,  0xe1, 0x43, 0x42, 0x0b, 0x96, 0xe6, 0x53, 0xd0, 0xa8, 0x40, 0x66, 0x5e);

#endif /*!IMUTABLETHREAD_H_IDL_*/
