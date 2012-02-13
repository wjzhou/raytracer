/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: ImageOutputAdaptor.hpp Sun Feb  5 22:34:30 2012 wujun $
 * 
 *
 * This is used to output ImageBuffer.
 * ImageOutputAdaptor Iout(string filename);
 * Iout<<image; //filename is the output file name
 */
#ifndef _IMAGEOUTPUTADAPTOR_H_
#define _IMAGEOUTPUTADAPTOR_H_
#include "config.hpp"
#include <string>
class ImageOutputAdaptor
{  
public:
  enum FORMAT{OUTPUT_FORMAT_ARGB,OUTPUT_FORMAT_GRAY};
  virtual int output(std::string& filename,void* buffer,
                     int width,int height,FORMAT format)=0;
  virtual ~ImageOutputAdaptor(){};
};


class PPMOutputAdaptor: public ImageOutputAdaptor
{
public:
  virtual int output(std::string& filename,void* buffer,int width,int height,FORMAT format);
  virtual ~PPMOutputAdaptor(){};
};

#ifdef HAVE_GM
class GMOutputAdaptor: public ImageOutputAdaptor
{
public:
  virtual int output(std::string& filename,void* buffer,int width,int height,FORMAT format);
  virtual ~GMOutputAdaptor(){};
};
#endif /* HAVE_GM */

#endif /* _IMAGEOUTPUTADAPTOR_H_ */
