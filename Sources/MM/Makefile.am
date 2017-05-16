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

AM_CPPFLAGS = @AM_CPPFLAGS@ -DW_NO_UNSTABLE_INTERFACES \
	-I${top_builddir}/Sources -I${top_srcdir}/Sources 

noinst_LIBRARIES = libmm.a

libmm_a_SOURCES = hostmm.c hostalloc.c
