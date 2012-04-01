/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Mateial.hpp Tue Jan 31 10:18:44 2012 wujun $
 * 
 *
 * Define the Material base class and PhongMaterial
 */
#ifndef _MATEIAL_H_
#define _MATEIAL_H_

#include "common.hpp"
/*class Material
{
public:
  Material();
  virtual ~Material()=0;
  Color diffuseColor;
};*/

/**
 * only support diffuseColor now
 * 
 */

class PhongMaterial//: public Material
{
public:
  PhongMaterial()
  {
    diffuse=math::zero;
    specular=math::zero;
    ambient=math::zero;
    exponent=0.0f;
    reflectiveRate=0.0f;
  }
  
  void setAmbient(Color* ambientp)
  {
    if (ambientp == NULL) {
      ambient = Vec3f(0.0f,0.0f,0.0f);
    } else {
      ambient = *ambientp;
    }
  }
  void setSpecular(Color* specularp)
  {
    if (specularp == NULL) {
      specular = Vec3f(0.0f,0.0f,0.0f);
    } else {
      specular = *specularp;
    }
  }
  void setExponent(float a_exponent)
  {
    exponent = a_exponent;
  }
  void setDiffuse(Color* diffusep)
  {
    if (diffusep == NULL) {
      diffuse = Vec3f(0.0f,0.0f,0.0f);
    } else {
      diffuse = *diffusep;
    }
  }
  void setReflectiveRate(float a_reflectiveRate)
  {
    reflectiveRate=a_reflectiveRate;
  }
  Color diffuse;
  Color specular;
  Color ambient;
  float exponent;
  float reflectiveRate;
private:
};
typedef PhongMaterial Material;
#endif /* _MATEIAL_H_ */
