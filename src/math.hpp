/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: math.hpp Tue Jan 31 10:07:31 2012 wujun $
 * 
 *
 * this file is almost copied from Jacco Bikker - jacco@bik5.com - www.bik5.com
 */

#ifndef _MATH_H_
#define _MATH_H_
#include <cmath>
#include <cstdlib>
#include <iostream>
/* the stansard seems drop this within C99*/
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif
using namespace std;


inline float Rand( float a_Range ) { return ((float)rand() / RAND_MAX) * a_Range; }

#define DOT(A,B)		(A.x*B.x+A.y*B.y+A.z*B.z)
#define CEOSS(A, B)  Vec3( A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x ) 
#define LENGTH(A)		(sqrtf(A.x*A.x+A.y*A.y+A.z*A.z))
#define NORMALIZE(A)	{float l=1/LENGTH(A);A.x*=l;A.y*=l;A.z*=l;}
#define SQRLENGTH(A)	(A.x*A.x+A.y*A.y+A.z*A.z)
#define SQRDISTANCE(A,B) ((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z))

#define EPSILON			0.0001f
#define TRACEDEPTH		6

#define PI				3.141592653589793238462f

class Vec3
{
public:
	Vec3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {};
	Vec3( float a_X, float a_Y, float a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) {};
	void set( float a_X, float a_Y, float a_Z ) { x = a_X; y = a_Y; z = a_Z; }
	void normalize() { float l = 1.0f / length(); x *= l; y *= l; z *= l; }
	float length() { return (float)sqrt( x * x + y * y + z * z ); }
	float sqrLength() { return x * x + y * y + z * z; }
	float dot( Vec3 a_V ) { return x * a_V.x + y * a_V.y + z * a_V.z; }
	Vec3 cross( Vec3 b ) { return Vec3( y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x ); }
	void operator += ( Vec3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
	void operator += ( Vec3* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }
  void operator += ( const Vec3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
	void operator += (const Vec3* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }
	void operator -= ( Vec3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
	void operator -= ( Vec3* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }
  	void operator -= (const Vec3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
	void operator -= (const Vec3* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }
	void operator *= ( float f ) { x *= f; y *= f; z *= f; }
	void operator *= ( Vec3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }
	void operator *= ( Vec3* a_V ) { x *= a_V->x; y *= a_V->y; z *= a_V->z; }
  void operator *= ( const Vec3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }
	void operator *= (const Vec3* a_V ) { x *= a_V->x; y *= a_V->y; z *= a_V->z; }
	Vec3 operator- () const { return Vec3( -x, -y, -z ); }
	friend Vec3 operator + ( const Vec3& v1, const Vec3& v2 ) { return Vec3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
	friend Vec3 operator - ( const Vec3& v1, const Vec3& v2 ) { return Vec3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	friend Vec3 operator + ( const Vec3& v1, Vec3* v2 ) { return Vec3( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
	friend Vec3 operator - ( const Vec3& v1, Vec3* v2 ) { return Vec3( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
	friend Vec3 operator * ( const Vec3& v, float f ) { return Vec3( v.x * f, v.y * f, v.z * f ); }
	friend Vec3 operator * ( const Vec3& v1, Vec3& v2 ) { return Vec3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
	friend Vec3 operator * ( float f, const Vec3& v ) { return Vec3( v.x * f, v.y * f, v.z * f ); }
  union
  {
    struct { float x, y, z; };
    float data[3];
  };
  constexpr float operator [] (int i)
  {
    return (i==0)?x:((i==1)?y:((i==2)?:z));
  }
  
    
    
friend  ostream& operator << (ostream & out,Vec3 vec)
  {
    out<<"["<<vec.x<<","<<vec.y<<","<<vec.z<<"]";
    return out;
  }
  
  
};

#endif /* _MATH_H_ */
