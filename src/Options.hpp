/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Options.hh Sun Jan 29 01:17:55 2012 wujun $
 * 
 *
 * Parsing the command options.
 */
#ifndef _OPTIONS_H_
#define _OPTIONS_H_
#include <string>
class Options
{
public:
  Options(){};
  virtual ~Options(){};
  int parse(int argc, char* argv[]);
  std::string& getInputFileName();
  std::string& getOutputFileName();
  std::string& getOutputDepthFileName();
  std::string& getShadingMethod();
  //int getXres(){return xres;}
  //int getYres(){return yres;}
private:
  std::string input;
  std::string output;
  std::string depth;
  std::string shadingMethod;
  //int xres;
  //int yres;
  std::string config_file;
};


#endif /* _OPTIONS_H_ */
