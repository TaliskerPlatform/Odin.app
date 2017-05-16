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

#define IKERNEL_STRUCT_DEFINED
#define IMUTABLEKERNEL_STRUCT_DEFINED

#include "p_Odin.h"

#define INTF_TO_CLASS(i) (Odin *)((void *)(i))

typedef union Odin Odin;

/* This construction is valid for as long as the interfaces are all part of a
 * single-inheritance chain
 */
union Odin
{
	IObject object;
	IKernel kernel;
	IMutableKernel mutablekernel;
	struct
	{
		void *vtable;
		/* Private data */
		IMemoryManager *mm;
		IAllocator *allocator;
		IConsole *console;
	} data;
};

static int odin_init_(void);
static int odin_queryinterface_(IMutableKernel *kernel, const uuid_t riid, void **ptr);
static int32_t odin_retain_(IMutableKernel *kernel);
static int32_t odin_release_(IMutableKernel *kernel);
static int odin_mm_(IMutableKernel *kernel, IMemoryManager **mm);
static int odin_allocator_(IMutableKernel *kernel, IAllocator **allocator);
static int odin_panic_(IMutableKernel *kernel, const char *message);
static int odin_console_(IMutableKernel *kernel, IConsole **console);
static int odin_createtask_(IMutableKernel *kernel, IMutableTask **task);

static Odin odin_global;

static struct IMutableKernel_vtable_ odin_vtable =
{
	/* IUnknown */
	odin_queryinterface_,
	odin_retain_,
	odin_release_,
	/* IKernel */
	odin_mm_,
	odin_allocator_,
	/* IMutableKernel */
	odin_panic_,
	odin_console_,
	odin_createtask_
};

/* Obtain the global kernel state */
int
odin(IKernel **ptr)
{
	odin_init_();
	*ptr = &odin_global.kernel;
	return 0;
}

/* Obtain the global kernel state as a mutable object */
int
odin_mutable(IMutableKernel **ptr)
{
	odin_init_();
	*ptr = &odin_global.mutablekernel;
	return 0;	
}

static int
odin_init_(void)
{
	odin_global.mutablekernel.lpVtbl = &odin_vtable;
	odin_mm_create(&(odin_global.kernel), &(odin_global.data.mm));
	odin_alloc_create(&(odin_global.kernel), &(odin_global.data.allocator));
	odin_console_create(&(odin_global.kernel), &(odin_global.data.console));
	return 0;
}

static int
odin_queryinterface_(IMutableKernel *kernel, const uuid_t riid, void **ptr)
{
	Odin *me = INTF_TO_CLASS(kernel);
	
	if(!memcmp(riid, IID_IObject, sizeof(uuid_t)))
	{
		*ptr = &(me->object);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IKernel, sizeof(uuid_t)))
	{
		*ptr = &(me->kernel);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IMutableKernel, sizeof(uuid_t)))
	{
		*ptr = &(me->mutablekernel);
		return E_SUCCESS;
	}
	return -E_NOENT;
}

static int32_t
odin_retain_(IMutableKernel *kernel)
{
	(void) kernel;
	
	return 2;
}

static int32_t
odin_release_(IMutableKernel *kernel)
{
	(void) kernel;

	return 1;
}

static int 
odin_allocator_(IMutableKernel *kernel, IAllocator **allocator)
{
	Odin *me = INTF_TO_CLASS(kernel);

	IAllocator_retain(me->data.allocator);
	*allocator = me->data.allocator;
	return 0;
}

static int 
odin_mm_(IMutableKernel *kernel, IMemoryManager **mm)
{
	Odin *me = INTF_TO_CLASS(kernel);

	IMemoryManager_retain(me->data.mm);
	*mm = me->data.mm;
	return 0;
}

static int
odin_panic_(IMutableKernel *kernel, const char *message)
{
	Odin *me = INTF_TO_CLASS(kernel);
	
	IConsole_puts(me->data.console, "\n\nFATAL KERNEL ERROR\n\n");
	IConsole_puts(me->data.console, message);
	IConsole_puts(me->data.console, "\n\n");
#ifdef HOST_TYPE_HOSTED
	abort();
#endif
	for(;;) { }
	/* not reached */

	return 0;
}

static int
odin_console_(IMutableKernel *kernel, IConsole **console)
{
	Odin *me = INTF_TO_CLASS(kernel);
	
	if(!me->data.console)
	{
		return -1;
	}
	IConsole_retain(me->data.console);
	*console = me->data.console;
	return 0;
}

static int
odin_createtask_(IMutableKernel *kernel, IMutableTask **task)
{
	(void) kernel;
	(void) task;
	
	/* We don't know how to do this yet */
	return -1;
}
