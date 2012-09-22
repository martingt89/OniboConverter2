AC_PREREQ(2.59)
AC_INIT(OniboConverter2, [0.1], [martingt89@gmail.com])

AC_ARG_ENABLE([debug],[  --enable-debug    Turn on debugging],
[case "${enableval}" in
yes) debug=true ;;
no)  debug=false ;;
*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

AC_MSG_CHECKING([uname -m for detecting host operating system architecture])
ARCH=`uname -m`
AC_MSG_RESULT(${ARCH})

AC_MSG_CHECKING([uname -s for detecting host operating system])
OSNAME=`uname -s`
AC_MSG_RESULT(${OSNAME})

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

# List all available languages here

ALL_LINGUAS="sk"
AM_GLIB_GNU_GETTEXT

AC_CONFIG_FILES([Makefile src/Makefile data/Makefile data/OniboConverter2.desktop po/Makefile.in])
AC_OUTPUT

echo
echo "===================================="
echo "Configure report:"
echo
echo " Core:"
echo "             os: ${OSNAME}"
echo "         prefix: ${prefix}"
echo "   architecture: ${ARCH}"
echo
echo " Debug mode:"
if test "x$debug" = "xtrue" ; then
echo "          debug: true";
else
echo "          debug: false";
fi

