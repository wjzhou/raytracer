#ifndef _RANDOM3D_H_
#define _RANDOM3D_H_
#include <random>
#include "common.hpp"

class Random3D
{
public:
  virtual void getRandom(Vec3f& result)=0;
  virtual void getRandomNormal(Vec3f& result, const Vec3f& normal)=0;
  virtual ~Random3D(){};
};

class DiffuseRandom: public Random3D
{
public:
  virtual void getRandom(Vec3f& result)=0;
  virtual void getRandomNormal(Vec3f& result, const Vec3f& normal)=0;
  virtual ~DiffuseRandom(){};
};

class RejectDiffuseRandom: public DiffuseRandom
{
  virtual void getRandom(Vec3f& result);
  virtual void getRandomNormal(Vec3f& result, const Vec3f& normal);
  ~RejectDiffuseRandom(){};
private:
  std::default_random_engine engine;
  std::uniform_real_distribution<float> distribution;  
};

class SimpleDiffuseRandom: public DiffuseRandom
{
public:
  virtual void getRandom(Vec3f& result);
  virtual void getRandomNormal(Vec3f& result, const Vec3f& normal);
  virtual ~SimpleDiffuseRandom(){};
private:
  std::default_random_engine engine;
  std::uniform_real_distribution<float> distribution;  
};  

#endif /* _RANDOM3D_H_ */
