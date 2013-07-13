#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cReddit], [0.0.1], [https://github.com/Cotix/cReddit/issues])
AC_CONFIG_SRCDIR([jsmn.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([foreign 1.14 no-installinfo -Wall])
AM_MAINTAINER_MODE
AC_EXEEXT
AC_LANG([C])

# Checks for programs.
AM_PROG_CC_C_O
AC_PROG_GCC_TRADITIONAL
LIBCURL_CHECK_CONFIG([yes])
AX_LIB_CURL
AC_PATH_PROG([FLAGSORT], [flag-sort])
AC_PATH_PROG([FLAGDEDUP], [flag-dedup])
AC_PATH_PROG([XCODEBUILD], [xcodebuild])

# TODO: use the PKG_CHECK_MODULES macro instead
PKG_PROG_PKG_CONFIG

# Checks for libraries.
AC_CHECK_LIB([curl], [curl_easy_init])
AC_CHECK_LIB([curl], [curl_easy_setopt])
AC_CHECK_LIB([curl], [curl_global_init])
AC_CHECK_LIB([curl], [curl_global_cleanup])
AC_CHECK_LIB([curses], [initscr])
AX_WITH_CURSES
AX_WITH_CURSES_PANEL
AX_WITH_CURSES_MENU
AX_WITH_CURSES_FORM
AX_LIB_READLINE

# Checks for header files.
AC_CHECK_HEADERS([curl/curl.h form.h ncurses.h stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_PROTOTYPES
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memcpy strcat strcmp strcpy strlen])

AC_CONFIG_FILES([Makefile build.sh])
AC_OUTPUT
