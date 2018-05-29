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
#line 4 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <Parser/YYTYPE.h>

#line 96 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:404


#include <Parser/Driver.h>
#include <Parser/YYTYPE.h>
#include <Lexer/Scanner.h>

#undef yylex
#define yylex driver.lexer->lex

#line 56 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.hh"

// User implementation prologue.

#line 70 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:412


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
#line 156 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:479

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
    #line 40 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 535 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:741

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
#line 111 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	         (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTLong(driver.context(),(yystack_[0].value.longVal_)) );
	       }
#line 647 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 115 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	         (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTDouble(driver.context(),(yystack_[0].value.doubleVal_)) );
	       }
#line 655 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 119 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
              (yylhs.value.astElement_) =  std::shared_ptr<ASTCstr>( new ASTCstr(driver.context(),(yystack_[0].value.stringVal_)));
	       }
#line 663 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 124 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astParameters_) = ASTFunctionParametersPtr(new ASTFunctionParameters(driver.context()));
            }
#line 671 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 128 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
               (yystack_[2].value.astParameters_)->addParameter((yystack_[0].value.stringVal_));
               (yylhs.value.astParameters_) = (yystack_[2].value.astParameters_);
            }
#line 680 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 133 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astParameters_) = ASTFunctionParametersPtr(new ASTFunctionParameters(driver.context()));
                (yylhs.value.astParameters_)->addParameter((yystack_[0].value.stringVal_));
            }
#line 689 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 139 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astElement_) = std::shared_ptr<ASTElement> (new ASTArgList(driver.context()));
            }
#line 697 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 143 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
                dynamic_cast<ASTArgList*>((yystack_[2].value.astElement_).get())->addArgument((yystack_[0].value.astElement_));
                (yylhs.value.astElement_)=(yystack_[2].value.astElement_);
            }
#line 706 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 148 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
                (yylhs.value.astElement_) = std::shared_ptr<ASTElement> (new ASTArgList(driver.context()));
                dynamic_cast<ASTArgList*>((yylhs.value.astElement_).get())->addArgument((yystack_[0].value.astElement_));
            }
#line 715 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 154 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
              (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTFunctionCall(driver.context(), (yystack_[3].value.stringVal_), (yystack_[1].value.astElement_) ) );
           }
#line 723 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 159 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	         (yylhs.value.astElement_) =  std::shared_ptr<ASTElement>( new ASTVariable(driver.context(),(yystack_[0].value.stringVal_)) );
           }
#line 731 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 164 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
	   }
#line 739 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 169 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = std::shared_ptr<ASTElement> ( new ASTStrSlice (driver.context(), (yystack_[3].value.astElement_), (yystack_[1].value.astElement_), ASTElementPtr()));
	   }
#line 747 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 174 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = std::shared_ptr<ASTElement> ( new ASTStrSlice (driver.context(), (yystack_[5].value.astElement_), (yystack_[3].value.astElement_), (yystack_[1].value.astElement_)));
	   }
#line 755 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 178 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
           (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
	   }
#line 763 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 182 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	       (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
	   }
#line 771 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 186 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
	   }
#line 779 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 190 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTLogical(driver.context()
                              ,ASTLogical::Operator::OR
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 793 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 200 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 801 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 204 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
          (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTLogical(driver.context()
                              ,ASTLogical::Operator::AND
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );

          }
#line 816 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 215 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
             (yylhs.value.astElement_) =(yystack_[0].value.astElement_);
          }
#line 824 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 220 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTLogicalNOT(driver.context(), (yystack_[0].value.astElement_))
            );
          }
#line 835 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 227 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 843 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 232 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::MORE
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 857 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 242 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::LESS
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 871 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 252 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::NOT_EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 885 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 263 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 899 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 274 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::MORE_OR_EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 913 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 285 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTCompare(driver.context()
                              ,ASTCompare::Operator::LESS_OR_EQUAL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 927 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 295 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
             (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
          }
#line 935 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 299 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 943 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 303 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::PLUS
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 957 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 314 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MINUS
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
          }
#line 971 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 324 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	        (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
          }
#line 979 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 329 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
           (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MUL
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
         }
#line 993 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 339 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::DIV
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
         }
#line 1007 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 349 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = std::shared_ptr<ASTElement>
            (
                new ASTArithmetical(driver.context()
                              ,ASTArithmetical::Operator::MOD
                              , (yystack_[2].value.astElement_)
                              , (yystack_[0].value.astElement_))
            );
         }
#line 1021 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 359 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
         }
