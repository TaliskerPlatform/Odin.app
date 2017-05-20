## Odin: the Talisker nanokernel

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

AC_INIT([Odin],[develop])

AC_CONFIG_MACRO_DIR([M4])
AC_CONFIG_AUX_DIR([BuildScripts])

test x"$CPPFLAGS" = x"" && empty_cppflags=yes
test x"$CXXFLAGS" = x"" && empty_cxxflags=yes
test x"$CFLAGS" = x"" && empty_cflags=yes

TAL_CANONICAL_SYSTEM

AC_PREFIX_DEFAULT([/Preview])

AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_MAINTAINER_MODE

AC_PROG_CC

if test x"$GCC" = x"yes" ; then
	test x"$empty_cppflags" = x"yes" && CPPFLAGS="$CPPFLAGS -W -Wall"
	test x"$empty_cflags" = x"yes" && CFLAGS="$CFLAGS -ggdb -O0"
	test x"$empty_cxxflags" = x"yes" && CXXFLAGS="$CXXFLAGS -ggdb -O0"
fi

AC_CHECK_PROG([IDL],[idl],[idl],)
if test x"$IDL" = x"" ; then
        AC_MSG_ERROR([cannot find the Talisker IDL compiler, which is required to build Odin])
fi

AM_CPPFLAGS="$AM_CPPFLAGS -I\${top_builddir}/Headers -I\${top_srcdir}/Headers"

AC_CONFIG_HEADER([config.h])

AC_PROG_RANLIB

AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])

if test $host_type = hosted ; then
	AC_DEFINE_UNQUOTED([ENABLE_ODIN_MM_HOSTMM], [1], [Enable the hosted memory manager])
	AC_DEFINE_UNQUOTED([ENABLE_ODIN_MM_HOSTALLOC], [1], [Enable the hosted allocator])
	AC_DEFINE_UNQUOTED([ENABLE_ODIN_DEV_HOSTCON], [1], [Enable the host console])
fi

AC_CONFIG_FILES([
Makefile
IDL/Makefile
IDL/Odin/Makefile
Headers/Makefile
Headers/Odin/Makefile
Sources/Makefile
Sources/Devices/Makefile
Sources/MM/Makefile
Sources/Filesystems/Makefile
Sources/Interpreters/Makefile
])

AC_OUTPUT
