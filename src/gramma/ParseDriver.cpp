/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: ParseDriver.cpp Fri Feb 10 13:09:52 2012 wujun $
 * 
 *
 * the first version lost, reimplment one
 */

#include "ParseDriver.hpp"
#include "SceneParser.hpp"
#include <iostream>

ParseDriver::ParseDriver (Scene& scene)
:scene(scene){}

int
ParseDriver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::SceneParser parser (*this);
  parser.set_debug_level (garg_debug_trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}
  
void
ParseDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void
ParseDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}


