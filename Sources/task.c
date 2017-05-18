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

/* This is Odin's implementation of a task object: it ultimately implements the
 * IMutableTask interface, and primarily keeps track of various pieces of
 * metadata: the owning user and group, current working directory, open object
 * descriptors, run state, memory maps, and threads.
 *
 * ITask provides a read-only, unprivileged view of a task. IMutableTask,
 * when available, allows control of a task's properties.
 */

#define INTF_TO_CLASS(i) (Task *)((void *)(i))

typedef union Task Task;

union Task
{
	/* Interface inheritance chain */
	IObject object;
	ISupports supports;
	ITask task;
	IMutableTask mutabletask;
	struct
	{
		void *vtable;
		int32_t refcount;
		IKernel *kernel;
		IAllocator *alloc;
	} data;
};

/* Private */

static int odin_task_init_(Task *me);
static int odin_task_done_(Task *me);

/* IObject */

static int odin_task_queryinterface_(IMutableTask *self, const uuid_t riid, void **ptr);
static int32_t odin_task_retain_(IMutableTask *self);
static int32_t odin_task_release_(IMutableTask *self);

/* ISupports */

/* ITask */

static int odin_task_subsystem_(IMutableTask *self, const uuid_t riid, void **ptr);

/* IMutableTask */

static int odin_task_createthread_(IMutableTask *self, IMutableThread **newthread);
static int odin_task_descriptorfor_(IMutableTask *self, void *object, const uuid_t iid);

static struct IMutableTask_vtable_ odin_task_vtable_ = {
	odin_task_queryinterface_,
	odin_task_retain_,
	odin_task_release_,
	odin_task_subsystem_,
	odin_task_createthread_,
	odin_task_descriptorfor_
};

int
odin_task_create(IKernel *kernel, IMutableTask **task)
{
	IAllocator *alloc;
	Task *p;
	int r;
	
	if((r = IKernel_allocator(kernel, &alloc)))
	{
		return r;
	}
	p = IAllocator_alloc(alloc, sizeof(Task));
	if(!p)
	{
		return -E_NOMEM;
	}
	p->mutabletask.lpVtbl = &odin_task_vtable_;
	p->data.kernel = kernel;
	p->data.alloc = alloc;
	p->data.refcount = 1;
	if((r = odin_task_init_(p)))
	{
		IAllocator_free(alloc, p);
		IAllocator_release(alloc);
		return r;
	}
	IKernel_retain(kernel);
	*task = &(p->mutabletask);
	
	/* TODO: add task to object namespace */
	
	return E_SUCCESS;
}


static int
odin_task_init_(Task *me)
{
	(void) me;
	
	return E_SUCCESS;
}

static int
odin_task_done_(Task *me)
{
	(void) me;
	
	return E_SUCCESS;
}

/* IObject */

static int
odin_task_queryinterface_(IMutableTask *self, const uuid_t riid, void **ptr)
{
	Task *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, IID_IObject, sizeof(uuid_t)))
	{
		odin_task_retain_(self);
		*ptr = &(me->object);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_ISupports, sizeof(uuid_t)))
	{
		odin_task_retain_(self);
		*ptr = &(me->supports);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_ITask, sizeof(uuid_t)))
	{
		odin_task_retain_(self);
		*ptr = &(me->task);
		return E_SUCCESS;
	}
	if(!memcmp(riid, IID_IMutableTask, sizeof(uuid_t)))
	{
		odin_task_retain_(self);
		*ptr = &(me->mutabletask);
		return E_SUCCESS;
	}
	return -E_NOENT;
}

static int32_t odin_task_retain_(IMutableTask *self)
{
	Task *me = INTF_TO_CLASS(self);
	int32_t r;
	
	/* LOCK */
	me->data.refcount++;
	r = me->data.refcount;
	/* UNLOCK */
	
	return r;
}

static int32_t
odin_task_release_(IMutableTask *self)
{
	IAllocator *alloc;
	Task *me = INTF_TO_CLASS(self);
	int32_t r;
	
	/* LOCK */
	me->data.refcount++;
	r = me->data.refcount;
	/* UNLOCK */
	
	if(!r)
	{
		odin_task_done_(me);
		IKernel_release(me->data.kernel);
		alloc = me->data.alloc;
		
		IAllocator_free(alloc, me);
		IAllocator_release(alloc);
	}
	return r;	
}

/* ISupports */

/* ITask */

static int
odin_task_subsystem_(IMutableTask *self, const uuid_t riid, void **ptr)
{
	Task *me = INTF_TO_CLASS(self);

	(void) me;
	(void) riid;
	(void) ptr;
	
	return -E_NOENT;
}

/* IMutableTask */

static int
odin_task_createthread_(IMutableTask *self, IMutableThread **newthread)
{
	Task *me = INTF_TO_CLASS(self);
	int r;
	
	if((r = odin_thread_create(self, me->data.kernel, newthread)))
	{
		return r;
	}
	
	/* TODO: add thread to task's list */
	/* TODO: add thread to object namespace */
	
	return E_SUCCESS;
}

static int
odin_task_descriptorfor_(IMutableTask *self, void *object, const uuid_t iid)
{
	Task *me = INTF_TO_CLASS(self);

	(void) me;
	(void) object;
	(void) iid;
	
	return -E_NOMEM;
}
