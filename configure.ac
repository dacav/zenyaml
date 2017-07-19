AC_PREREQ([2.69])
AC_INIT([zenyaml], [0.0.1], [dacav@openmailbox.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([zenyaml/parser.cc])
AC_CONFIG_HEADERS([zenyaml/config.h])
AC_CONFIG_FILES([
    Makefile
    zenyaml/Makefile
    tests/Makefile
])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AM_PROG_AR
LT_INIT

PKG_CHECK_MODULES(YAML, [yaml-0.1])

AC_CHECK_HEADER_STDBOOL

AC_CHECK_FUNCS([strerror])

AC_OUTPUT
