#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libmanchicken], [0.1], [themanchicken@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([c], [strcmp])
AC_CHECK_LIB([cunit], [CU_assertImplementation])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h CUnit/CUnit.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile src/Makefile t/Makefile])
AC_OUTPUT()
