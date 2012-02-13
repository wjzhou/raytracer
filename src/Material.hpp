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

#include "math.hpp"
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
  PhongMaterial(const Color& a_diffuseColor):diffuseColor(a_diffuseColor){};
  PhongMaterial(Color& a_diffuseColor):diffuseColor(a_diffuseColor){};

  Color diffuseColor;
private:
};
typedef PhongMaterial Material;
#endif /* _MATEIAL_H_ */
