// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   roelex

// First part of user declarations.
#line 4 "Parser/Parser.yy" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <Parser/YYTYPE.h>

#line 95 "Parser/Parser.yy" // lalr1.cc:404


#include <Driver.h>
#include <Parser/YYTYPE.h>
#include <Lexer/Scanner.h>

#undef yylex
#define yylex driver.lexer->lex

#line 56 "Parser/Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.hh"

// User implementation prologue.

#line 70 "Parser/Parser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace roe {
#line 156 "Parser/Parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 40 "Parser/Parser.yy" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 535 "Parser/Parser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 110 "Parser/Parser.yy" // lalr1.cc:859
    {
	         (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTLong(driver.context(),(yystack_[0].value.longVal_)) );
	       }
#line 647 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 114 "Parser/Parser.yy" // lalr1.cc:859
    {
	         (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTDouble(driver.context(),(yystack_[0].value.doubleVal_)) );
	       }
#line 655 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 118 "Parser/Parser.yy" // lalr1.cc:859
    {
              (yylhs.value.astElement_) =  std::shared_ptr<ASTCstr>( new ASTCstr(driver.context(),(yystack_[0].value.stringVal_)));
	       }
#line 663 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 123 "Parser/Parser.yy" // lalr1.cc:859
    { 
                (yylhs.value.astParameters_) = ASTFunctionParametersPtr(new ASTFunctionParameters(driver.context())); 
            }
#line 671 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 127 "Parser/Parser.yy" // lalr1.cc:859
    {
               (yystack_[2].value.astParameters_)->addParameter((yystack_[0].value.stringVal_));
               (yylhs.value.astParameters_) = (yystack_[2].value.astParameters_);
            }
#line 680 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 132 "Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astParameters_) = ASTFunctionParametersPtr(new ASTFunctionParameters(driver.context()));
                (yylhs.value.astParameters_)->addParameter((yystack_[0].value.stringVal_));
            }
#line 689 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 138 "Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astElement_) = std::shared_ptr<ASTElement> (new ASTArgList(driver.context()));
            }
#line 697 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 142 "Parser/Parser.yy" // lalr1.cc:859
    {
                dynamic_cast<ASTArgList*>((yystack_[2].value.astElement_).get())->addArgument((yystack_[0].value.astElement_));
                (yylhs.value.astElement_)=(yystack_[2].value.astElement_);
            }
#line 706 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 147 "Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astElement_) = std::shared_ptr<ASTElement> (new ASTArgList(driver.context()));
                dynamic_cast<ASTArgList*>((yylhs.value.astElement_).get())->addArgument((yystack_[0].value.astElement_));  
            }
#line 715 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 153 "Parser/Parser.yy" // lalr1.cc:859
    {
              (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTFunctionCall(driver.context(), (yystack_[3].value.stringVal_), (yystack_[1].value.astElement_) ) );
           }
#line 723 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 158 "Parser/Parser.yy" // lalr1.cc:859
    {
	         (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTVariable(driver.context(),(yystack_[0].value.stringVal_)) );
           }
#line 731 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 163 "Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
	   }
#line 739 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 168 "Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = std::shared_ptr<ASTElement> ( new ASTStrSlice (driver.context(), (yystack_[3].value.astElement_), (yystack_[1].value.astElement_), ASTElement::ASTElementPtr()));
	   }
#line 747 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 173 "Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = std::shared_ptr<ASTElement> ( new ASTStrSlice (driver.context(), (yystack_[5].value.astElement_), (yystack_[3].value.astElement_), (yystack_[1].value.astElement_)));
	   }
#line 755 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 177 "Parser/Parser.yy" // lalr1.cc:859
    {
           (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
	   }
#line 763 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 181 "Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
	   }
#line 771 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 185 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
	   }
#line 779 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 189 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTLogical(driver.context()
                              ,ASTLogical::Operator::OR
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 793 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 199 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 801 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 203 "Parser/Parser.yy" // lalr1.cc:859
    {
          (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTLogical(driver.context()
                              ,ASTLogical::Operator::AND
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
            
          }
#line 816 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 214 "Parser/Parser.yy" // lalr1.cc:859
    {
             (yylhs.value.astElement_) =(yystack_[0].value.astElement_);
          }
#line 824 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 219 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTLogicalNOT(driver.context(), (yystack_[0].value.astElement_))
            );
          }
