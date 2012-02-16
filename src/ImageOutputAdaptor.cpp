#include "ImageOutputAdaptor.hpp"
#include <fstream>
#include <iostream>
#include <exception>
#include "common.hpp"
int
PPMOutputAdaptor::output(std::string& filename,void* buffer,
                         int width,int height,FORMAT format)
{
  std::ofstream fs(filename.c_str());
  if (!fs.is_open())
  {
    std::cerr << "Error opening file:"<<filename<<std::endl;
    return -1;
  }
  if(format==OUTPUT_FORMAT_ARGB)
    fs<<"P3\n"<<width<<' '<<height<<'\n';
  else if (format==OUTPUT_FORMAT_GRAY)
    fs<<"P2\n"<<width<<' '<<height<<'\n';
  fs<<"255\n";
  int i,j;
  for(j=0;j<height;j++){
    for(i=0;i<width;i++){
      if(format==OUTPUT_FORMAT_ARGB){
        int px=((int*)buffer)[i+j*width];
        int sum=((px>>16)&255)+((px>>8)&255)+((px)&255);
        fs<<((px>>16)&255)<<' '<<((px>>8)&255)<<' '<<(px&255)<<' ';
      }
      else if (format==OUTPUT_FORMAT_GRAY){
        int px=int(((float*)buffer)[i+j*width]*255);
        fs<<px<<' ';
      }
        
    }
    fs<<'\n';
  }
  fs.close();
  return 0;  
}


#ifdef HAVE_GM
#include <Magick++.h>
#include <iostream>
using namespace std;
using namespace Magick;
  
int
GMOutputAdaptor::output(std::string& filename,void* buffer,
                         int width,int height,FORMAT format)
{
  string map;
  MagickLib::StorageType storage;
  if(format==OUTPUT_FORMAT_ARGB){
    map="BGRO";//from low to high,B comes first,Opacity the last(gm constitute)
    storage=MagickLib::CharPixel;
  }
  else if (format==OUTPUT_FORMAT_GRAY){
    map="I"; //intensity or gray
    storage=MagickLib::FloatPixel;
  }
  
  InitializeMagick("raytrace");
  Image image;
  try {
    image.read(width,height,map,storage,buffer);
    if(format==OUTPUT_FORMAT_GRAY && garg_contrast_enhance){
      cerr<<"gray constrast enhance enabled."<<endl;
      image.normalize();
    }
    image.write(filename);
  }
  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }
  return 0;
  
}

#endif /*HAVE_GM*/
