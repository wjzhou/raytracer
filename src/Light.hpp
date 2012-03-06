/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Light.hpp Wed Feb  1 22:06:08 2012 wujun $
 * 
 *
 * light is unimplemented
 */
#ifndef _LIGHT_H_
#define _LIGHT_H_

class Light
{
public:
  Light()
  {
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

  void setDiffuse(Color* diffusep)
  {
    if (diffusep == NULL) {
      diffuse = Vec3f(0.0f,0.0f,0.0f);
    } else {
      diffuse = *diffusep;
    }
  }
  void setAttenuation(Vec3f* attenuationp)
  {
    if (attenuationp == NULL) {
      attenuation = Vec3f(1.0f,0.0f,0.0f);
    } else {
      attenuation=*attenuationp;
    }
  }  
  
  void setColor(Vec3f* color)
  {
    ambient=Vec3f(0.0f, 0.0f, 0.0f);
    specular=diffuse=*color;
    attenuation=Vec3f(1.0f,0.0f,0.0f);
  }
  
  
  Color diffuse;
  Color specular;
  Color ambient;
  Vec3f attenuation;
  virtual Vec3f getLightVector(Vec3f& hitPoint)=0;
  virtual ~Light(){};
};

class PointLight : public Light
{
public:
  PointLight(const Vec3f& position)
    :position(position){}
  Vec3f position;
  virtual Vec3f getLightVector(Vec3f& hitPoint)
  {
    return position-hitPoint;
  }
  
  virtual ~PointLight(){};
};
  
#endif /* _LIGHT_H_ */
