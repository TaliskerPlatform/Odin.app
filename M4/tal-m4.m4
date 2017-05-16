#serial 2017021100
# Talisker: Keep distributed files up to date

dnl Copyright 2017 Mo McRoberts.
dnl
dnl  Licensed under the Apache License, Version 2.0 (the "License");
dnl  you may not use this file except in compliance with the License.
dnl  You may obtain a copy of the License at
dnl
dnl      http://www.apache.org/licenses/LICENSE-2.0
dnl
dnl  Unless required by applicable law or agreed to in writing, software
dnl  distributed under the License is distributed on an "AS IS" BASIS,
dnl  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
dnl  See the License for the specific language governing permissions and
dnl  limitations under the License.

m4_pattern_forbid([^_?TAL_])

dnl - TAL_M4_UPDATE()
dnl Substitute a Makefile fragment which adds a `make m4-update` target which
dnl checks the timestamps on M4 macro files in the source tree against those
dnl installed on the system, and updates the tree if newer versions are
dnl installed system-wide.
dnl
dnl In an ideal world, aclocal/autoreconf would be able to do this for us,
dnl but they do not play nicely 
dnl
dnl Remember that this an M4 macro which is expanded to a shell fragment that
dnl defines a rule that will be substituted into a Makefile, so care must be
dnl taken with escaping, newlines and quoting.
 
AC_DEFUN([TAL_M4_UPDATE],[
AC_REQUIRE_AUX_FILE([tal-m4.mk])dnl
tal__aux_dir="$ac_aux_dir"
tal_m4_update="$tal__aux_dir/tal-m4.mk"
AC_SUBST([tal__aux_dir])
AC_SUBST_FILE([tal_m4_update])
])
