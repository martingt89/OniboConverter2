AC_PREREQ(2.59)
AC_INIT(OniboConverter2, [1.0], [martingt89@gmail.com])

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([subdir-objects 1.10 -Wall no-define])

AC_CONFIG_HEADER([config.h])

IT_PROG_INTLTOOL(0.35.0)

CXXFLAGS=""

AC_PROG_CXX

PKG_CHECK_MODULES([DEPS], [libxml++-2.6, gtkmm-3.0 >= 3.0.0])

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

#AM_GLIB_GNU_GETTEXT
#PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
#AC_SUBST(PROGRAMNAME_LOCALEDIR)

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_OUTPUT
