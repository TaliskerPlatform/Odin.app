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

int
main(int argc, char **argv, char **envp)
{
	IMutableKernel *odin;
	IConsole *console;
	IMutableTask *task;
	IMutableThread *thread;
	int od;
	
	if(odin_mutable(&odin))
	{
		/* Somehow, we failed to initialise the kernel itself, which is
		 * particularly suboptimal as there's not a great deal we can do
		 * about it except return an error status
		 */
		return 1;
	}
	
	if(IMutableKernel_console(odin, &console))
	{
		/* We've failed to obtain a console from the kernel. This is hard
		 * error - even if no console device was available, Odin should still
		 * provider an interface pointer from a no-op implementation.
		 */
		IMutableKernel_release(odin);
		return 2;
	}
	IConsole_puts(console, "Talisker " PACKAGE_NAME PACKAGE_RELEASE " Version " PACKAGE_VERSTR "-" PACKAGE_PLATSTR "\n");
	IConsole_puts(console, PACKAGE_COPYRIGHT_NOTICE);
	IConsole_puts(console, "\n");
	
	/* Create the first task and thread, which on a multitasking system will
	 * simply be an idle loop once the system has booted
	 */
	if(IMutableKernel_createTask(odin, &task))
	{
		IConsole_release(console);
		IMutableKernel_panic(odin, "failed to create initial kernel task\n");
		IMutableKernel_release(odin);
		return 3;
	}
	/* XXX the task should probably track the kernel memory mappings */
	if(IMutableTask_createThread(task, &thread))
	{
		IMutableKernel_panic(odin, "failed to create initial task's main thread\n");
		IConsole_release(console);
		IMutableKernel_panic(odin, "failed to create initial kernel task\n");
		IMutableKernel_release(odin);
	}
	/* Set the new thread's initial state (in particular the entry-point) */
	/* Create an object descriptor for the console within this task */
	od = IMutableTask_descriptorFor(task, console, IID_IConsole);
	if(od < 0)
	{
		/* If the (numeric) returned object descriptor is negative,
		 * the call failed.
		 */
		IConsole_puts(console, "failed to obtain an object descriptor for the console in the initial task\n");
	}
	/* Pass control to the task's initial thread, which will spawn the Startup
	 * app and then loop forever.
	 */
	IMutableThread_resume(thread);
	/* If control is returned here, trigger a systemwide exception - it
	 * means the (supposedly-unkillable) executive task has died.
	 */
	IConsole_release(console);
	
	return 127;
}