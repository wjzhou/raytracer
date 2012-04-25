AC_DEFUN([AM_DEBUG],
[dnl
dnl add debug info
AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [indicate whether generate debug data(default=yes),
         gdb: macro DEBUG and set -g -O0 FLAGS, will be slow,
         no: macro NDEBUG, it will leave out all debug info,
         yes: set -g FLAGS])],
    [debugit="$enableval"],
    [debugit="yes"])
AC_MSG_RESULT([$debugit])

AS_CASE([$debugit],
  [gdb],[dnl
    AC_DEFINE([DEBUG],[],[Debug Mode])
    CFLAGS=""
    CXXFLAGS=""
    DEBUG_CXXFLAGS="-g -Wall -Werror -Wno-uninitialized -O0"
  ]
  [no],[AC_DEFINE([NDEBUG],[],[No-debug Mode])]
  [DEBUG_CXXFLAGS="-g"]
)
AC_SUBST(DEBUG_CXXFLAGS)
])
