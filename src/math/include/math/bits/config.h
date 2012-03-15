#ifndef MATH2_BITS_CONFIG_H
#define MATH2_BITS_CONFIG_H

// detects defects and features of the compiler

// GNU C++
#if __GNUG__
	// unaliased references are supported in g++, use them
#	define MATH2_RESTRICT __restrict
#endif

// Microsoft Visual C++
#if defined _MSC_VER
#	if _MSC_VER < 1310
#		error "mathlib will not work with MSVC versions earlier than 7.1"
#	else

// disable "truncation from 'double' to 'const float'"
#   pragma warning (disable : 4305)

#	endif
#endif

// unaliased references does not appear to be supported
#ifndef MATH2_RESTRICT
#	define MATH2_RESTRICT
#endif

#endif
