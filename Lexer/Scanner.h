#pragma once

#include <Parser/YYTYPE.h>

#ifndef YY_DECL
#define YY_DECL                                                                \
  roe::Parser::token_type roe::Scanner::lex(                                   \
    roe::Parser::semantic_type* yylval, roe::Parser::location_type* yylloc)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer RoeFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include <Parser/Parser.h>
#include <Parser/YYTYPE.h>

namespace roe
{

  class Scanner : public RoeFlexLexer
  {
  public:
    Scanner(const std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);
    virtual ~Scanner();
    virtual Parser::token_type
    lex(Parser::semantic_type* yylval, Parser::location_type* yylloc);
    void set_debug(bool b);
  };
}
