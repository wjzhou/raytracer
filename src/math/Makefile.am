noinst_LTLIBRARIES = libmath.la
libmath_la_CPPFLAGS = -I$(srcdir)/include 
libmath_la_CXXFLAGS = $(DEBUG_CXXFLAGS)
libmath_la_SOURCES = $(srcdir)/src/matrix2.cpp  $(srcdir)/src/matrix3.cpp\
     $(srcdir)/src/matrix4.cpp  $(srcdir)/src/simd/intel_sse.cpp 
noinst_HEADERS = $(srcdir)/include/math/constants.h         \
                 $(srcdir)/include/math/fwd.h               \
                 $(srcdir)/include/math/matrix.h            \
                 $(srcdir)/include/math/utility.h           \
                 $(srcdir)/include/math/bits/assign_dispatch.h\
                 $(srcdir)/include/math/bits/binary.h        \
                 $(srcdir)/include/math/bits/index_objects.h \
                 $(srcdir)/include/math/bits/opcodes.h       \
                 $(srcdir)/include/math/bits/scalar_traits.h \
                 $(srcdir)/include/math/bits/spec_mmul.h     \
                 $(srcdir)/include/math/bits/unary.h         \
                 $(srcdir)/include/math/bits/assign_elop.h   \
                 $(srcdir)/include/math/bits/config.h        \
                 $(srcdir)/include/math/bits/matrix.h        \
                 $(srcdir)/include/math/bits/operations.h    \
                 $(srcdir)/include/math/bits/simd            \
                 $(srcdir)/include/math/bits/tmatrix.h       \
                 $(srcdir)/include/math/bits/vector_inline.h \
                 $(srcdir)/include/math/bits/assign_generic.h\
                 $(srcdir)/include/math/bits/helpers.h       \
                 $(srcdir)/include/math/bits/matrix_inline.h \
                 $(srcdir)/include/math/bits/operators.h     \
                 $(srcdir)/include/math/bits/spec_dot.h      \
                 $(srcdir)/include/math/bits/tmatrix_inline.h\
                 $(srcdir)/include/math/bits/basic_matrix.h  \
                 $(srcdir)/include/math/bits/indexing.h      \
                 $(srcdir)/include/math/bits/matrix_storage.h\
                 $(srcdir)/include/math/bits/pseudo_matrix.h \
                 $(srcdir)/include/math/bits/spec_index.h    \
                 $(srcdir)/include/math/bits/tmatrix_types.h \
                 $(srcdir)/include/math/bits/simd/config.h   \
                 $(srcdir)/include/math/bits/simd/intel_sse.h\
                 $(srcdir)/include/math/bits/simd/select_impl.h\
                 $(srcdir)/include/math/bits/simd/simd4_types.h

