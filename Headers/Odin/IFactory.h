/* DO NOT EDIT: Automatically generated from IFactory.idl by idl */

#ifndef IFactory_FWD_DEFINED
# define IFactory_FWD_DEFINED
typedef struct IFactory IFactory;
#endif

#ifndef IFACTORY_H_IDL_
# define IFACTORY_H_IDL_

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

/* IFactory version 0.0 */

# ifndef __IFactory_INTERFACE_DEFINED__
#  define __IFactory_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IFactory


DECLARE_INTERFACE_(IFactory, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IFactory */
	STDMETHOD_(int, createInstance)(THIS_ IObject *outer, const uuid_t iid, void **object) PURE;
	STDMETHOD_(int, lock)(THIS_ bool lock) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IFactory_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IFactory_retain(__this) __this->lpVtbl->retain(__this)
#   define IFactory_release(__this) __this->lpVtbl->release(__this)
#   define IFactory_createInstance(__this, outer, iid, object) __this->lpVtbl->createInstance(__this, outer, iid, object)
#   define IFactory_lock(__this, lock) __this->lpVtbl->lock(__this, lock)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IFactory_INTERFACE_DEFINED__*/


/* IID_IFactory = {00000001-0000-0000-c000-000000000046} */
UUID_DEFINE(IID_IFactory, 0x00, 0x00, 0x00, 0x01,  0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#endif /*!IFACTORY_H_IDL_*/
