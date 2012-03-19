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
#include "Scene.hpp"
Scene* Object3D::scenep;//this must been set before use
Object3D::Object3D()
{
  materialIndex=0;
#ifdef DEBUG
  num=totalNum++;
#endif
}
#ifdef DEBUG
int Object3D::totalNum = 0;
#endif

Material&
Object3D::getMaterial()
{
  return scenep->getMaterial(materialIndex);
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
  if (ray.hitObject == this)
    return Object3D::RESULT_MISS;
  Vec3f v=ray.origin-center;
  float b=-dot(v,ray.direction);
  float det=(b*b)-dot(v,v)+radius2;
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

Plane::Plane(Vec3f normal, float offset)
 :normal(normal),moffset(offset)
{
}

/* n.(o+td)=-f
 * t=-f-n.o/n.d  
 */
Object3D::Result
Plane::intersection(Ray& ray)
{
  float t=(moffset-dot(normal,ray.origin))/dot(normal,ray.direction); //divid 0 is ok
  if(ray.hitObject!=this && t>EPSILON_BOUNUS && t< ray.distance){                               //for ieee745
    ray.distance=t;
    ray.hitObject=static_cast<Object3D *>(this);
    return Object3D::RESULT_HIT;
  }
  return Object3D::RESULT_MISS;
}

Vec3f
Plane::getNormal(Vec3f& hitPoint)
{
  return normal;
}

// Triangle::Triangle(Vec3f a, Vec3f b, Vec3f c)
//   :a(a),b(b),c(c)
// {
//   normal=(b-a).cross(c-a);
//   normal.normalize();
//   float A1_D=(a.x-b.x)*(a.y-c.y)-(a.x-c.x)*(a.y-b.y);
//   A1[0]=(a.y-c.y)/A1_D;
//   A1[1]=(b.y-a.y)/A1_D;
//   A1[2]=(c.x-a.x)/A1_D;
//   A1[3]=(a.x-b.x)/A1_D;
// }

// /* n.(o+td-a)=0
//  * t=n.(a-o)/n.d  
//  */
// Object3D::Result
// Triangle::intersection(Ray& ray)
// {
//   float t=(normal.dot(a-ray.origin))/(normal.dot(ray.direction));
//   //  cout<<"t"<<t<<endl;
//   if(t>0 && t<ray.distance){
//     Vec3f hitPoint=ray.origin+t*ray.direction;
//     float y[2];
//     y[0]=a.x-hitPoint.x;
//     y[1]=a.y-hitPoint.y;
    
//     float beta=A1[0]*y[0]+A1[1]*y[1];
//     if (beta>0 && beta<1){
//       float garma=A1[2]*y[0]+A1[3]*y[1];
//       if (garma>0 && beta+garma<1){
//         ray.distance=t;
//         ray.hitObject=static_cast<Object3D *>(this);
//         return Object3D::RESULT_HIT;
//       }
//     }
//   } 
//   return Object3D::RESULT_MISS;
// }

// Vec3f
// Triangle::getNormal(Vec3f& hitPoint)
// {
//   return normal;
// }


Triangle::Triangle(Vec3f& a, Vec3f& b, Vec3f& c)
  :a(a)
{
  normal=cross((b-a),(c-a));
  normal=norm(normal);
  A=a-b;
  B=a-c;
  AB.x=A(1)*B(2)-A(2)*B(1);
  AB.y=A(2)*B(0)-A(0)*B(2);
  AB.z=A(0)*B(1)-A(1)*B(0);
}

/* 
 * 
 */
Object3D::Result
Triangle::intersection(Ray& ray)
{
  float A_D=1/dot(ray.direction,AB);
  Vec3f O=a-ray.origin;
  float t=A_D*dot(O,AB);
  Vec3f& d=ray.direction;

  //  cout<<"t"<<t<<endl;
  if(ray.hitObject!=this && t>EPSILON_BOUNUS && t<ray.distance){
    float x0=O(1)*d(2)-O(2)*d(1);
    float x1=O(0)*d(2)-O(2)*d(0);
    float x2=O(0)*d(1)-O(1)*d(0);
    float beta=(-B(0)*x0+B(1)*x1-B(2)*x2)*A_D;
    if (beta>=0.0f && beta<=1.0f){
      float garma=(A(0)*x0-A(1)*x1+A(2)*x2)*A_D;
      if (garma>=0.0f && beta+garma<=1.0f){
        ray.distance=t;
        ray.hitObject=static_cast<Object3D *>(this);
        return Object3D::RESULT_HIT;
      }
    }
  } 
  return Object3D::RESULT_MISS;
}

Vec3f
Triangle::getNormal(Vec3f& hitPoint)
{
  return normal;
}

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

