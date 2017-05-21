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

idlgenerated = Interfaces.h Errors.h \
	IObject.h IFactory.h ISupports.h \
	ITask.h IMutableTask.h \
	IThread.h IMutableThread.h \
	IVariant.h IArray.h IDictionary.h IString.h \
	IKernel.h IMutableKernel.h \
	IAllocator.h \
	IRegion.h IMemoryManager.h \
	IConsole.h

odindir = $(includedir)/Odin

CLEANFILES = $(idlgenerated)

odin_HEADERS = $(idlgenerated) _decl.h

%.h: $(top_srcdir)/IDL/Odin/%.idl
	$(IDL) -I$(top_srcdir)/IDL/Odin -H $@ $<
