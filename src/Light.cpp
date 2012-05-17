#include "Light.hpp"
#include "Scene.hpp"
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
AreaLight::initPosition(const Vec3f& a_o, const Vec3f& o1, const Vec3f& o2)
{
  o=a_o;
  a=o1-o;
  b=o2-o;
  normal=norm(cross(a,b));

  Material* mlight=new Material();
  mlight->diffuse=color;
  mlight->isLight=1;
  int index=gScene.addMaterial(mlight);
  gScene.newGroup(2);
  Triangle* t1=new Triangle(a_o,o1,o2);
  t1->isLight=1;
  t1->setMaterialIndex(index);
  gScene.addObject3D(t1);
  Vec3f oo=o+(o1-o)+(o2-o);
  Triangle* t2=new Triangle(oo,o2,o1);
  t2->isLight=1;
  t2->setMaterialIndex(index);
  gScene.addObject3D(t2);
  gScene.endGroup(2);
}

void
AreaLight::getLightVector2(Vec3f& result, float& a_power,float& a_distance, const Vec3f& hitPoint)
{
  float e1=distribution(engine);
  float e2=distribution(engine);
  result=o+e1*a+e2*b-hitPoint;
  a_distance=abs(result);
  result=result/a_distance;
  a_power=std::max(0.0f,(-power)*dot(result,normal));
}
