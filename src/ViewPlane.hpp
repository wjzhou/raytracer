/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: ViewPlane.hpp Sun Jan 29 22:47:48 2012 wujun $
 * 
 *
 * 
 */
#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_
#include "common.hpp"
struct ViewPlane
{
public:
  ViewPlane(){}; //needed for been embedded in other class
  ViewPlane(Vec3f& center, Vec3f& direction, Vec3f& up, float width,float hight,float pixelsize,float dist);
  Vec3f leftTop;
  Vec3f dxaxis;
  Vec3f dyaxis;
};
#endif /* _VIEWPLANE_H_ */
