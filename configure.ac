AC_PREREQ(2.59)
AC_INIT(OniboConverter2, [0.1], [martingt89@gmail.com])

AM_INIT_AUTOMAKE([subdir-objects 1.10 -Wall no-define])
AC_CONFIG_HEADERS([config.h])

IT_PROG_INTLTOOL(0.35.0)

CXXFLAGS=""

AC_PROG_CXX

PKG_CHECK_MODULES([DEPS], [libxml++-2.6, gtkmm-3.0 >= 3.0.0])

# Checks for header files.
AC_CHECK_HEADERS([string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_FORK
AC_CHECK_FUNCS([gettimeofday mkdir regcomp strerror])

top_builddir=`pwd`
AC_SUBST([top_builddir])

# I18n
GETTEXT_PACKAGE=OniboConverter2
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"],
		   [The domain name to use with gettext.])
		   
ALL_LINGUAS="sk"
AM_GLIB_GNU_GETTEXT

# List all available languages here

#PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
#AC_SUBST(PROGRAMNAME_LOCALEDIR)

AC_CONFIG_FILES([Makefile src/Makefile data/Makefile data/OniboConverter2.desktop po/Makefile.in])
AC_OUTPUT
