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

/* This is Odin's implementation of a thread object: it ultimately implements the
 * IMutableThread interface, and primarily keeps track of various pieces of
 * metadata: the owning user and group, current working directory, open object
 * descriptors, run state, memory maps, and threads.
 *
 * IThread provides a read-only, unprivileged view of a thread. IMutableThread,
 * when available, allows control of a thread's properties.
 */

#define INTF_TO_CLASS(i) (Thread *)((void *)(i))

typedef union Thread Thread;

union Thread
{
	/* Interface inheritance chain */
	IObject object;
	ISupports supports;
	IThread thread;
	IMutableThread mutablethread;
	struct
	{
		void *vtable;
		int32_t refcount;
		IMutableTask *task; /* not retained */
		IKernel *kernel;
		IAllocator *alloc;
	} data;
};

/* Private */

static int odin_thread_init_(Thread *me);
static int odin_thread_done_(Thread *me);

/* IObject */

static int odin_thread_queryinterface_(IMutableThread *self, const uuid_t riid, void **ptr);
static int32_t odin_thread_retain_(IMutableThread *self);
static int32_t odin_thread_release_(IMutableThread *self);

/* ISupports */

/* IThread */

/* IMutableThread */

static int odin_thread_resume_(IMutableThread *self);
static int odin_thread_despatch_(IMutableThread *self, int od, int mid, int r1, int r2, int r3, int r4, int r5, int r6);

static struct IMutableThread_vtable_ odin_thread_vtable_ = {
	odin_thread_queryinterface_,
	odin_thread_retain_,
	odin_thread_release_,
	odin_thread_resume_,
	odin_thread_despatch_
};

int
odin_thread_create(IMutableTask *task, IKernel *kernel, IMutableThread **thread)
{
	IAllocator *alloc;
	Thread *p;
	int r;
	
	if((r = IKernel_allocator(kernel, &alloc)))
	{
		return r;
	}
	p = IAllocator_alloc(alloc, sizeof(Thread));
	if(!p)
	{
		return -E_NOMEM;
	}
	p->mutablethread.lpVtbl = &odin_thread_vtable_;
	p->data.task = task;
	p->data.kernel = kernel;
	p->data.alloc = alloc;
	p->data.refcount = 1;
	if((r = odin_thread_init_(p)))
	{
		IAllocator_free(alloc, p);
		IAllocator_release(alloc);
		return r;
	}
	IKernel_retain(kernel);
	*thread = &(p->mutablethread);
	return E_SUCCESS;
}


static int
odin_thread_init_(Thread *me)
{
	(void) me;
	
	return E_SUCCESS;
}

static int
odin_thread_done_(Thread *me)
{
	(void) me;
	
	return E_SUCCESS;
}

/* IObject */

static int
odin_thread_queryinterface_(IMutableThread *self, const uuid_t riid, void **ptr)
{
	Thread *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, IID_IObject, sizeof(uuid_t)))
	{
		odin_thread_retain_(self);
		*ptr = &(me->object);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_ISupports, sizeof(uuid_t)))
	{
		odin_thread_retain_(self);
		*ptr = &(me->supports);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IThread, sizeof(uuid_t)))
	{
		odin_thread_retain_(self);
		*ptr = &(me->thread);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IMutableThread, sizeof(uuid_t)))
	{
		odin_thread_retain_(self);
		*ptr = &(me->mutablethread);
		return E_SUCCESS;
	}
	return -E_NOENT;
}

static int32_t odin_thread_retain_(IMutableThread *self)
{
	Thread *me = INTF_TO_CLASS(self);
	int32_t r;
	
	/* LOCK */
	me->data.refcount++;
	r = me->data.refcount;
	/* UNLOCK */
	
	return r;
}

static int32_t
odin_thread_release_(IMutableThread *self)
{
	IAllocator *alloc;
	Thread *me = INTF_TO_CLASS(self);
	int32_t r;
	
	/* LOCK */
	me->data.refcount++;
	r = me->data.refcount;
	/* UNLOCK */
	
	if(!r)
	{
		odin_thread_done_(me);
		IKernel_release(me->data.kernel);
		alloc = me->data.alloc;
		
		IAllocator_free(alloc, me);
		IAllocator_release(alloc);
	}
	return r;	
}

/* ISupports */

/* IThread */

/* IMutableThread */

static int
odin_thread_resume_(IMutableThread *self)
{
	Thread *me = INTF_TO_CLASS(self);

	(void) me;
	
	return E_SUCCESS;
}

static int
odin_thread_despatch_(IMutableThread *self, int od, int mid, int r1, int r2, int r3, int r4, int r5, int r6)
{
	Thread *me = INTF_TO_CLASS(self);

	(void) me;
	(void) od;
	(void) mid;
	(void) r1;
	(void) r2;
	(void) r3;
	(void) r4;
	(void) r5;
	(void) r6;
	
	return -E_PERM;
}

