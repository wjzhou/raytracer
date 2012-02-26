/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Object3D.hpp Thu Feb  9 21:53:00 2012 wujun $
 * 
 *
 * Object3D is the base class for all the object in scene
 */
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include "common.hpp"
#include "Ray.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
class Ray;
class Object3D
{
public:
  enum Result{RESULT_HIT,RESULT_MISS,RESULT_INSIDE};
  Object3D();
  virtual ~Object3D(){};
  virtual Object3D::Result intersection(Ray& ray)=0;
  virtual Vec3f getNormal(Vec3f& hitPoint)=0;
  virtual int getMaterialIndex(){return materialIndex;}
  virtual void setMaterialIndex(int index){materialIndex=index;}
private:
  int materialIndex;
#ifdef DEBUG
  int num;
  static int totleNum; //for debug
#endif /*DEBUG*/
};

class Sphere : public Object3D
{
public:
  Sphere(Vec3f center, float radius);
  inline virtual Object3D::Result intersection(Ray& ray);
  virtual Vec3f getNormal(Vec3f& hitPoint);
private:
  Vec3f center;
  float radius;
  float radius2;//squre of radius
  float rradius;//reciprocal of radius
  
};

class Plane : public Object3D
{
public:
  Plane(Vec3f normal, float offset);
  virtual Object3D::Result intersection(Ray& ray);
  virtual Vec3f getNormal(Vec3f& hitPoint);
private:
  Vec3f normal;
  float moffset;  //-offset
};

class Triangle : public Object3D
{
public:
  Triangle(Vec3f a, Vec3f b, Vec3f c);
  virtual Object3D::Result intersection(Ray& ray);
  virtual Vec3f getNormal(Vec3f& hitPoint);
private:
  Vec3f a;
  Vec3f b;
  Vec3f c;
  Vec3f normal;
  float A1[4];
};

class Group : public Object3D
{
public:
  explicit Group(int size):data(size){};
  virtual ~Group(){};
  virtual Object3D::Result intersection(Ray& ray);
  virtual Vec3f getNormal(Vec3f& hitPoint);
  size_t getSize(){return data.size();}
  void addObject3D(Object3D* object3D);
private:
  int size;
  boost::ptr_vector<Object3D> data;
};

#endif /* _OBJECT3D_H_ */

