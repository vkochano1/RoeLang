/* $Id$ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <Parser/YYTYPE.h>

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="roe"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/


%define api.value.type {struct YYSTYPE}

%token			IF_KEYWORD	  	"if keyword"
%token			ELSE_KEYWORD	"else keyword"
%token			END	     0	"end of file"
%token			EOL		    "end of line"
%token    	            RULE_KEYWORD		"ruleid"
%token    	            AND_KEYWORD		"and"
%token    	            OR_KEYWORD		"or"
%token    	            NOT_KEYWORD		"not"
%token    	            NOT_EQUAL		"!="
%token    	            EQUAL		    "=="
%token    	            MORE		    ">"
%token    	            LESS		    "<"
%token    	            MORE_OR_EQUAL		    ">="
%token    	            LESS_OR_EQUAL		    "<="
%token    	            PLUS		    "+"
%token    	            MINUS		    "-"
%token    	            MULT		    "*"
%token    	            DIV		        "/"
%token    	            COMMA		    ","
%token    	            SEMI_COL		";"
%token    	            LPAREN		"("
%token    	            RPAREN		")"
%token    	            ASSIGN		"="




%token <longVal_> 	    INTEGER		"integer"
%token <doubleVal_> 	DOUBLE		"double"
%token <stringVal_> 	STRING		"string"
%token <stringVal_> 	NAME		"name"

%type <astParameters_>  parameters
%type <astRule_>    rule rules
%type <astElement_>	constant variable not_exp  arg_list func_call factor statement
%type <astElement_>	atomexpr addexpr expr assignment if_expr expr_block expr_list compare_exp and_exp or_exp

%{

#include <Parser/Driver.h>
#include <Parser/YYTYPE.h>
#include <Lexer/Scanner.h>

#undef yylex
#define yylex driver.lexer->lex
%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

constant :  INTEGER
           {
	         $$ =  std::shared_ptr<ASTElement>( new ASTLong(driver.context(),$1) );
	       }
	       | DOUBLE
           {
	         $$ =  std::shared_ptr<ASTElement>( new ASTDouble(driver.context(),$1) );
	       }
	       | STRING
           {
              $$ =  std::shared_ptr<ASTCstr>( new ASTCstr(driver.context(),$1));
	       }

parameters : /*epsilon*/
            {
                $$ = ASTFunctionParametersPtr(new ASTFunctionParameters(driver.context()));
            }
            | parameters COMMA NAME
            {
               $1->addParameter($3);
               $$ = $1;
            }
            | NAME
            {
                $$ = ASTFunctionParametersPtr(new ASTFunctionParameters(driver.context()));
                $$->addParameter($1);
            }

arg_list :  /*epsilon*/
            {
                $$ = std::shared_ptr<ASTElement> (new ASTArgList(driver.context()));
            }
            | arg_list COMMA or_exp
            {
                dynamic_cast<ASTArgList*>($1.get())->addArgument($3);
                $$=$1;
            }
            | or_exp
            {
                $$ = std::shared_ptr<ASTElement> (new ASTArgList(driver.context()));
                dynamic_cast<ASTArgList*>($$.get())->addArgument($1);
            }

func_call: NAME LPAREN arg_list RPAREN
           {
              $$ =  std::shared_ptr<ASTElement>( new ASTFunctionCall(driver.context(), $1, $3 ) );
           }

variable : NAME
           {
	         $$ =  std::shared_ptr<ASTElement>( new ASTVariable(driver.context(),$1) );
           }

atomexpr : variable
	   {
	       $$ = $1;
	   }
	   |
	   variable '[' atomexpr ']'
	   {
	       $$ = std::shared_ptr<ASTElement> ( new ASTStrSlice (driver.context(), $1, $3, ASTElementPtr()));
	   }
       |
	   variable '[' atomexpr ':' atomexpr  ']'
	   {
	       $$ = std::shared_ptr<ASTElement> ( new ASTStrSlice (driver.context(), $1, $3, $5));
	   }
	   |func_call
	   {
           $$ = $1;
	   }
       |constant
       {
	       $$ = $1;
	   }
	   | LPAREN expr RPAREN
	   {
            $$ = $2;
	   }
