#include "Options.hpp"
#include "Scene.hpp"
#include "gramma/ParseDriver.hpp"
#include "Raytracer.hpp"

int
main(int argc, char *argv[])
{
      options.parse(argc,argv);
      Scene scene;
      ParseDriver pd(scene);
      pd.parse(options.getInputFileName());
      ImageBuffer image(garg_xres,garg_yres);
      Shader* shaderp=Shader::getShader(options.getShadingMethod(),scene);

      Raytracer tracer=Raytracer(&scene,&image,shaderp);
      tracer.doRaytrace();
      image.outputImage(options.getOutputFileName());
      image.outputDepth(options.getOutputDepthFileName());
      cout<<"render has been completed."<<endl;
      delete shaderp;
      return 0;
}
