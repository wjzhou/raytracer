/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Shader.hpp Tue Feb 14 21:39:57 2012 wujun $
 * 
 *
 * This is the base class for shader.
 * Each shader can get the material normal from object3D
 */

#ifndef _SHADER_H_
#define _SHADER_H_
#include "Ray.hpp"
#include "Random3D.hpp"
class Shader
{
public:
  Shader(){}
  static Shader* getShader(std::string shadingMethod,Scene& scene);
  virtual Color doShading(Ray& ray)=0;
  virtual ~Shader(){};
};

class SimpleDiffuseShader : public Shader /* for efficent, do not use virtual function here*/
{
public:
  SimpleDiffuseShader(){};
  virtual Color doShading(Ray& ray);
  virtual ~SimpleDiffuseShader(){};
};

class PhongShader : public Shader /* for efficent, do not use virtual function here*/
{
public:
  PhongShader(Scene& scene)
    :scene(scene){};
  virtual Color doShading(Ray& ray);
  virtual ~PhongShader(){};
  Scene& scene;
};

class PhongShaderWithShadow : public Shader /* for efficent, do not use virtual function here*/
{
public:
  PhongShaderWithShadow(Scene& scene);
  virtual Color doShading(Ray& ray);
  virtual ~PhongShaderWithShadow(){};
  Scene& scene;
  Group* topGroup;
};

class PhotonMapping : public Shader /* for efficent, do not use virtual function here*/
{
public:
  PhotonMapping(Scene& scene);
  virtual Color doShading(Ray& ray);
private:
  Color doShading2(Ray& ray,int depth);
  Scene& scene;
  Group* topGroup;
  DiffuseRandom* diffuseRandom;
};

#endif /* _SHADER_H_ */
