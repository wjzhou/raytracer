#ifndef _PARSEDRIVER_H_
#define _PARSEDRIVER_H_

# include <string>
# include "../common.hpp" 
# include "../Scene.hpp"
# include "../Options.hpp"
//bison will generate this .h file...
# include "SceneParser.hpp" 
# include "location.hh"

  // Tell Flex the lexer's prototype ...
# define YY_DECL                                        \
  yy::SceneParser::token_type                         \
  yylex (yy::SceneParser::semantic_type* yylval,      \
         yy::SceneParser::location_type* yylloc,      \
         ParseDriver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Scene.
class ParseDriver
{
  friend class SceneParser;
public:
  ParseDriver (Scene& scene);
  Scene& getScene(){return scene;}
  int result;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;

  // Run the parser.  Return 0 on success.
  int parse (const std::string& f);
  std::string file;
  bool trace_parsing;

  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
  Scene& scene;
  int currentMaterialIndex;
  int baseMaterialIndex;
};
#endif // ! _PARSEDRIVER_H_
