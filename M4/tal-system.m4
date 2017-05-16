#serial 2017051400
# Talisker: Determine system types

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

dnl - TAL_CANONICAL_SYSTEM()
dnl Determine the build, host and target system types

AC_DEFUN([TAL_CANONICAL_SYSTEM],[
AC_REQUIRE([TAL_M4_UPDATE])dnl
AC_REQUIRE([TAL_CANONICAL_BUILD])dnl
AC_REQUIRE([TAL_CANONICAL_HOST])dnl
AC_REQUIRE([TAL_CANONICAL_TARGET])dnl
])

dnl - TAL_CANONICAL_BUILD()
dnl Determine the build system type (i.e., the system this script is being
dnl executed on).

AC_DEFUN([TAL_CANONICAL_BUILD],[
AC_REQUIRE([TAL_M4_UPDATE])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
_TAL_SYS([build])dnl
])

dnl - TAL_CANONICAL_HOST()
dnl Determine the host system type (i.e., the system that executables will be
dnl compiled for); usually the same as the build system type unless
dnl cross-compiling.

AC_DEFUN([TAL_CANONICAL_HOST],[
AC_REQUIRE([TAL_M4_UPDATE])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
_TAL_SYS([host])dnl
])

dnl - TAL_CANONICAL_TARGET()
dnl Determine the target system type (i.e., the system that output from built
dnl executables will be targeting; usually the same as the host system type
dnl unless building cross-build tools.

AC_DEFUN([TAL_CANONICAL_TARGET],[
AC_REQUIRE([TAL_M4_UPDATE])dnl
AC_REQUIRE([AC_CANONICAL_TARGET])dnl
_TAL_SYS([target])dnl
])

dnl - _TAL_SYS($1:KIND=build|host|target)

AC_DEFUN([_TAL_SYS],[
AS_LITERAL_IF([$1],,[m4_fatal([_TAL_SYS: $1 is not a literal])])dnl
# Determine ]$1[ system family, platform, platform type (freestanding,
# native, hosted)

AC_MSG_CHECKING([for ]$1[ system CPU architecture family])
_TAL_SYS_FAMILY([$1])
AC_MSG_RESULT([$]$1[_family])

AC_MSG_CHECKING([for ]$1[ platform and type])
_TAL_SYS_PLATFORM([$1])
_TAL_SYS_TYPE([$1])
_TAL_SYS_BINDIR([$1])
AC_MSG_RESULT([$]$1[_platform ($]$1[_type)])

m4_if([$1],[host],[_TAL_SYS_VARIANTS([$1])])
m4_if([$1],[target],[_TAL_SYS_VARIANTS([$1])])
])

dnl - _TAL_SYS_FAMILY($1:KIND=build|host|target)

AC_DEFUN([_TAL_SYS_FAMILY],[
case "$]$1[_cpu" in
	i?86)
		AS_VAR_SET($1[_family], ['i386'])
		;;
	x86_64|amd64)
		AS_VAR_SET($1[_family], ['x86_64'])
		;;
	*)
		AS_VAR_SET($1[_family],["$]$1[_cpu"])
		;;
esac
AC_SUBST($1[_family])
AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_FAMILY],["$]$1[_family"],[The name of the ]$1[ CPU family that we are building for])
])

dnl - _TAL_SYS_PLATFORM($1:KIND=build|host|target)

AC_DEFUN([_TAL_SYS_PLATFORM],[
AS_VAR_SET([tal_check],["$]$1[_os"])
m4_changequote({,})dnl
case "$tal_check" in
	linux-*)
		tal_platform='linux'
		;;
	*)
		tal_platform="`echo $tal_check | sed 's@[0-9.]*{$}@@;'`"
		;;
esac
m4_changequote([,])dnl
AS_VAR_SET($1_[platform], ["${tal_platform}"])
AC_SUBST($1[_platform])
AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_PLATFORM],["$]$1[_platform"],[The name of the ]$1[ platform that we are building for])
])

dnl - _TAL_SYS_TYPE($1:KIND=build|host|target)

AC_DEFUN([_TAL_SYS_TYPE],[
case "$]$1[_os" in
	none|elf*|coff*|ecoff*|aout*|oabi*|eabi*)
		AS_VAR_SET($1[_type], ['freestanding'])
		;;
	*)
		if test x"$]$1[_vendor" = x"none" ; then
			AS_VAR_SET($1[_type], ['native'])
		else
			AS_VAR_SET($1[_type], ['hosted'])
		fi
esac
AC_SUBST($1[_type])
AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_TYPE],["$]$1[_type"],[The type of ]$1[ platform that we are building for])
case "$]$1[_type" in
	native)
		AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_TYPE_NATIVE],[1],[If we are building for the native variant of the ]$1[ platform])
		;;
	hosted)
		AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_TYPE_HOSTED],[1],[If we are building for the hosted variant of the ]$1[ platform])
		;;
	freestanding)
		AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_TYPE_FREESTANDING],[1],[If we are building for the freestanding variant of the ]$1[ platform])
		;;
esac
])

dnl - _TAL_SYS_BINDIR($1:KIND=build|host|target)

AC_DEFUN([_TAL_SYS_BINDIR],[
case "$]$1[_type" in
	hosted)
		AS_VAR_SET($1[_bindir], ['${host_family}-${host_vendor}-${host_platform}'])
		;;
	native)
		AS_VAR_SET($1[_bindir], ['${host_family}-${host_platform}'])
		;;
	freestanding)
		AS_VAR_SET($1[_bindir], ['${host_family}'])
		;;
esac
AC_SUBST($1[_bindir])
])

dnl - _TAL_SYS_VARIANTS($1:KIND=build|host|target)

AC_DEFUN([_TAL_SYS_VARIANTS],[
case "$]$1[_type" in
	hosted)
		AS_VAR_SET($1[_variant_hosted], ["${]$1[_cpu}-${]$1[_vendor}-${]$1[_platform}"])
		AS_VAR_SET($1[_variant_native], ["${]$1[_cpu}-none-${]$1[_platform}"])
		AS_VAR_SET($1[_variant_freestanding], ["${]$1[_cpu}-none"])
		;;
	native)
		AS_VAR_SET($1[_variant_hosted], [''])
		AS_VAR_SET($1[_variant_native], ["${]$1[_cpu}-none-${]$1[_platform}"])
		AS_VAR_SET($1[_variant_freestanding], ["${]$1[_cpu}-none"])
		;;
	freestanding)
		AS_VAR_SET($1[_variant_hosted], [''])
		AS_VAR_SET($1[_variant_native], [''])
		AS_VAR_SET($1[_variant_freestanding], ["${]$1[_cpu}-none"])
		;;
esac
AC_SUBST($1[_variant_hosted])
AC_SUBST($1[_variant_native])
AC_SUBST($1[_variant_freestanding])
])