/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Options.cpp Sun Jan 29 01:17:55 2012 wujun $
 * 
 *
 * implement the command line parsing
 */
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include "common.hpp"
#include "Options.hpp"
namespace po = boost::program_options;
using namespace std;
float garg_max_depth;
bool garg_override_xres=false;
int garg_xres;
int garg_yres;
bool garg_disable_gm;

const float UNDEFINEDF=-1;
bool garg_override_pixelsize=false;
float garg_pixelsize;
bool garg_contrast_enhance;

bool garg_verbose;
bool garg_debug_trace_lexing=false;
bool garg_debug_trace_parsing=false;
long garg_debug_flage;

#define DTEST(select) (garg_debug_flage&(1<<select))
#define DSET(select)              \
do                                \
  garg_debug_flage|=(1<<select);  \
while (false);

static void usage(char* pname)
{
  cout<<"This is a simple raytracer for cs566."<<endl;
  cout<<"Usage:"<<pname<<" -i input -o output.tiff -d depth.tiff\n"<<endl;
}


int
Options::parse(int argc, char* argv[])
{

  po::options_description generic("Generic options");
  generic.add_options()
    ("help,h", "produce help message")
    ("version,V", "print version string")
    ("config,c", po::value<string>(&config_file)->default_value("multiple_sources.cfg"),
     "name of a file of a configuration.")
    ("verbose,v",po::bool_switch(&garg_verbose),"output more message(verbose)")
    ;

  po::options_description required("Required options");
  required.add_options()
    ("input,i", po::value<string>(&input), "set input file name")
    ("output,o", po::value<string>(&output)->default_value("output.ppm"), "set output file name")
    ("depth,d", po::value<string>(&depth)->default_value("depth.pgm"), "set depthfile file name");
    //    ("resolution,r", po::value<string>(), "set raytracer's resolution");
    //("Width,xres,W", po::value<int>(&xres)->default_value(1000), "set raytracer's horizontal resolution")
    //("Height,yres,H", po::value<int>(&yres)->default_value(1000), "set raytracer's vertical resolution");
  

  po::options_description perspective("Perspective Camera options");
  perspective.add_options()
    ("xres,x", po::value<int>(&garg_xres)->default_value(1000), "Set the horizontal resolution. ")
    ("yres,y", po::value<int>(&garg_yres)->default_value(1000), "Set the vertical resolution. ");
  
  po::options_description orthographic ("Orthographic Camera options");
  orthographic.add_options()
    ("pixelsize,p", po::value<float>(&garg_pixelsize)->default_value(0.005f), "Override the pixelsize setting in file");
  
  po::options_description misc("Miscellaneous options");
  misc.add_options()
    ("maxdepth,m", po::value<float>(&garg_max_depth)->default_value(20.0f), "set the max depth(used for computing gray level in depth file).")
    ("disable-gm", po::bool_switch(&garg_disable_gm), "whether avoid using graphicsmagick when it is available.")
    ("contrastEnhance", po::bool_switch(&garg_contrast_enhance), "whether using contrast stretch to improve dynamic of depth image when possible.")
    ("debugParser,P", po::bool_switch(&garg_debug_trace_parsing),"turn on parser debug")
    ("debugLexer,L",po::bool_switch(&garg_debug_trace_lexing),"turn on lexer debug")
    ;
    
  po::options_description all("All allowed options");
  all.add(generic).add(required).add(perspective).add(orthographic).add(misc);

  po::options_description show("Options");
  show.add(generic).add(required);
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, all), vm);
  po::notify(vm);
  ifstream ifs(config_file.c_str());
  if (ifs){
    po::store(parse_config_file(ifs, required), vm);
    po::notify(vm);
  }
  if (vm.count("version")) {
    cout << "raytracer, version 0.2\n";
    exit(0);
  }

  if (vm.count("help")){
    usage(argv[0]);
    cout<<all<<endl;
    exit(0);
  }
  
  if (!vm.count("input")){
    usage(argv[0]);
    cout<<show<<endl;
    exit(1);
  }

  if (vm.count("xres")){
    garg_override_xres=true;
  }
  if (vm.count("pixelsize")){
    garg_override_pixelsize=true;
  }
  //  if (vm.count("debugParser")){
    //DSET(DEBUG_PARSER);
  //}
  cout<<"Option parse has been completed."<<endl;
  return 0;  
}

std::string& Options::getInputFileName()
{
  return input;
}

std::string& Options::getOutputFileName()
{
  return output;
}
std::string& Options::getOutputDepthFileName()
{
  return depth;
}




/*
int main(int argc, char *argv[])
{
  try
    {
      Options opt;
      opt.parse(argc,argv);
      Scene scene;
      ParseDriver pd(scene);
      pd.parse(opt.getInputFileName());
      ImageBuffer image(width,height);
      Raytracer tracer=Raytracer(scene,image);
      tracer.doRaytrace();
      
  std::fstream fs(opt.getOutputFileName);
  fs<<"P3"<<endl<<width<<" "<<height<<endl;
  fs<<"255"<<endl;
  int i,j;
  for(j=0;j<height;j++){
    for(i=0;i<width;i++){
      Pixel px=image.buffer[i+j*width];
      //cout<<"pix x="<<i<<",y="<<j<<":"<<(px>>16)<<" "<<((px>>8)&255)<<" "<<(px&255)<<endl;
      fs<<(px>>16)<<" "<<((px>>8)&255)<<" "<<(px&255)<<" ";
      
    }
    fs<<endl;
  }
    }
  catch(exception& e) {
    cerr << "error: " << e.what() << "\n";
  }
  catch(...) {
    cerr << "Exception of unknown type!\n";
  }
  return 0;
}

*/
