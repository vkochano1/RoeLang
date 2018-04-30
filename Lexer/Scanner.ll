/* $Id$ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */

%{ /*** C/C++ Declarations ***/

#include <string>

#include <Lexer/Scanner.h>

/* import the parser's token type into a local typedef */
typedef roe::Parser::token token;
typedef roe::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

%option c++
%option prefix="Roe"
%option batch
%option debug
%option yywrap nounput 
%option stack

%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%% /*** Regular Expressions Part ***/

%{
    // reset location
    yylloc->step();
%}

"if" {
    return token::IF_KEYWORD;
}

"else" {
    return token::ELSE_KEYWORD;
}

"ruleid" {
        return token::RULE_KEYWORD;
}

"and" {
        return token::AND_KEYWORD;
}

"or" {
        return token::OR_KEYWORD;
}

"not" {
        return token::NOT_KEYWORD;
}

"!=" {
        return token::NOT_EQUAL;
}

"==" {
        return token::EQUAL;
}

">" {
        return token::MORE;
}

"<" {
        return token::LESS;
}

">=" {
        return token::MORE_OR_EQUAL;
}

"<=" {
        return token::LESS_OR_EQUAL;
}

"+" {
        return token::PLUS;
}

"-" {
        return token::MINUS;
}

"*" {
        return token::MULT;
}

"/" {
        return token::DIV;
}

"," {
        return token::COMMA;
}

";" {
        return token::SEMI_COL;
}

"(" {
        return token::LPAREN;
}

")" {
        return token::RPAREN;
}

"=" {
        return token::ASSIGN;
}

[0-9]+ {
    yylval->longVal_ = atoi(yytext);
    return token::INTEGER;
}

[0-9]+"."[0-9]* {
    yylval->doubleVal_ = atof(yytext);
    return token::DOUBLE;
}

\"[A-Za-z][A-Za-z0-9_,.-]*\" {
    yylval->stringVal_ = std::string(&yytext[1], yyleng - 2);
    return token::STRING;
}

[A-Za-z][A-Za-z0-9^\.]*[\.]field[A-Za-z][A-Za-z0-9]* {
    yylval->stringVal_ = std::string(yytext, yyleng);
    return token::NAME;
}

[A-Za-z][A-Za-z0-9^\.]*[\.]tag[0-9]+ {
    yylval->stringVal_ = std::string(yytext, yyleng);
    return token::NAME;
}


[A-Za-z][A-Za-z0-9]* {
    yylval->stringVal_ = std::string(yytext, yyleng);
    return token::NAME;
}


 /* gobble up white-spaces */
[ \t\r\n]+ {
    yylloc->step();
}

[/][/][^'\n']*['\n']  { }

[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]       { /* DO NOTHING */ }

 /* gobble up end-of-lines */
'\n' {
    yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}


%% /*** Additional Code ***/

namespace roe 
{

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : RoeFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

#ifdef yylex
#undef yylex
#endif

int RoeFlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

int RoeFlexLexer::yywrap()
{
    return 1;
}
