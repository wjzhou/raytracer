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
RejectDiffuseRandom::getRandomNormal(Vec3f& result, const Vec3f& normal)
{
  getRandom(result);
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

void
SimpleDiffuseRandom::getRandomNormal(Vec3f& result, const Vec3f& normal)
{
  Vec3f tmp;
  float e1=distribution(engine);
  float e2=distribution(engine);
  float part=2.0f*std::sqrt(e1*(1-e1));
  float theta=2.0f*M_PI*e2;
  tmp.x=std::cos(theta)*part;
  tmp.y=std::sin(theta)*part;
  tmp.z=1.0f-2.0f*e1;


  float cosfi=normal.z;
  float sinfi=std::sqrt(1.0f-normal.z*normal.z);
  if(sinfi<0.00001f)
    result=tmp;
  else{
    float costh=normal.x/sinfi;
    float sinth=normal.y/sinfi;
    tmp.x=costh*tmp.x-sinth*tmp.y;
    tmp.y=sinth*tmp.x+costh*tmp.y;

    if(tmp.x<0.0f)
      sinth=-sinth;
    
    result.x=cosfi*tmp.x+sinfi*tmp.z;
    result.y=tmp.y;
    result.z=-sinfi*tmp.x+cosfi*tmp.z;
  }
  
  
}
