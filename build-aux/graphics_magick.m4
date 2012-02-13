# Configure paths for GraphicsMagic
# Wujun Zhou modified from gtk-3.0.m4

dnl AM_PATH_GRAPHICS_MAGICK
dnl Test for GraphicsMagick, and define GM_CFLAGS and GM_LIBS,
dnl
AC_DEFUN([AM_PATH_GRAPHICS_MAGICK],
[dnl 
dnl Get the cflags and libraries from GraphicsMagick++-config
dnl
AC_ARG_ENABLE(gm, 
[  --disable-gm      do not try to link with graphicmgic, then the output fall back to ppm],
[AC_MSG_RESULT([get --disable-gm, skip graphicsmagic probing])],
[

  AC_PATH_PROG([GM_CONFIG], [GraphicsMagick++-config], [no])

  if test x"$GM_CONFIG" = xno ; then
    AC_MSG_ERROR([GraphicsMagick++ not found, if it has been installed, try to set GM_CONFIG=/path/to/GraphicsMagick++-config, and try again. or --disable-gm to fall back to ppm.])
  else
    GM_CPPFLAGS=`$GM_CONFIG --cppflags`
    GM_CXXFLAGS=`$GM_CONFIG --cxxflags`
    GM_LDFLAGS=`$GM_CONFIG --ldflags`
    GM_LIBS=`$GM_CONFIG --libs`
    gm_version=`$GM_CONFIG --version`
    AC_MSG_RESULT([GraphicMagic version $gm_version found])
  fi
  AC_DEFINE([HAVE_GM],1,[This indicate to use Gragicsmagick])
  AC_SUBST(GM_CPPFLAGS)
  AC_SUBST(GM_CXXFLAGS)
  AC_SUBST(GM_LDFLAGS)
  AC_SUBST(GM_LIBS)
])
])


