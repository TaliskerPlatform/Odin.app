## Odin: The Talisker nanokernel

## Copyright 2017 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

SUBDIRS = Devices MM .

AM_CPPFLAGS = @AM_CPPFLAGS@ -DW_NO_UNSTABLE_INTERFACES

sbin_PROGRAMS = Odin

Odin_SOURCES = p_Odin.h \
	main.c odin.c mm.c alloc.c despatch.c console.c task.c thread.c \
	user.c group.c descriptor.c subsystems.c

Odin_LDADD = Devices/libdevices.a MM/libmm.a
