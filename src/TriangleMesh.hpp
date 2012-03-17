#ifndef _TRIANGLEMESH_H_
#define _TRIANGLEMESH_H_

#include "Object3D.hpp"
#include <cassert>
#include <boost/foreach.hpp>
#define foreach         BOOST_FOREACH
class Vertex{
public:
  Vec3f position;
  Vec3f normal;
  int Materialindex;
  Vertex(Vec3f& position)
     :position(position)
  {

  }
  Vertex(float x,float y,float z)
    :position(Vec3f(x,y,z))
  {

  }
};
class TriangleFace: public Triangle
{
  int a;
  int b;
  int c;
  TriangleFace(Vec3f& pa, Vec3f& pb, Vec3f& pc, int a, int b, int c)
    :Triangle(pa,pb,pc),a(a),b(b),c(c){}
  TriangleFace(Vec3f& pa, Vec3f& pb, Vec3f& pc)
    :Triangle(pa,pb,pc){};
};

template <typename TMVertex,typename TMFace>
class TriangleMesh : public Object3D
{
public:
  TriangleMesh(std::vector<TMVertex> vertexs,std::vector<TMFace> faces);
  virtual Object3D::Result intersection(Ray& ray);
  virtual Vec3f getNormal(Vec3f& hitPoint);
private:
  std::vector<TMVertex> vertexs;
  std::vector<TMFace> faces;
};

template <typename TMVertex,typename TMFace>
TriangleMesh<TMVertex, TMFace>::TriangleMesh(std::vector<TMVertex> vertexs,std::vector<TMFace> faces)
  :vertexs(vertexs),faces(faces)
{
}

/* n.(o+td-a)=0
 * t=n.(a-o)/n.d  
 */
template <typename TMVertex,typename TMFace>
Object3D::Result
TriangleMesh<TMVertex, TMFace>::intersection(Ray& ray)
{
  foreach(TMFace& f, faces)
    f.intersection(ray);
  
  return Object3D::RESULT_MISS;
}

template <typename TMVertex,typename TMFace>
Vec3f
TriangleMesh<TMVertex, TMFace>::getNormal(Vec3f& hitPoint)
{
  //getNormal of TriangleMesh invoked, something must wrong.");
  assert (true);
  exit(-4);  //for the warning message
}

#endif /* _TRIANGLEMESH_H_ */