#line 835 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 226 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 843 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 231 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::MORE
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 857 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 241 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::LESS
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 871 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 251 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::NOT_EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 885 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 262 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 899 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 273 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::MORE_OR_EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 913 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 284 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::LESS_OR_EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 927 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 294 "Parser/Parser.yy" // lalr1.cc:859
    { 
             (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
          }
#line 935 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 298 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 943 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 302 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::PLUS
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 957 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 313 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MINUS
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 971 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 323 "Parser/Parser.yy" // lalr1.cc:859
    {
	        (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 979 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 328 "Parser/Parser.yy" // lalr1.cc:859
    {
           (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MUL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
         }
#line 993 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 338 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement> 
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::DIV
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
         }
#line 1007 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 348 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
         }
#line 1015 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 355 "Parser/Parser.yy" // lalr1.cc:859
    {
   (yylhs.value.astElement_)=std::shared_ptr<ASTElement>( new ASTAssignment(driver.context(),(yystack_[2].value.astElement_), (yystack_[0].value.astElement_)) );
}
#line 1023 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 360 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_)=std::shared_ptr<ASTElement>
            ( new ASTIf(driver.context(),(yystack_[2].value.astElement_), (yystack_[0].value.astElement_), ASTElement::ASTElementPtr()) );            
        }
#line 1032 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 366 "Parser/Parser.yy" // lalr1.cc:859
    {
           (yylhs.value.astElement_)=std::shared_ptr<ASTElement>( new ASTIf(driver.context(),(yystack_[4].value.astElement_), (yystack_[2].value.astElement_), (yystack_[0].value.astElement_)) );            
        }
#line 1040 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 371 "Parser/Parser.yy" // lalr1.cc:859
    {
         (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
    }
#line 1048 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 376 "Parser/Parser.yy" // lalr1.cc:859
    {
	      (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
    }
#line 1056 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 381 "Parser/Parser.yy" // lalr1.cc:859
    {
      (yylhs.value.astElement_)=(yystack_[1].value.astElement_);
   }
#line 1064 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 385 "Parser/Parser.yy" // lalr1.cc:859
    {
      (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
   }
#line 1072 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 389 "Parser/Parser.yy" // lalr1.cc:859
    {
      (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
   }
#line 1080 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 393 "Parser/Parser.yy" // lalr1.cc:859
    {(yylhs.value.astElement_) = std::shared_ptr<ASTElement> (new ASTBlock(driver.context()));}
#line 1086 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 396 "Parser/Parser.yy" // lalr1.cc:859
    {
                dynamic_cast<ASTBlock*>((yystack_[1].value.astElement_).get())->addElement((yystack_[0].value.astElement_));
                (yylhs.value.astElement_)=(yystack_[1].value.astElement_);
            }
#line 1095 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 403 "Parser/Parser.yy" // lalr1.cc:859
    {
          (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
        }
#line 1103 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 407 "Parser/Parser.yy" // lalr1.cc:859
    {
          (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
        }
#line 1111 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 412 "Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astRule_) = std::shared_ptr<ASTRule> (new ASTRule(driver.context(), (yystack_[4].value.stringVal_), (yystack_[2].value.astParameters_), (yystack_[0].value.astElement_))); 
       }
#line 1119 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 416 "Parser/Parser.yy" // lalr1.cc:859
    {}
#line 1125 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 418 "Parser/Parser.yy" // lalr1.cc:859
    {
          driver.rules().addRule((yystack_[0].value.astRule_));
       }
#line 1133 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 422 "Parser/Parser.yy" // lalr1.cc:859
    {
       }
#line 1140 "Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1144 "Parser/Parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -58;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
     -58,    59,    18,    45,   -58,   -58,    24,    48,    47,   -58,
      31,    64,    46,   -58,    54,    -6,   -58,   -58,   -58,    71,
     -58,   -58,   -58,    29,   -58,    -5,    42,   -58,    73,    75,
     -58,   -58,    55,    72,    55,     4,    -6,    -6,    -6,    -6,
      -6,    -6,   -58,   -58,    55,    55,    68,     5,    91,   -58,
     -58,    74,   -58,    36,    92,   -58,   -58,   -58,    32,    42,
      42,   -58,   -58,   -58,    27,    74,    55,    46,    55,    -6,
      -6,    -6,    -6,    -6,    -6,    55,   -58,   -58,    -6,   -58,
      91,    95,   -58,    -5,    -5,    -5,    -5,    -5,    -5,    92,
      76,    46,   -58,   -58
  };

  const unsigned char
  Parser::yydefact_[] =
  {
      52,    54,     0,     0,    53,     1,     0,     0,     5,     7,
       0,     0,     0,     6,     0,     0,     2,     3,     4,    12,
      47,    17,    16,    13,    38,    43,    35,    42,    45,     0,
      49,    51,     0,     0,     8,     0,     0,     0,     0,     0,
       0,     0,    46,    44,     0,     0,    13,     0,    20,    22,
      24,    32,    18,     0,    10,    50,    48,    39,     0,    33,
      34,    36,    37,    23,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    14,     0,    31,
      19,    40,    21,    27,    28,    25,    26,    29,    30,     9,
       0,     0,    15,    41
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -58,   -58,   -58,   -58,   -58,   -12,   -32,   -28,    35,   -43,
     -58,   -30,    28,   -58,   -58,    12,    67,   -58,   -57,   -58,
     -58,   -58
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    21,    10,    53,    22,    46,    24,    47,    48,    49,
      50,    25,    26,    27,    28,    29,    30,    35,    31,     4,
       1,     2
  };

  const unsigned char
  Parser::yytable_[] =
  {
      23,    63,    51,    23,    51,    58,    54,    14,    61,    62,
      81,    38,    39,    66,    51,    65,    15,    64,     5,    16,
      17,    18,    19,    23,    23,    82,    15,    33,    67,    16,
      17,    18,    19,    23,    93,    66,    51,    55,    51,    83,
      84,    85,    86,    87,    88,    51,    90,    89,    57,    14,
      79,    11,     7,    36,    12,    23,    75,    33,    37,    76,
      40,    41,    77,    78,    44,     3,    59,    60,    15,     6,
       8,    16,    17,    18,    19,     9,    32,    45,    20,    23,
      16,    17,    18,    19,    69,    70,    71,    72,    73,    74,
      38,    39,    13,    34,    42,    52,    43,    37,    68,    91,
      66,    80,    56,     0,     0,     0,    92
  };

  const signed char
  Parser::yycheck_[] =
  {
      12,    44,    32,    15,    34,    37,    34,     3,    40,    41,
      67,    16,    17,     8,    44,    45,    22,    45,     0,    25,
      26,    27,    28,    35,    36,    68,    22,    15,    23,    25,
      26,    27,    28,    45,    91,     8,    66,    33,    68,    69,
      70,    71,    72,    73,    74,    75,    78,    75,    36,     3,
      23,    20,    28,    24,    23,    67,    20,    45,    29,    23,
      18,    19,    30,    31,     9,     6,    38,    39,    22,    24,
      22,    25,    26,    27,    28,    28,    22,    22,    32,    91,
      25,    26,    27,    28,    10,    11,    12,    13,    14,    15,
      16,    17,    28,    22,    21,    23,    21,    29,     7,     4,
       8,    66,    35,    -1,    -1,    -1,    30
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    54,    55,     6,    53,     0,    24,    28,    22,    28,
      36,    20,    23,    28,     3,    22,    25,    26,    27,    28,
      32,    35,    38,    39,    40,    45,    46,    47,    48,    49,
      50,    52,    22,    49,    22,    51,    24,    29,    16,    17,
      18,    19,    21,    21,     9,    22,    39,    41,    42,    43,
      44,    45,    23,    37,    41,    33,    50,    49,    40,    46,
      46,    40,    40,    43,    41,    45,     8,    23,     7,    10,
      11,    12,    13,    14,    15,    20,    23,    30,    31,    23,
      42,    52,    43,    45,    45,    45,    45,    45,    45,    41,
      40,     4,    30,    52
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    34,    35,    35,    35,    36,    36,    36,    37,    37,
      37,    38,    39,    40,    40,    40,    40,    40,    40,    41,
      41,    42,    42,    43,    43,    44,    44,    44,    44,    44,
      44,    44,    44,    45,    45,    45,    46,    46,    46,    47,
      48,    48,    49,    49,    50,    50,    50,    51,    51,    52,
      52,    53,    54,    54,    55
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     0,     3,     1,     0,     3,
       1,     4,     1,     1,     4,     6,     1,     1,     3,     3,
       1,     3,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       5,     7,     1,     1,     2,     1,     2,     0,     2,     1,
       3,     7,     0,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"if keyword\"",
  "\"else keyword\"", "\"end of line\"", "\"ruleid\"", "\"and\"", "\"or\"",
  "\"not\"", "\"!=\"", "\"==\"", "\">\"", "\"<\"", "\">=\"", "\"<=\"",
  "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\",\"", "\";\"", "\"(\"", "\")\"",
  "\"=\"", "\"integer\"", "\"double\"", "\"string\"", "\"name\"", "'['",
  "']'", "':'", "'{'", "'}'", "$accept", "constant", "parameters",
  "arg_list", "func_call", "variable", "atomexpr", "or_exp", "and_exp",
  "not_exp", "compare_exp", "addexpr", "factor", "assignment", "if_expr",
  "expr", "statement", "expr_list", "expr_block", "rule", "rules", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   109,   109,   113,   117,   123,   126,   131,   138,   141,
     146,   152,   157,   162,   167,   172,   176,   180,   184,   188,
     198,   202,   213,   218,   225,   230,   240,   250,   261,   272,
     283,   293,   297,   301,   312,   322,   327,   337,   347,   354,
     359,   365,   370,   375,   380,   384,   388,   393,   395,   402,
     406,   411,   416,   417,   421
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    31,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
    };
    const unsigned int user_token_number_max_ = 283;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // roe
#line 1629 "Parser/Parser.cpp" // lalr1.cc:1167
#line 427 "Parser/Parser.yy" // lalr1.cc:1168
 /*** Additional Code ***/

void roe::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
