/* Odin: The Talisker nanokernel */

/* Copyright 2015-2017 Mo McRoberts.
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

#ifndef ODIN__DECL_H_
# define ODIN__DECL_H_                 1

# ifndef __stdcall
#  ifndef _WIN32
#   define __stdcall
#  endif
# endif

# if defined(__cplusplus)
#  define DECLARE_INTERFACE(name) \
	struct name
#  define DECLARE_INTERFACE_(name, parent) \
	struct name: virtual public parent
#  define BEGIN_INTERFACE
#  define END_INTERFACE
#  define THIS
#  define THIS_
#  define PURE = 0
#  define STDMETHOD_(type, name) \
	virtual type __stdcall name
#  define STDMETHOD(name) \
	STDMETHOD(int, name)
# else /*__cplusplus*/
#  define DECLARE_INTERFACE(name) \
	struct name { \
		struct name##_vtable_ *lpVtbl; \
	}; \
	struct name##_vtable_
#  define DECLARE_INTERFACE_(name, parent) \
	DECLARE_INTERFACE(name)
#  define BEGIN_INTERFACE
#  define END_INTERFACE
#  define THIS \
	struct INTERFACE *self
#  define THIS_ \
	struct INTERFACE *self,
#  define PURE
#  define STDMETHOD_(type, name) \
	type __stdcall (*name)
#  define STDMETHOD(name) \
	STDMETHOD(int, name)
# endif /*__cplusplus*/

#endif /*!ODIN__DECL_H_*/