#line 1029 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 366 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
   (yylhs.value.astElement_)=std::shared_ptr<ASTElement>( new ASTAssignment(driver.context(),(yystack_[2].value.astElement_), (yystack_[0].value.astElement_)) );
}
#line 1037 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 371 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astElement_)=std::shared_ptr<ASTElement>
            ( new ASTIf(driver.context(),(yystack_[2].value.astElement_), (yystack_[0].value.astElement_), ASTElementPtr()) );
        }
#line 1046 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 377 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
           (yylhs.value.astElement_)=std::shared_ptr<ASTElement>( new ASTIf(driver.context(),(yystack_[4].value.astElement_), (yystack_[2].value.astElement_), (yystack_[0].value.astElement_)) );
        }
#line 1054 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 382 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
         (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
    }
#line 1062 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 387 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
	      (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
    }
#line 1070 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 392 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
      (yylhs.value.astElement_)=(yystack_[1].value.astElement_);
   }
#line 1078 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 396 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
      (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
   }
#line 1086 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 400 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
      (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
   }
#line 1094 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 404 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
     (yylhs.value.astElement_) = ASTElementPtr (new ASTReturn(driver.context()));
   }
#line 1102 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 408 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {(yylhs.value.astElement_) = std::shared_ptr<ASTElement> (new ASTBlock(driver.context()));}
#line 1108 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 411 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
                dynamic_cast<ASTBlock*>((yystack_[1].value.astElement_).get())->addElement((yystack_[0].value.astElement_));
                (yylhs.value.astElement_)=(yystack_[1].value.astElement_);
            }
#line 1117 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 418 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
          (yylhs.value.astElement_) = (yystack_[0].value.astElement_);
        }
#line 1125 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 422 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
          (yylhs.value.astElement_) = (yystack_[1].value.astElement_);
        }
#line 1133 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 427 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
            (yylhs.value.astRule_) = std::shared_ptr<ASTRule> (new ASTRule(driver.context(), (yystack_[4].value.stringVal_), (yystack_[2].value.astParameters_), (yystack_[0].value.astElement_)));
       }
#line 1141 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 431 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {}
#line 1147 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 433 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
          driver.rules().addRule((yystack_[0].value.astRule_));
       }
#line 1155 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 437 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:859
    {
       }
