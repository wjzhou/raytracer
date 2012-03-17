#include "Shader.hpp"
#include "Material.hpp"
#include <boost/foreach.hpp>
#include "Light.hpp"
#include "Scene.hpp"
#include <algorithm>
Color
SimpleDiffuseShader::doShading(Ray& ray)
{
  Vec3f hitPoint=ray.origin+ray.distance*ray.direction;
  Vec3f normal=ray.hitObject->getNormal(hitPoint);
  Material& material=ray.hitObject->getMaterial();
  return dot(normal,-ray.direction)*(material.diffuse);
}

Color
PhongShader::doShading(Ray& ray)
{
  Vec3f hitPoint=ray.origin+ray.distance*ray.direction;
  Vec3f normal=ray.hitObject->getNormal(hitPoint);
  Material& material=ray.hitObject->getMaterial();
  Color color(0.0f,0.0f,0.0f);
  boost::ptr_vector<Light>::iterator light;
  boost::ptr_vector<Light>& lights=scene.getLights();
  for (light=lights.begin();light < lights.end(); light++){
    Vec3f lightVector=light->getLightVector(hitPoint);
    float distance=abs(lightVector);
    lightVector/=distance;
    //constant linear quadratic 
    float attenuation= 1.0f / (light->attenuation(0)+light->attenuation(1)*distance
                               +light->attenuation(2)*distance*distance);
      //float attenuation=1.0f;
    Color ambient=light->ambient*material.ambient*attenuation;
    Color diffuse=light->diffuse*dot(normal,-ray.direction)*(material.diffuse)*attenuation;

    if(material.exponent!=0.0f){
      Vec3f halfVector=lightVector-ray.direction;
      //halfVector.normalize(); //change to new math library
      halfVector/=abs(halfVector);
      float half=std::max(0.0f, dot(normal,halfVector));
      float powerFactor=std::pow(half, material.exponent);
      Color specular=light->specular*material.specular*powerFactor*attenuation;
      color+=specular;
    }
    color+=ambient;
    color+=diffuse;

    
  }
  return color;
}
