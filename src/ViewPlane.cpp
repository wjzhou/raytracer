#include "ViewPlane.hpp"
ViewPlane::ViewPlane(Vec3f& center, Vec3f& direction, Vec3f& up,
                     float width, float height, float pixelsize, float dist)
{
  //cout<<"ViewPlane center:"<<center<<" width:"<<width<<" height:"<<height<<" pixelsize: "<<pixelsize<<endl<<" direction:"<<direction<<" up:"<<up<<endl;
  //direction.normalize(); //change to new math library
  direction/=abs(direction);
  //up.normalize(); //change to new math library
  up/=abs(up);
  Vec3f xaxis=cross(direction,up); // x=y cross z, because up is -y, change the order 
  Vec3f down=cross(direction,xaxis); 
  /** although xaxis and down should be unit length by principle,
   *  normalnize again for round off.
   */
  //xaxis.normalize(); //change to new math library
  xaxis/=abs(xaxis);
  //down.normalize(); //change to new math library
  down/=abs(down);
  //cout<<"ViewPlane1 xasix:"<<xaxis<<"down: "<<down<<endl;
  Vec3f centerOfview=center+direction*dist;

  dxaxis=pixelsize*xaxis;  
  dyaxis=pixelsize*down;
  leftTop=centerOfview-(width-pixelsize)/2*xaxis-(height-pixelsize)/2*down;
  //cout<<"ViewPlane2 dx:"<<dxaxis<<" dy:"<<dyaxis<<" lefttop:"<<leftTop<<endl;  
}
