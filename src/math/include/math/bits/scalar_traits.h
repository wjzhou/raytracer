
namespace math {
namespace bits {

template<class Type>
struct scalar_traits {
	typedef Type value_type;
	typedef Type argument_type;

	enum { is_pod = false };
};

template<>
struct scalar_traits<char> {
	typedef char value_type;
	typedef char argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<signed char> {
	typedef signed char value_type;
	typedef signed char argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<unsigned char> {
	typedef unsigned char value_type;
	typedef unsigned char argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<short> {
	typedef short value_type;
	typedef short argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<unsigned short> {
	typedef unsigned short value_type;
	typedef unsigned short argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<int> {
	typedef int value_type;
	typedef int argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<unsigned> {
	typedef unsigned value_type;
	typedef unsigned argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<long> {
	typedef long value_type;
	typedef long argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<unsigned long> {
	typedef unsigned long value_type;
	typedef unsigned long argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<float> {
	typedef float value_type;
	typedef float argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<double> {
	typedef double value_type;
	typedef double argument_type;

	enum { is_pod = true };
};

template<>
struct scalar_traits<long double> {
	typedef long double value_type;
	typedef long double argument_type;

	enum { is_pod = true };
};

} // namespace bits
} // namespace math
