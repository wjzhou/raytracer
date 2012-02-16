/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Object3D.cpp Tue Jan 31 01:23:03 2012 wujun $
 * 
 *
 * implement the 3D objects
 */

#include <cmath>
#include "Object3D.hpp"
#include "common.hpp"

Object3D::Object3D()
{
  materialIndex=0;
#ifdef DEBUG
  num=totleNum++;
#endif
}


Sphere::Sphere(Vec3f center, float radius)
 :center(center),radius(radius)
{
  radius2=radius*radius;
  rradius=1/radius;
}

/**
 * calculate the intersection point, and update distance member of ray object.
 *
 * for a ray, x=o+td and a sphere with center c, radius r,
 * we get (x-c)^2=r^2. Then, (td+(o-c))^2=r^2.
 * expand, get t^2d^2+2td(o-c)+(o-c)^2-r^2=0
 * thus t=d(o-c)+-det, det=(d(o-c))^2-(o-c)^2+r^2
 *
 * @param ray the input ray
 * 
 * @return if hit return Object3D::Hit
 */
Object3D::Result
Sphere::intersection(Ray& ray) 
{
  Vec3f v=ray.origin-center;
  float b=-DOT(v,ray.direction);
  float det=(b*b)-DOT(v,v)+radius2;
  //cout<<"direction"<<ray.direction<<"origin"<<ray.origin<<endl;
  //cout<<"center"<<center<<"radius"<<radius<<"det:"<<det<<endl<<endl;
  if (det<EPSILON) //it is not a good idea to compare with 0
    return Object3D::RESULT_MISS;
  //cout<<"center"<<center<<"radius"<<radius<<"det:"<<det<<endl;
  //cout<<"v:"<<v<<" b:"<<b<<"radius2:"<<radius2<<endl;
  //  det=std::sqrtf(det);
  det=sqrtf(det); //sqrtf is not in std:: space,why?
  float hit1=b-det;
  float hit2=b+det;
  //cout<<"hit1"<<hit1<<" hit2:"<<hit2<<endl;
  if(hit2>0){
    if(hit1<=0 && hit2< ray.distance){
      //inside should be invisible
      //state.hitObject=static_cast<const Object3D *>(this);
      //state.distance=hit2;
      return Object3D::RESULT_INSIDE;
    }
    if(hit1>0 && hit1< ray.distance){
      ray.distance=hit1;
      ray.hitObject=static_cast<Object3D *>(this);
      return Object3D::RESULT_HIT;
    }
  }
  return Object3D::RESULT_MISS;   
}

inline Vec3f
Sphere::getNormal(Vec3f& hitPoint)
{
  return (hitPoint-center)*rradius;
}


// /**
//  * calculate the intersection point, and update distance member of ray object.
//  *
//  * for a ray, x=o+td and a plane with normal n, point a on the plane,
//  * we get n.(p-a)=0. Then, n.(o+td-a)=0.
//  * expand, get n.dt=n.(a-o)
//  * thus t=n.(a-o)/(n.d)
//  *
//  * @param ray the input ray
//  * 
//  * @return if hit return Object3D::Hit
//  */
// Object3D::Result
// Sphere::intersect(Ray& ray,TraceState& state) const
// {
//   Vec3f nd=DOT(normal,ray.direction);
//   if(nd<0.001)
//      return Object3D::Result::MISS;
  
//   float det=(b*b)-DOT(v,v)+radius2;
//   if (det<0)
//     return Object3D::Result::MISS;
//   //  det=std::sqrtf(det);
//   det=sqrtf(det); //sqrtf is not in std:: space,why?
//    float hit1=b-det;
//   float hit2=b+det;
//   if(hit2>0){
//     if(hit1<=0 && hit2< state.distance){
//       state.distance=hit2;
//       return Object3D::Result::INSIDE;
//     }
//     if(hit1>0 && hit1< state.distance){
//       state.distance=hit1;
//       state.hitObject=static_cast<const Object3D *>(this);
//       return Object3D::Result::HIT;
//     }
//   }
//   return Object3D::Result::MISS;   
// }



inline Object3D::Result
Group::intersection(Ray& ray)
{
  
  //Gcc 4.5 does not support range-based for
  boost::ptr_vector<Object3D>::iterator it;
  for (it=data.begin(); it < data.end(); it++ )
    (it)->intersection(ray);
  //don't know if this is useful..
  return Object3D::RESULT_MISS;
}

Vec3f
Group::getNormal(Vec3f& hitPoint)
{
  //ASSERT_MSG(true,"getNormal of Group invoked, something must wrong.");
  exit(3);
}

void
Group::addObject3D(Object3D* object3D)
{
  data.push_back(object3D);
}

