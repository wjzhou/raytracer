/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: ImageBuffer.hpp Tue Jan 31 15:21:27 2012 wujun $
 * 
 *
 * 
 */

#ifndef _IMAGEBUFFER_H_
#define _IMAGEBUFFER_H_

#include "config.hpp"
#include "common.hpp"
#include "ImageOutputAdaptor.hpp"
class ImageBuffer
{
public:
  ImageBuffer(int width,int height);
  void setColor(int x,int y,Color color);
  void setDepth(int x,int y,float depth);
  virtual void outputImage(std::string& output);
  virtual void outputDepth(std::string& depth);
  virtual ~ImageBuffer(){};

  int width;
  int height;
  Pixel* buffer;
  float* zbuffer;
  ImageOutputAdaptor* iout;

};

#endif /* _IMAGEBUFFER_H_ */
