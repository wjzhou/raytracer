#ifndef _RANDOM3D_H_
#define _RANDOM3D_H_
#include <random>
#include "common.hpp"

class Random3D
{
public:
  virtual void getRandom(Vec3f& result);
  virtual ~Random3D();
};

class DiffuseRandom:Random3D
{
public:
  virtual void getRandom(Vec3f& result);
  virtual ~DiffuseRandom();
};

class RejectDiffuseRandom
{
  virtual void getRandom(Vec3f& result);
  ~RejectDiffuseRandom(){};
private:
  std::default_random_engine engine;
  std::uniform_real_distribution<float> distribution; 
};

  

#endif /* _RANDOM3D_H_ */
