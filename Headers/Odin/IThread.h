/* DO NOT EDIT: Automatically generated from IThread.idl by idl */

#ifndef IThread_FWD_DEFINED
# define IThread_FWD_DEFINED
typedef struct IThread IThread;
#endif

#ifndef ITHREAD_H_IDL_
# define ITHREAD_H_IDL_

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

/* IThread version 0.0 */

# ifndef __IThread_INTERFACE_DEFINED__
#  define __IThread_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IThread interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IThread


DECLARE_INTERFACE_(IThread, ISupports)
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

	/* IThread */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IThread_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IThread_retain(__this) __this->lpVtbl->retain(__this)
#   define IThread_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IThread_INTERFACE_DEFINED__*/


/* IID_IThread = {50740873-d5a9-4103-9d64-8148f461e866} */
UUID_DEFINE(IID_IThread, 0x50, 0x74, 0x08, 0x73,  0xd5, 0xa9, 0x41, 0x03, 0x9d, 0x64, 0x81, 0x48, 0xf4, 0x61, 0xe8, 0x66);

#endif /*!ITHREAD_H_IDL_*/
