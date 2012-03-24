
namespace math {

// wrapped around indexing objects to allow subscripting
template<class I>
struct indexer {
	indexer() {}

	template<class T> indexer<bits::index_sequence<I, T> >
	operator,(indexer<T>) const
		{ return indexer<bits::index_sequence<I, T> >(); }

	template<class T> indexer<bits::index_stack<I, T> >
	operator|(indexer<T>) const
		{ return indexer<bits::index_stack<I, T> >(); }

	template<class T> indexer<bits::index_sequence<T, I> >
	operator()(const indexer<T>) const
		{ return indexer<bits::index_sequence<T, I> >(); }
};

namespace bits {

template<int RC> struct mask {
	enum { row = 0x000f << RC*4 };
	enum { col = 0x1111 << RC };
	enum { rows_ge = 0xffff & (0xffff << RC*4) };
	enum { rows_le = 0xffff >> (3-RC)*4 };
	enum { col_ge_t = 0xf & (0xf << RC) };
	enum { col_le_t = 0xf >> (3-RC) };
	enum { cols_ge = col_ge_t | (col_ge_t << 4) | (col_ge_t << 8)
		| (col_ge_t << 12) };
	enum { cols_le = col_le_t | (col_le_t << 4) | (col_le_t << 8)
		| (col_le_t << 12) };
};

template<class I, class T> struct index_info;

// concatenate indexing transformations
template<class I, class J, class A>
struct index_info<index_sequence<I, J>, A> {
	typedef index_info<I, A> i_only;
	typedef index_info<J, i_only> ij;

	enum { rows = ij::rows,
		columns = ij::columns };
	enum { error = i_only::error || ij::error };
	enum { element_mask = 0 };
	enum { aliasing = i_only::aliasing || ij::aliasing };
	template<int R, int C> struct index {
		typedef typename ij::template index<R, C> j;
		enum { rt = j::r };
		enum { ct = j::c };
		typedef typename i_only::template index<rt, ct> i;
		enum { r = i::r };
		enum { c = i::c };
	};
};

// stack submatrices
template<class I, class J, class A>
struct index_info<index_stack<I, J>, A> {
	typedef index_info<I, A> i_only;
	typedef index_info<J, A> j_only;

	enum { rows = i_only::rows + j_only::rows,
		columns = i_only::columns };
	enum { error = i_only::error || j_only::error
		|| i_only::columns != j_only::columns };
	enum { element_mask = i_only::element_mask
		| j_only::element_mask };
	enum { aliasing = i_only::aliasing || j_only::aliasing
		|| (i_only::element_mask & j_only::element_mask) };
	enum { limit = i_only::rows-1 };
	template<int R, int C> struct index {
		typedef typename i_only::template index<R, C> i;
		typedef typename j_only::template index<R-j_only::rows, C> j;
		enum { r = R > limit ? j::r : i::r };
		enum { c = R > limit ? j::c : i::c };
	};
};

// rearrange elements
template<int X, int Y, int Z, int W, class A>
struct index_info<index_swizzle<X, Y, Z, W>, A> {
	enum { in_range = X < A::rows && Y < A::rows
		&& Z < A::rows && W < A::rows };
	enum { rows = Z == -98 ? 2 : W == -99 ? 3 : 4,
		columns = 1 };
	enum { error = A::columns != 1 || !in_range };
	enum { element_mask = (1<<X) | (1<<Y)
		| (1<<(Z!=-98 ? Z : X)) | (1<<(W!=-99 ? W : X)) };
	enum { aliasing = X == Y || X == Z || X == W
		|| Y == Z || Y == W || Z == W };
	template<int R, int C> struct index {
		enum { r = R == 0 ? X : R == 1 ? Y : R == 2 ? Z : W };
		enum { c = 0 };
	};
};

// transpose matrix
template<class A>
struct index_info<index_transpose, A> {
	enum { rows = A::columns,
		columns = A::rows };
	enum { error = false };
	enum { element_mask = 0xffff };
	enum { aliasing = false };
	template<int R, int C> struct index {
		enum { r = C };
		enum { c = R };
	};
};

// extract single element
template<int R, int C, class A>
struct index_info<index_element<R, C>, A> {
	enum { rows = 1,
		columns = 1 };
	enum { error = false };
	enum { element_mask = 1 << (R+C*4) };
	enum { aliasing = false };
	template<int, int> struct index {
		enum { r = R };
		enum { c = C };
	};
};

// remove row R and column C
template<int R, int C, class A>
struct index_info<index_cofactor<R, C>, A> {
	enum { rows = A::rows-1,
		columns = A::columns-1 };
	enum { error = rows <= 0 || columns <= 0 };
	enum { element_mask = 0xffff & ~mask<R>::row
		& ~mask<C>::col };
	enum { aliasing = false };
	template<int IR, int IC> struct index {
		enum { r = IR >= R ? IR+1 : IR };
		enum { c = IC >= C ? IC+1 : IC };
	};
};

// select submatrix
template<int R1, int C1, int R2, int C2, bool RR, bool RC, class A>
struct index_info<index_submatrix<R1, C1, R2, C2, RR, RC>, A> {
	enum { max_rows = R2-R1+1,
		max_cols = C2-C1+1 };
	enum { rows = int(max_rows) > A::rows ? int(A::rows) : int(max_rows),
		columns = int(max_cols) > A::columns
		? int(A::columns) : int(max_cols) };
	enum { error = rows <= 0 || columns <= 0
           || (RR && int(max_rows) > A::rows)
           || (RC && int(max_cols) > A::columns) };
	enum { element_mask = mask<R1>::rows_ge
		& mask<R2>::rows_le & mask<C1>::cols_ge & mask<C2>::cols_le };
	enum { aliasing = false };
	template<int R, int C> struct index {
		enum { r = R + R1 };
		enum { c = C + C1 };
	};
};

} // namespace bits
} // namespace math
