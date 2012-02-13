#include "Options.hpp"
#include "Scene.hpp"
#include "gramma/ParseDriver.hpp"
#include "Raytracer.hpp"
int
main(int argc, char *argv[])
{
  
      Options opt;
      opt.parse(argc,argv);
      Scene scene;
      ParseDriver pd(scene);
      pd.parse(opt.getInputFileName());
      ImageBuffer image(garg_xres,garg_yres);
      Raytracer tracer=Raytracer(scene,image);
      tracer.doRaytrace();
      image.outputImage(opt.getOutputFileName());
      image.outputDepth(opt.getOutputDepthFileName());
      cout<<"render has been completed."<<endl;
      return 0;
}
