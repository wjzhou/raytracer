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
#include "common.hpp"
#include <random>
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
  Color& getColor()
  {
    return diffuse;
  }
    
  void setPower(float a_power)
  {
    power=a_power;
  }
  float getPower()
  {
    return power;
  }
  
  
  float power;
  Color diffuse;
  Color specular;
  Color ambient;
  Vec3f attenuation;
  virtual Vec3f getLightVector(Vec3f& hitPoint)=0;
  virtual void getLightVector2(Vec3f& result, float& power, float& distance, const Vec3f& hitPoint)=0;
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
  virtual void getLightVector2(Vec3f& result, float& power,float& distance, const Vec3f& hitPoint);
  virtual ~PointLight(){};
};

class AreaLight : public Light
{
public:
  AreaLight(Color& color, float power)
    :color(color),power(power),distribution(0.0f,1.0f){
    setColor(&color);
  }
  
  void initPosition(const Vec3f& a_o, const Vec3f& o1, const Vec3f& o2)
  {
    o=a_o;
    a=o1-o;
    b=o2-o;
    normal=norm(cross(a,b));
  }
  virtual void getLightVector2(Vec3f& result, float& power,float& distance, const Vec3f& hitPoint);
  virtual Vec3f getLightVector(Vec3f& hitPoint)
  {
    return o+distribution(engine)*a+distribution(engine)*b-hitPoint;
  }
    
  Vec3f color;
  float power;
  Vec3f o;
  Vec3f a;
  Vec3f b;
  Vec3f normal;
  std::mt19937 engine;
  std::uniform_real_distribution<float> distribution;
  virtual ~AreaLight(){};
private:
};

#endif /* _LIGHT_H_ */