#line 1162 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1166 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -61;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
     -61,    -4,    19,    14,   -61,   -61,    22,    49,    44,   -61,
       9,    52,    50,   -61,    74,    -6,    53,   -61,   -61,   -61,
      75,   -61,   -61,   -61,   -11,   -61,    45,    46,   -61,    77,
      78,   -61,   -61,    58,    80,   -61,    58,    28,    -6,    -6,
      -6,    -6,    -6,    -6,    -6,   -61,   -61,    58,    58,    70,
       4,    95,   -61,   -61,    79,   -61,    13,    97,   -61,   -61,
     -61,    36,    46,    46,   -61,   -61,   -61,   -61,     5,    79,
      58,    50,    58,    -6,    -6,    -6,    -6,    -6,    -6,    58,
     -61,   -61,    -6,   -61,    95,    99,   -61,    45,    45,    45,
      45,    45,    45,    97,    76,    50,   -61,   -61
  };

  const unsigned char
  Parser::yydefact_[] =
  {
      54,    56,     0,     0,    55,     1,     0,     0,     5,     7,
       0,     0,     0,     6,     0,     0,     0,     2,     3,     4,
      12,    49,    17,    16,    13,    39,    44,    35,    43,    46,
       0,    51,    53,     0,     0,    48,     8,     0,     0,     0,
       0,     0,     0,     0,     0,    47,    45,     0,     0,    13,
       0,    20,    22,    24,    32,    18,     0,    10,    52,    50,
      40,     0,    33,    34,    36,    37,    38,    23,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,    14,     0,    31,    19,    41,    21,    27,    28,    25,
      26,    29,    30,     9,     0,     0,    15,    42
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -61,   -61,   -61,   -61,   -61,   -12,   -34,   -30,    37,   -40,
     -61,   -32,    30,   -61,   -61,    12,    69,   -61,   -60,   -61,
     -61,   -61
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    22,    10,    56,    23,    49,    25,    50,    51,    52,
      53,    26,    27,    28,    29,    30,    31,    37,    32,     4,
       1,     2
  };

  const unsigned char
  Parser::yytable_[] =
  {
      24,    54,     3,    24,    54,    61,    57,    67,    64,    65,
      66,    85,    70,    70,    38,    54,    69,    15,    68,     5,
      39,    17,    18,    19,    20,    24,    24,    34,    71,    83,
      11,    14,    86,    12,    79,    97,    24,    80,    54,     6,
      54,    87,    88,    89,    90,    91,    92,    54,    94,    93,
      60,    15,     7,    14,    16,    17,    18,    19,    20,    24,
      34,    40,    41,    58,    42,    43,    44,    47,    81,    82,
      62,    63,     8,    15,     9,    35,    16,    17,    18,    19,
      20,    48,    13,    24,    21,    17,    18,    19,    20,    73,
      74,    75,    76,    77,    78,    40,    41,    33,    36,    45,
      46,    39,    72,    95,    55,    70,    59,    84,    96
  };

  const unsigned char
  Parser::yycheck_[] =
  {
      12,    33,     6,    15,    36,    39,    36,    47,    42,    43,
      44,    71,     8,     8,    25,    47,    48,    23,    48,     0,
      31,    27,    28,    29,    30,    37,    38,    15,    24,    24,
      21,     3,    72,    24,    21,    95,    48,    24,    70,    25,
      72,    73,    74,    75,    76,    77,    78,    79,    82,    79,
      38,    23,    30,     3,    26,    27,    28,    29,    30,    71,
      48,    16,    17,    35,    18,    19,    20,     9,    32,    33,
      40,    41,    23,    23,    30,    22,    26,    27,    28,    29,
      30,    23,    30,    95,    34,    27,    28,    29,    30,    10,
      11,    12,    13,    14,    15,    16,    17,    23,    23,    22,
      22,    31,     7,     4,    24,     8,    37,    70,    32
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    56,    57,     6,    55,     0,    25,    30,    23,    30,
      38,    21,    24,    30,     3,    23,    26,    27,    28,    29,
      30,    34,    37,    40,    41,    42,    47,    48,    49,    50,
      51,    52,    54,    23,    51,    22,    23,    53,    25,    31,
      16,    17,    18,    19,    20,    22,    22,     9,    23,    41,
      43,    44,    45,    46,    47,    24,    39,    43,    35,    52,
      51,    42,    48,    48,    42,    42,    42,    45,    43,    47,
       8,    24,     7,    10,    11,    12,    13,    14,    15,    21,
      24,    32,    33,    24,    44,    54,    45,    47,    47,    47,
      47,    47,    47,    43,    42,     4,    32,    54
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    36,    37,    37,    37,    38,    38,    38,    39,    39,
      39,    40,    41,    42,    42,    42,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    47,    48,    48,    48,    48,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    53,
      53,    54,    54,    55,    56,    56,    57
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     0,     3,     1,     0,     3,
       1,     4,     1,     1,     4,     6,     1,     1,     3,     3,
       1,     3,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       3,     5,     7,     1,     1,     2,     1,     2,     2,     0,
       2,     1,     3,     7,     0,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"if keyword\"",
  "\"else keyword\"", "\"end of line\"", "\"ruleid\"", "\"and\"", "\"or\"",
  "\"not\"", "\"!=\"", "\"==\"", "\">\"", "\"<\"", "\">=\"", "\"<=\"",
  "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\",\"", "\";\"", "\"(\"",
  "\")\"", "\"=\"", "\"return\"", "\"integer\"", "\"double\"",
  "\"string\"", "\"name\"", "'['", "']'", "':'", "'{'", "'}'", "$accept",
  "constant", "parameters", "arg_list", "func_call", "variable",
  "atomexpr", "or_exp", "and_exp", "not_exp", "compare_exp", "addexpr",
  "factor", "assignment", "if_expr", "expr", "statement", "expr_list",
  "expr_block", "rule", "rules", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   110,   110,   114,   118,   124,   127,   132,   139,   142,
     147,   153,   158,   163,   168,   173,   177,   181,   185,   189,
     199,   203,   214,   219,   226,   231,   241,   251,   262,   273,
     284,   294,   298,   302,   313,   323,   328,   338,   348,   358,
     365,   370,   376,   381,   386,   391,   395,   399,   403,   408,
     410,   417,   421,   426,   431,   432,   436
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
       2,     2,     2,     2,     2,     2,     2,     2,    33,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
    };
    const unsigned int user_token_number_max_ = 285;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // roe
#line 1652 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.cpp" // lalr1.cc:1167
#line 442 "/home/vkochano/RoeLang/RoeLang/Parser/Parser.yy" // lalr1.cc:1168
 /*** Additional Code ***/

void roe::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
