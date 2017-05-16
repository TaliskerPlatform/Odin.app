/* Odin: The Talisker nanokernel */

/* Copyright (c) 2017 Mo McRoberts.
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_Odin.h"

/* Only for hosted (i.e., user-space) builds: a kernel memory allocator
 * which uses malloc()/free() behind the scenes
 */

#ifdef HOST_TYPE_HOSTED

#define INTF_TO_CLASS(i) (HostMM *)((void *)(i))

typedef union HostMM HostMM;

/* This construction is valid for as long as the interfaces are all part of a
 * single-inheritance chain
 */
union HostMM
{
	IObject object;
	IMemoryManager mm;
	struct
	{
		void *vtable;
		IKernel *kernel;
	} data;
};

static int odin_hostmm_queryinterface_(IMemoryManager *self, const uuid_t riid, void **ptr);
static int32_t odin_hostmm_retain_(IMemoryManager *self);
static int32_t odin_hostmm_release_(IMemoryManager *self);

static struct IMemoryManager_vtable_ odin_hostmm_vtable_ = {
	odin_hostmm_queryinterface_,
	odin_hostmm_retain_,
	odin_hostmm_release_
};

static HostMM odin_hostmm;

int
odin_hostmm_create(IKernel *kernel, IMemoryManager **mm)
{
	if(!odin_hostmm.mm.lpVtbl)
	{
		odin_hostmm.mm.lpVtbl = &odin_hostmm_vtable_;
		odin_hostmm.data.kernel = kernel;
	}
	*mm = &(odin_hostmm.mm);
	return E_SUCCESS;
}

static int odin_hostmm_queryinterface_(IMemoryManager *self, const uuid_t riid, void **ptr)
{
	HostMM *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, IID_IObject, sizeof(uuid_t)))
	{
		*ptr = &(me->object);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IMemoryManager, sizeof(uuid_t)))
	{
		*ptr = &(me->mm);
		return E_SUCCESS;
	}
	return -E_NOENT;
}

static int32_t
odin_hostmm_retain_(IMemoryManager *self)
{
	(void) self;
	
	/* HostMM is a singleton */
	return 2;
}

static int32_t
odin_hostmm_release_(IMemoryManager *self)
{
	(void) self;
	
	/* HostMM is a singleton */
	return 1;
}

#endif /*HOST_TYPE_HOSTED*/