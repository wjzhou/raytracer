/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: common.hpp Wed Feb  8 20:53:23 2012 wujun $
 * 
 *
 * 
 */
#ifndef _COMMON_H_
#define _COMMON_H_
#include "config.hpp"
#include "math/include/math/matrix.h"


typedef math::vector<3> Vec3f;
typedef math::vector<3> Color;

const float EPSILON=0.0001f;
const int TRACEDEPTH=6;

typedef unsigned int Pixel;
extern float garg_max_depth;
extern bool garg_override_xres;
extern int garg_xres;
extern int garg_yres;
extern bool garg_disable_gm;

extern const float UNDEFINEDF;
extern bool garg_override_pixelsize;
extern float garg_pixelsize;
extern bool garg_contrast_enhance;

extern bool garg_verbose;
extern bool garg_debug_trace_parsing;
extern bool garg_debug_trace_lexing;
extern long garg_debug_flage;
const int DEBUG_PARSER=1;
#define DTEST(select) (garg_debug_flage&(1<<select))
#define DSET(select)              \
do                                \
  garg_debug_flage|=(1<<select);  \
while (false);

#define ASSERT_MSG(TST,MSG)					\
		( (TST) ? (void)0				\
          : (std::cerr << __FILE__ "(" << __LINE__	\
				<< "): Assertion failed " #TST	\
             << MSG << std::endl,abort()))
#define PRECONDITION(TST,MSG) ASSERT_MSG(TST,"Precondition " << MSG)

#ifdef DEBUG
#  define POSTCONDITION(TST,MSG) ASSERT_MSG(TST,"Postcondition " << MSG)
#  define INVARIANT(TST,MSG) ASSERT_MSG(TST,"Invariant " << MSG)
#else
#  define POSTCONDITION(TST,MSG) ((void)0)
#  define INVARIANT(TST,MSG) ((void)0)
#endif /* DEBUG */

#endif /* _COMMON_H_ */
