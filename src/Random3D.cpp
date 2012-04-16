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
  }while(len>1);
  result/=len;
}

