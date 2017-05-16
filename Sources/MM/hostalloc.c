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

#define INTF_TO_CLASS(i) (HostAlloc *)((void *)(i))

typedef union HostAlloc HostAlloc;

/* This construction is valid for as long as the interfaces are all part of a
 * single-inheritance chain
 */
union HostAlloc
{
	IObject object;
	IAllocator allocator;
	struct
	{
		void *vtable;
		IMemoryManager *mm;
		IKernel *kernel;
	} data;
};

static int odin_hostalloc_queryinterface_(IAllocator *self, const uuid_t riid, void **ptr);
static int32_t odin_hostalloc_retain_(IAllocator *self);
static int32_t odin_hostalloc_release_(IAllocator *self);

static void *odin_hostalloc_alloc_(IAllocator *self, size_t nbytes);
static void *odin_hostalloc_realloc_(IAllocator *self, void *ptr, size_t nbytes);
static void odin_hostalloc_free_(IAllocator *self, void *ptr);
static size_t odin_hostalloc_size_(IAllocator *self, void *ptr);
static int odin_hostalloc_didalloc_(IAllocator *self, void *ptr);
static void odin_hostalloc_compact_(IAllocator *self);

static struct IAllocator_vtable_ odin_hostalloc_vtable_ = {
	odin_hostalloc_queryinterface_,
	odin_hostalloc_retain_,
	odin_hostalloc_release_,
	odin_hostalloc_alloc_,
	odin_hostalloc_realloc_,
	odin_hostalloc_free_,
	odin_hostalloc_size_,
	odin_hostalloc_didalloc_,
	odin_hostalloc_compact_
};

static HostAlloc odin_hostalloc;

int
odin_hostmm_create_alloc(IKernel *kernel, IAllocator **allocator)
{
	int r;
	
	if(!odin_hostalloc.allocator.lpVtbl)
	{
		odin_hostalloc.allocator.lpVtbl = &odin_hostalloc_vtable_;
		odin_hostalloc.data.kernel = kernel;
		/* One-time singleton initialisation */
		if((r = IKernel_mm(kernel, &(odin_hostalloc.data.mm))))
		{
			/* Failed to obtain the default allocator */
			return r;
		}
	}
	*allocator = &(odin_hostalloc.allocator);
	return E_SUCCESS;
}

static int odin_hostalloc_queryinterface_(IAllocator *self, const uuid_t riid, void **ptr)
{
	HostAlloc *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, IID_IObject, sizeof(uuid_t)))
	{
		*ptr = &(me->object);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IAllocator, sizeof(uuid_t)))
	{
		*ptr = &(me->allocator);
		return E_SUCCESS;
	}
	return -E_NOENT;
}

static int32_t
odin_hostalloc_retain_(IAllocator *self)
{
	(void) self;
	
	/* HostAlloc is a singleton */
	return 2;
}

static int32_t
odin_hostalloc_release_(IAllocator *self)
{
	(void) self;
	
	/* HostAlloc is a singleton */
	return 1;
}

static void *
odin_hostalloc_alloc_(IAllocator *self, size_t nbytes)
{
	(void) self;
	
	return calloc(1, nbytes);
}

static void *
odin_hostalloc_realloc_(IAllocator *self, void *ptr, size_t nbytes)
{
	(void) self;
	
	return realloc(ptr, nbytes);
}

static void
odin_hostalloc_free_(IAllocator *self, void *ptr)
{
	(void) self;
	
	free(ptr);
}

static size_t
odin_hostalloc_size_(IAllocator *self, void *ptr)
{
	(void) self;
	(void) ptr;
	
	return (size_t)((int) -E_PERM);
}

static int
odin_hostalloc_didalloc_(IAllocator *self, void *ptr)
{
	(void) self;
	(void) ptr;
	
	return -E_PERM;
}

static void
odin_hostalloc_compact_(IAllocator *self)
{
	(void) self;
}


#endif /*HOST_TYPE_HOSTED*/