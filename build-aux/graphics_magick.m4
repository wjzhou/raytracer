# Configure paths for GraphicsMagic
# Wujun Zhou modified from gtk-3.0.m4

dnl AM_PATH_GRAPHICS_MAGICK
dnl Test for GraphicsMagick, and define GM_CFLAGS and GM_LIBS,
dnl
AC_DEFUN([AM_PATH_GRAPHICS_MAGICK],
[dnl 
dnl Get the cflags and libraries from GraphicsMagick++-config
dnl
AC_MSG_CHECKING([whether attempt to link to graphicmagic])
AC_ARG_ENABLE([gm], 
    [AS_HELP_STRING([--disable-gm],
        [do not try to link with graphicmgic])],
[AC_MSG_RESULT([get --disable-gm, skip graphicsmagic probing])],
[
  AC_MSG_RESULT([yes])
  AC_PATH_PROG([GM_CONFIG], [GraphicsMagick++-config], [no])
  AC_MSG_CHECKING([whether the graphicsmagick lib have been installed])

  if test x"$GM_CONFIG" = xno ; then
    AC_MSG_RESULT([GraphicsMagick++ not found, fall back to ppm. If it has been installed, try to set GM_CONFIG=/path/to/GraphicsMagick++-config, and try again.])
  else
    AC_MSG_RESULT([yes])
    AC_DEFINE([HAVE_GM],1,[This indicate to use Gragicsmagick])
    GM_CPPFLAGS=`$GM_CONFIG --cppflags`
    GM_CXXFLAGS=`$GM_CONFIG --cxxflags`
    GM_LDFLAGS=`$GM_CONFIG --ldflags`
    GM_LIBS=`$GM_CONFIG --libs`
    gm_version=`$GM_CONFIG --version`
    AC_MSG_CHECKING([for GraphicsMagick++ version])
    AC_MSG_RESULT([$gm_version])
  fi
  AC_SUBST(GM_CPPFLAGS)
  AC_SUBST(GM_CXXFLAGS)
  AC_SUBST(GM_LDFLAGS)
  AC_SUBST(GM_LIBS)
])
])


