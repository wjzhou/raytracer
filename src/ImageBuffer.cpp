/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: ImageBuffer.cpp Tue Jan 31 15:27:40 2012 wujun $
 * 
 *
 * 
 */

#include <cmath>
#include <iostream>
#include "common.hpp"
#include "ImageBuffer.hpp"

ImageBuffer::ImageBuffer(int width,int height)
    :width(width),height(height)
{
  int totalPixel=width*height;
  buffer=new Pixel[totalPixel];
  zbuffer=new float[totalPixel];
  for (int i=0;i<totalPixel;i++)
    zbuffer[i]=0.0f;
#ifdef HAVE_GM
  if(garg_disable_gm)
    iout=new PPMOutputAdaptor();
  else
    iout=new GMOutputAdaptor();
#else
  iout=new PPMOutputAdaptor();
#endif
}
void
ImageBuffer::setColor(int x,int y,Color color)
{    
  int cr=std::floor(color.x*255);
  if(cr>255)
    cr=255;
  int cg=std::floor(color.y*255);
  if(cg>255)
    cg=255;
  int cb=std::floor(color.z*255);
  if(cb>255)
    cb=255;
  buffer[x+y*width]=((cr&255)<<16)|((cg&255)<<8)|(cb&255);
}

void
ImageBuffer::setDepth(int x,int y,float depth)
{
  float normal=depth/garg_max_depth;
  float invese=1.0-normal;
  zbuffer[x+y*width]=(invese<0.0f)?0.0f:invese;
}

void
ImageBuffer::outputImage(string& output)
{
  iout->output(output,buffer,width,height,
              ImageOutputAdaptor::OUTPUT_FORMAT_ARGB);
}

void
ImageBuffer::outputDepth(string& depth)
{
  iout->output(depth,zbuffer,width,height,
              ImageOutputAdaptor::OUTPUT_FORMAT_GRAY);
}