or_exp   : or_exp OR_KEYWORD and_exp
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTLogical(driver.context()
                              ,ASTLogical::Operator::OR
                              , $1
                              , $3)
            );
          }
          | and_exp
          {
            $$ = $1;
          }
and_exp  : and_exp AND_KEYWORD not_exp
          {
          $$ = std::shared_ptr<ASTElement>
            (
                new ASTLogical(driver.context()
                              ,ASTLogical::Operator::AND
                              , $1
                              , $3)
            );

          }
          | not_exp
          {
             $$ =$1;
          }

not_exp : NOT_KEYWORD not_exp
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTLogicalNOT(driver.context(), $2)
            );
          }
          | compare_exp
          {
            $$ = $1;
          }

compare_exp : addexpr MORE addexpr
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::MORE
                              , $1
                              , $3)
            );
          }|
          addexpr LESS addexpr
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::LESS
                              , $1
                              , $3)
            );
          }|
          addexpr NOT_EQUAL addexpr
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::NOT_EQUAL
                              , $1
                              , $3)
            );
          }
          |
          addexpr EQUAL addexpr
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::EQUAL
                              , $1
                              , $3)
            );
          }
          |
          addexpr MORE_OR_EQUAL addexpr
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::MORE_OR_EQUAL
                              , $1
                              , $3)
            );
          }
                    |
          addexpr LESS_OR_EQUAL addexpr
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::LESS_OR_EQUAL
                              , $1
                              , $3)
            );
          }
          | LPAREN or_exp RPAREN
          {
             $$ = $2;
          }
          | addexpr
          {
            $$ = $1;
          }
addexpr : addexpr PLUS factor
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::PLUS
                              , $1
                              , $3)
            );
          }
          |
          addexpr MINUS factor
          {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MINUS
                              , $1
                              , $3)
            );
          }
          |factor
          {
	        $$ = $1;
          }

factor:  factor MULT atomexpr
         {
           $$ = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MUL
                              , $1
                              , $3)
            );
         }
         | factor DIV atomexpr
         {
            $$ = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::DIV
                              , $1
                              , $3)
            );
         }
         | atomexpr
         {
            $$ = $1;
         }



assignment : variable ASSIGN expr
{
   $$=std::shared_ptr<ASTElement>( new ASTAssignment(driver.context(),$1, $3) );
}

if_expr : IF_KEYWORD LPAREN or_exp RPAREN expr_block
        {
            $$=std::shared_ptr<ASTElement>
            ( new ASTIf(driver.context(),$3, $5, ASTElementPtr()) );
        }
        |
        IF_KEYWORD LPAREN or_exp RPAREN expr_block ELSE_KEYWORD expr_block
        {
           $$=std::shared_ptr<ASTElement>( new ASTIf(driver.context(),$3, $5, $7) );
        }

expr	: assignment
    {
         $$ = $1;
    }
    |
    addexpr
    {
	      $$ = $1;
    }

statement : expr SEMI_COL
   {
      $$=$1;
   }
   |if_expr
   {
      $$ = $1;
   }
   |if_expr SEMI_COL
   {
      $$ = $1;
   }

expr_list : /*epsilon*/ {$$ = std::shared_ptr<ASTElement> (new ASTBlock(driver.context()));}
            |
            expr_list statement
            {
                dynamic_cast<ASTBlock*>($1.get())->addElement($2);
                $$=$1;
            }

expr_block:
        statement
        {
          $$ = $1;
        }
        |'{' expr_list '}'
        {
          $$ = $2;
        }

rule : RULE_KEYWORD ASSIGN NAME LPAREN parameters RPAREN expr_block
       {
            $$ = std::shared_ptr<ASTRule> (new ASTRule(driver.context(), $3, $5, $7));
       }

rules :/*epsilon*/    {}
       |  rules rule
       {
          driver.rules().addRule($2);
       }
start	: rules
       {
       }



%% /*** Additional Code ***/

void roe::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
