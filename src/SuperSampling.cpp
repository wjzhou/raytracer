#include "SuperSampling.hpp"
#include <iostream>
#include <functional>

int SuperSampling::samples=1;

SuperSampling*
SuperSampling::getSuperSampling(Method method, int samples,Vec3f& dx,Vec3f& dy)
{
  SuperSampling::samples=samples;
  switch (method)
    {
    case Method::grid:
      return new GridSuperSampling(dx,dy);
    case Method::random:
      return new RandomSuperSampling(dx,dy);
    case Method::poisson_disc:
      return new RandomSuperSampling(dx,dy);
    case Method::jitter:
      return new JitterSuperSampling(dx,dy);
    case Method::rotated_grid:
      return new RotatedGridSuperSampling(dx,dy);
    default:
      return NULL;
    }
}
SuperSampling*
SuperSampling::getSuperSamplingByName(std::string& name, int samples,Vec3f& dx,Vec3f& dy)
{
  Method method=Method::grid;;
  if (name=="grid")
    method=Method::grid;
  else if (name=="random")
    method=Method::random;
  else if (name=="poisson_disc")
    method=Method::poisson_disc;
  else if (name=="jitter")
    method=Method::jitter;
  else if (name=="rotated_grid")
    method=Method::rotated_grid;
  else
    std::cout<<"Unknown SuperSampling method:"<<name<<", use grid instead";
  return getSuperSampling(method,samples,dx,dy);
}

void
GridSuperSampling::init(Vec3f& dx,Vec3f& dy)
{
  int colums=std::sqrt(samples);
  if (colums*colums!=samples){
    std::cerr<<"superSampling number of samples must be perfect square number\
for grid method."<<std::endl;
    std::exit(5);
  }
  adjust=new Vec3f[samples];
  Vec3f lefttop=-(dx/2.0f)-(dy/2.0f);
  Vec3f sx=dx/(float)colums;
  Vec3f sy=dy/(float)colums;
  Vec3f current;
  for (int i=0;i<colums;i++){
    current=lefttop+sx/2.0f+sy*(i+0.5f);
    for (int j=0;j<colums;j++){
        adjust[i*colums+j]=current;
        current+=sx;
      }
  }
}

GridSuperSampling::GridSuperSampling(Vec3f& dx,Vec3f& dy)
{
  init(dx,dy);
}

Vec3f
GridSuperSampling::adjustPosition(const int i)
{
  return adjust[i];
}

RandomSuperSampling::RandomSuperSampling(Vec3f& dx,Vec3f& dy)
  :dx(dx),dy(dy),distribution(-0.5f,0.5f)
{
}

Vec3f
RandomSuperSampling::adjustPosition(const int i) 
{
  float r1=distribution(engine);
  float r2=distribution(engine);
  return dx*r1+dy*r2;
}


JitterSuperSampling::JitterSuperSampling(Vec3f& dx,Vec3f& dy)
  :GridSuperSampling(dx,dy),dx(dx),dy(dy),distribution(0.5f/std::sqrt(samples),0.5f/std::sqrt(samples))
{
}

Vec3f
JitterSuperSampling::adjustPosition(const int i) 
{
  float r1=distribution(engine);
  float r2=distribution(engine);
  return dx*r1+dy*r2+adjust[i];
}

RotatedGridSuperSampling::RotatedGridSuperSampling(Vec3f& dx,Vec3f& dy)
{
  float cos=std::cos(options.getRotatedGridAngleSuperSampling());
  float sin=std::sin(options.getRotatedGridAngleSuperSampling());
  Vec3f rotatedDx=dx*cos+dy*sin;
  Vec3f rotatedDy=dx*(-sin)+dy*cos;
  init(rotatedDx,rotatedDy);
}


