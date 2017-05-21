/* DO NOT EDIT: Automatically generated from IRegion.idl by idl */

#ifndef IRegion_FWD_DEFINED
# define IRegion_FWD_DEFINED
typedef struct IRegion IRegion;
#endif

#ifndef IREGION_H_IDL_
# define IREGION_H_IDL_

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

/* IRegion version 0.0 */

# ifndef __IRegion_INTERFACE_DEFINED__
#  define __IRegion_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IRegion


DECLARE_INTERFACE_(IRegion, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IRegion */
	STDMETHOD_(int, queryOwnerInterface)(THIS_ const uuid_t riid, void **ptr) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IRegion_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IRegion_retain(__this) __this->lpVtbl->retain(__this)
#   define IRegion_release(__this) __this->lpVtbl->release(__this)
#   define IRegion_queryOwnerInterface(__this, riid, ptr) __this->lpVtbl->queryOwnerInterface(__this, riid, ptr)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IRegion_INTERFACE_DEFINED__*/


/* IID_IRegion = {e739ecdb-06ec-40c9-95f7-99c22a0c4a7b} */
UUID_DEFINE(IID_IRegion, 0xe7, 0x39, 0xec, 0xdb,  0x06, 0xec, 0x40, 0xc9, 0x95, 0xf7, 0x99, 0xc2, 0x2a, 0x0c, 0x4a, 0x7b);

#endif /*!IREGION_H_IDL_*/
