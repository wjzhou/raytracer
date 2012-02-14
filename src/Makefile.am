bin_PROGRAMS = raytracer
raytracer_SOURCES = Raytracer.cpp ImageBuffer.cpp Object3D.cpp ViewPlane.cpp Options.cpp Camera.cpp Scene.cpp ImageOutputAdaptor.cpp main.cpp 
noinst_HEADERS=Camera.hpp ImageOutputAdaptor.hpp math.hpp Ray.hpp Transformation.hpp common.hpp Light.hpp Object3D.hpp Raytracer.hpp ViewPlane.hpp ImageBuffer.hpp Material.hpp Options.hpp Scene.hpp

raytracer_CPPFLAGS = $(BOOST_CPPFLAGS) $(GM_CPPFLAGS) -I$(top_srcdir)/gramma
raytracer_CXXFLAGS =  $(GM_CXXFLAGS) $(DEBUG_CXXFLAGS)
raytracer_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS) $(GM_LDFLAGS)
raytracer_LDADD = gramma/libgramma.la $(BOOST_PROGRAM_OPTIONS_LIBS) $(GM_LIBS)
SUBDIRS = gramma

#raytracer_SOURCES += ImageOut
#putAdaptorGraphicMagic.o
#ImageOutputAdaptorGraphicMagic.o: ImageOutputAdaptorGr#aphicMagic.cpp
#	$(CXX) -o $@  $? GCFLAGS
#noinst_PROGRAMS = $(DBG)
