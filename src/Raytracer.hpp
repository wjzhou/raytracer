/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Raytracer.hpp Thu Feb  9 21:05:00 2012 wujun $
 * 
 *
 * 
 */

#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_
#include "Scene.hpp"
#include "ImageBuffer.hpp"
#include "Shader.hpp"

class Raytracer
{
public:
  Raytracer(Scene* scenep, ImageBuffer* imagep, Shader* shaderp)
    :scenep(scenep),imagep(imagep),shaderp(shaderp){}
  
  void doRaytrace();
private:
  //this one will not be destroyed for the lifetime..
  Scene* scenep;
  ImageBuffer* imagep;
  Shader* shaderp;
};


#endif /* _RAYTRACER_H_ */
