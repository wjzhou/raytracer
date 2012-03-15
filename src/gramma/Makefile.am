# This file is modified from bison 2.5 c++ example because I can not get the 
# automake's default bison support works right for me.

# Compile the parser and save cycles.
# This code comes from "Handling Tools that Produce Many Outputs",
# from the Automake documentation.

EXTRA_DIST =					\
  $(srcdir)/bison.stamp  			\
  $(srcdir)/SceneParser.ypp			\
  $(srcdir)/SceneScanner.lpp

$(srcdir)/bison.stamp: $(srcdir)/SceneParser.ypp $(srcdir)/SceneScanner.lpp
	@rm -f bison.tmp
	@touch bison.tmp
	bison -d -ra -S lalr1.cc -o $(srcdir)/SceneParser.cpp \
	  $(srcdir)/SceneParser.ypp
	flex -o $(srcdir)/SceneScanner.cpp $(srcdir)/SceneScanner.lpp 
	@mv -f bison.tmp $@

CLEANFILES = $(srcdir)/*.output *.tmp
BUILT_SOURCES = $(bison_sources_generated)
$(bison_sources_generated): $(srcdir)/bison.stamp
	@if test -f $@; then :; else \
	  rm -f $(srcdir)/bison.stamp && \
	  $(MAKE) $(AM_MAKEFLAGS) $(srcdir)/bison.stamp; \
	fi

noinst_LTLIBRARIES = libgramma.la
noinst_HEADERS = $(srcdir)/ParseDriver.hpp $(srcdir)/ply/TrianglePly.hpp \
                 $(srcdir)/ply/ply_parser.hpp $(srcdir)/ply/ply.hpp      \
		 $(srcdir)/ply/io_operators.hpp $(srcdir)/ply/byte_order.hpp

gramma_sources = $(srcdir)/ParseDriver.cpp
bison_sources_generated = \
	$(srcdir)/stack.hh $(srcdir)/position.hh $(srcdir)/location.hh \
	$(srcdir)/SceneParser.hpp $(srcdir)/SceneParser.cpp $(srcdir)/SceneScanner.cpp
libgramma_la_CPPFLAGS = -I../math/include
libgramma_la_CXXFLAGS = $(STDCXX_0X) $(DEBUG_CXXFLAGS)
libgramma_la_SOURCES = $(srcdir)/ply/ply_parser.cpp $(gramma_sources) $(bison_sources_generated) 
