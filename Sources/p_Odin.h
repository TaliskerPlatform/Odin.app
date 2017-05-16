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

#ifndef P_ODIN_H_
# define P_ODIN_H_                     1

/* for memcmp(), et al */
# include <string.h>

# ifdef HOST_TYPE_HOSTED
/* File I/O */
#  include <unistd.h>
/* Errno values */
#  include <errno.h>
/* malloc(), free(), etc. */
#  include <stdlib.h>
# endif

# include "Odin/IMutableKernel.h"
# include "Odin/IMemoryManager.h"
# include "Odin/IAllocator.h"
# include "Odin/IConsole.h"
# include "Odin/IMutableTask.h"
# include "Odin/IMutableThread.h"

# ifdef PACKAGE_RELEASE
#  define PACKAGE_RELSTR               " Release" PACKAGE_RELEASE
# endif

# ifndef PACKAGE_RELEASE
#  define PACKAGE_RELEASE              ""
#  define PACKAGE_RELSTR               ""
# endif

# ifdef HOST_TYPE_FREESTANDING
#  define PACKAGE_PLATSTR              HOST_FAMILY
# else
#  define PACKAGE_PLATSTR              HOST_PLATFORM "_" HOST_FAMILY
# endif

# ifdef PACKAGE_CONFIG_NAME
#  define PACKAGE_VERSTR               PACKAGE_VERSION "-" PACKAGE_CONFIG_NAME
# else
#  define PACKAGE_VERSTR               PACKAGE_VERSION
# endif

# define PACKAGE_COPYRIGHT_NOTICE \
	"Copyright 2017 Mo McRoberts\n"

/* Odin */
int odin(IKernel **kernel);
int odin_mutable(IMutableKernel **kernel);

/* Console */
int odin_console_create(IKernel *kernel, IConsole **console);

/* Memory Manager */
int odin_mm_create(IKernel *kernel, IMemoryManager **mm);

/* Default allocator */
int odin_alloc_create(IKernel *kernel, IAllocator **alloc);

/* Devices */
int odin_hostcon_create(IKernel *kernel, IConsole **console);

/* MM */
int odin_hostmm_create(IKernel *kernel, IMemoryManager **mm);
int odin_hostmm_create_alloc(IKernel *kernel, IAllocator **allocator);

#endif /*!P_ODIN_H_*/
