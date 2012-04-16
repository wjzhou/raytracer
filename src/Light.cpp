#include "Light.hpp"
void
PointLight::getLightVector2(Vec3f& result, float& a_power,float& distance, const Vec3f& hitPoint)
{
  result=position-hitPoint;
  float dist2=abs_squared(result);
  a_power=power;
  result=norm(result);
  a_power=power;
}

void
AreaLight::getLightVector2(Vec3f& result, float& a_power,float& a_distance, const Vec3f& hitPoint)
{
  float e1=distribution(engine);
  float e2=distribution(engine);
  result=o+e1*a+e2*b-hitPoint;
  a_distance=abs(result);
  result=result/a_distance;
  a_power=power*dot(result,normal);
}
