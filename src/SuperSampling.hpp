#ifndef _SUPERSAMPLING_H_
#define _SUPERSAMPLING_H_
#include "common.hpp"
#include <random>
class SuperSampling
{
public:
  static int samples;
  enum class Method{grid,random,poisson_disc,jitter,rotated_grid};
  static SuperSampling* getSuperSampling(Method method, int samples, Vec3f& dx, Vec3f& dy);
  static SuperSampling* getSuperSamplingByName(std::string& method, int samples, Vec3f& dx, Vec3f& dy);
  
  int getSamplesPerPixel()const {return samples;}
  virtual Vec3f adjustPosition(const int i)=0;
  virtual ~SuperSampling(){};
};

class GridSuperSampling: public SuperSampling
{
public:
  GridSuperSampling(){};
  GridSuperSampling(Vec3f& dx,Vec3f& dy);
  void init(Vec3f& dx,Vec3f& dy); //used to subclass
  virtual Vec3f adjustPosition(const int i);
  virtual ~GridSuperSampling(){};
protected:
  Vec3f* adjust;
};

class RandomSuperSampling: public SuperSampling
{
public:
  RandomSuperSampling(Vec3f& dx,Vec3f& dy);
  virtual Vec3f adjustPosition(const int i);
  virtual ~RandomSuperSampling(){};
protected:
  Vec3f dx;
  Vec3f dy;
  std::mt19937 engine;
  std::uniform_real_distribution<float> distribution;
};

class JitterSuperSampling: public GridSuperSampling
{
public:
  JitterSuperSampling(Vec3f& dx,Vec3f& dy);
  virtual Vec3f adjustPosition(const int i);
  virtual ~JitterSuperSampling(){};
protected:
  Vec3f dx;
  Vec3f dy;
  std::mt19937 engine;
  std::uniform_real_distribution<float> distribution;
};

class RotatedGridSuperSampling: public GridSuperSampling
{
public:
  RotatedGridSuperSampling(Vec3f& dx,Vec3f& dy);
  virtual ~RotatedGridSuperSampling(){};
};

#endif /* _SUPERSAMPLING_H_ */
