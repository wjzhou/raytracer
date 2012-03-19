#include "Shader.hpp"
#include "Material.hpp"
#include <boost/foreach.hpp>
#include "Light.hpp"
#include "Scene.hpp"
#include <iostream>
#include <algorithm>
Shader* Shader::getShader(std::string shadingMethod,Scene& scene)
{
    if ( shadingMethod == "simple" ) return new SimpleDiffuseShader();
    if ( shadingMethod == "blinn_phong" ) return new PhongShader(scene);
    if ( shadingMethod == "blinn_phong_shadow" )
      return new PhongShaderWithShadow(scene);
    std::cout<<"unknown shading method:"<<shadingMethod<<std::endl;
    exit(4);
}
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
    color+=ambient;
    float normalLight=dot(normal,lightVector);
    if (normalLight<=0.0f)
      continue;
    Color diffuse=light->diffuse*(material.diffuse)*(normalLight*attenuation);

    if(material.exponent!=0.0f){
      Vec3f halfVector=lightVector-ray.direction;
      //halfVector.normalize(); //change to new math library
      halfVector/=abs(halfVector);
      float half=std::max(0.0f, dot(normal,halfVector));
      float powerFactor=std::pow(half, material.exponent);
      Color specular=light->specular*material.specular*powerFactor*attenuation;
      color+=specular;
    }
    color+=diffuse;    
  }
  return color;
}

PhongShaderWithShadow::PhongShaderWithShadow(Scene& scene)
 :scene(scene)
{
  topGroup=scene.getTopGroup();
}

Color
PhongShaderWithShadow::doShading(Ray& ray)
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
    color+=ambient;
    float normalLight=dot(normal,lightVector);
    if (normalLight<=0.0f)
      continue;
    Ray shadowRay;
    shadowRay.origin=hitPoint;
    shadowRay.direction=lightVector;
    shadowRay.distance=distance;
    shadowRay.hitObject=ray.hitObject;
    topGroup->intersection(shadowRay);
    if(shadowRay.distance < distance) //in shadow
      continue;
    Color diffuse=light->diffuse*(material.diffuse)*(normalLight*attenuation);
    
    if(material.exponent!=0.0f){
      Vec3f halfVector=lightVector-ray.direction;
      //halfVector.normalize(); //change to new math library
      halfVector/=abs(halfVector);
      float half=std::max(0.0f, dot(normal,halfVector));
      float powerFactor=std::pow(half, material.exponent);
      Color specular=light->specular*material.specular*powerFactor*attenuation;
      color+=specular;
    }
    color+=diffuse;
  }
  return color;
}
