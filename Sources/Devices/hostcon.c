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

/* Only for hosted (i.e., user-space) builds: a console device implementation
 * which sends output to stderr
 */

#ifdef HOST_TYPE_HOSTED

#define INTF_TO_CLASS(i) (HostCon *)((void *)(i))

typedef union HostCon HostCon;

/* This construction is valid for as long as the interfaces are all part of a
 * single-inheritance chain
 */
union HostCon
{
	IObject object;
	ISupports supports;
	IConsole console;
	struct
	{
		void *vtable;
		int32_t refcount;
		IAllocator *allocator;
		IKernel *kernel;
	} data;
};

static int odin_hostcon_queryinterface_(IConsole *self, const uuid_t riid, void **ptr);
static int32_t odin_hostcon_retain_(IConsole *self);
static int32_t odin_hostcon_release_(IConsole *self);
static int odin_hostcon_puts_(IConsole *self, const char *message);

static struct IConsole_vtable_ odin_hostcon_vtable_ = {
	odin_hostcon_queryinterface_,
	odin_hostcon_retain_,
	odin_hostcon_release_,
	odin_hostcon_puts_
};

int
odin_hostcon_create(IKernel *kernel, IConsole **console)
{
	IAllocator *allocator;
	HostCon *inst;
	int r;
	
	if((r = IKernel_allocator(kernel, &allocator)))
	{
		/* Failed to obtain the default allocator */
		return r;
	}
	inst = (HostCon *) IAllocator_alloc(allocator, sizeof(HostCon));
	if(!inst)
	{
		IAllocator_release(allocator);
		return -1;
	}
	inst->console.lpVtbl = &odin_hostcon_vtable_;
	IKernel_retain(kernel);
	inst->data.allocator = allocator;
	inst->data.kernel = kernel;
	inst->data.refcount = 1;
	*console = &(inst->console);
	return 0;
}

static int odin_hostcon_queryinterface_(IConsole *self, const uuid_t riid, void **ptr)
{
	HostCon *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, IID_IObject, sizeof(uuid_t)))
	{
		/* LOCK */
		*ptr = &(me->object);
		me->data.refcount++;
		/* UNLOCK */
		
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_ISupports, sizeof(uuid_t)))
	{
		/* LOCK */
		*ptr = &(me->supports);
		me->data.refcount++;
		/* UNLOCK */
		
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IConsole, sizeof(uuid_t)))
	{
		/* LOCK */
		*ptr = &(me->console);
		me->data.refcount++;
		/* UNLOCK */
		
		return E_SUCCESS;
	}
	return -E_NOENT;
}

static int32_t
odin_hostcon_retain_(IConsole *self)
{
	HostCon *me = INTF_TO_CLASS(self);
	int32_t r;
	
	/* LOCK */
	me->data.refcount++;
	r = me->data.refcount;
	/* UNLOCK */
	
	return r;
}

static int32_t
odin_hostcon_release_(IConsole *self)
{
	HostCon *me = INTF_TO_CLASS(self);
	IAllocator *allocator;
	int32_t r;
	
	/* LOCK */
	me->data.refcount--;
	r = me->data.refcount;
	allocator = me->data.allocator;
	/* UNLOCK */
	
	if(!r)
	{
		IAllocator_free(allocator, me);
		IAllocator_release(allocator);
	}
	return r;
}

static int
odin_hostcon_puts_(IConsole *self, const char *message)
{
	ssize_t r;
	
	(void) self;
	
	do
	{
		r = write(2, message, strlen(message));
	}
	while(r == -1 && errno == EINTR);
	if(r < 0)
	{
		return -E_IO;
	}
	return (int) r;
}


#endif /*HOST_TYPE_HOSTED*/