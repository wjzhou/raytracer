#include "math.hpp"
#include "Shader.hpp"
#include "Material.hpp"

Color
SimpleDiffuseShader::doShading(Ray& ray)
{
  Vec3f hitPoint=ray.origin+ray.distance*ray.direction;
  Vec3f normal=ray.hitObject->getNormal(hitPoint);
  Material& material=ray.hitObject->getMaterial();
  return DOT(normal,-ray.direction)*(material.diffuseColor);
}
