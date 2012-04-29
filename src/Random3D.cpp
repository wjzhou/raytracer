#include "Random3D.hpp"
void
RejectDiffuseRandom::getRandom(Vec3f& result)
{
  float len;
  do{
    result.x=distribution(engine);
    result.y=distribution(engine);
    result.z=distribution(engine);
    len=abs(result);
  }while(len>1.0f);
  result/=len;
}

void
SimpleDiffuseRandom::getRandom(Vec3f& result)
{
  float e1=distribution(engine);
  float e2=distribution(engine);
  float part=2.0f*std::sqrt(e1*(1-e1));
  float theta=2.0f*M_PI*e2;
  result.x=std::cos(theta)*part;
  result.y=std::sin(theta)*part;
  result.z=1.0f-2.0f*e1;
}
