// A Bison parser, made by GNU Bison 3.2.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "prefcalc.hh"


// Unqualified %code blocks.
#line 39 "src/prefcalc.yy" // lalr1.cc:438

    #include "driver.hh"

#line 49 "src/prefcalc.cc" // lalr1.cc:438


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 144 "src/prefcalc.cc" // lalr1.cc:513

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
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
  parser::parser (driver & drv_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 32: // printargs
        value.YY_MOVE_OR_COPY< std::list<std::shared_ptr<expr>> > (YY_MOVE (that.value));
        break;

      case 29: // sttmseq
        value.YY_MOVE_OR_COPY< std::list<std::shared_ptr<sttm>> > (YY_MOVE (that.value));
        break;

      case 33: // exp
        value.YY_MOVE_OR_COPY< std::shared_ptr<expr> > (YY_MOVE (that.value));
        break;

      case 30: // sttm
      case 31: // else
        value.YY_MOVE_OR_COPY< std::shared_ptr<sttm> > (YY_MOVE (that.value));
        break;

      case 3: // "number"
      case 4: // "variable"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 32: // printargs
        value.move< std::list<std::shared_ptr<expr>> > (YY_MOVE (that.value));
        break;

      case 29: // sttmseq
        value.move< std::list<std::shared_ptr<sttm>> > (YY_MOVE (that.value));
        break;

      case 33: // exp
        value.move< std::shared_ptr<expr> > (YY_MOVE (that.value));
        break;

      case 30: // sttm
      case 31: // else
        value.move< std::shared_ptr<sttm> > (YY_MOVE (that.value));
        break;

      case 3: // "number"
      case 4: // "variable"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 32: // printargs
        value.move< std::list<std::shared_ptr<expr>> > (that.value);
        break;

      case 29: // sttmseq
        value.move< std::list<std::shared_ptr<sttm>> > (that.value);
        break;

      case 33: // exp
        value.move< std::shared_ptr<expr> > (that.value);
        break;

      case 30: // sttm
      case 31: // else
        value.move< std::shared_ptr<sttm> > (that.value);
        break;

      case 3: // "number"
      case 4: // "variable"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
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

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 32: // printargs
        yylhs.value.emplace< std::list<std::shared_ptr<expr>> > ();
        break;

      case 29: // sttmseq
        yylhs.value.emplace< std::list<std::shared_ptr<sttm>> > ();
        break;

      case 33: // exp
        yylhs.value.emplace< std::shared_ptr<expr> > ();
        break;

      case 30: // sttm
      case 31: // else
        yylhs.value.emplace< std::shared_ptr<sttm> > ();
        break;

      case 3: // "number"
      case 4: // "variable"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 82 "src/prefcalc.yy" // lalr1.cc:907
    { drv.result = std::move(main_class(std::move(yystack_[0].value.as< std::list<std::shared_ptr<sttm>> > ()))); }
#line 627 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 3:
#line 86 "src/prefcalc.yy" // lalr1.cc:907
    {}
#line 633 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 4:
#line 87 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::list<std::shared_ptr<sttm>> > () = std::move(yystack_[0].value.as< std::list<std::shared_ptr<sttm>> > ()); yylhs.value.as< std::list<std::shared_ptr<sttm>> > ().push_front(std::move(yystack_[1].value.as< std::shared_ptr<sttm> > ())); }
#line 639 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 5:
#line 91 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = MAKE_SHARED(sttm, if_sttm(std::move(yystack_[3].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[2].value.as< std::shared_ptr<sttm> > ()), std::move(yystack_[1].value.as< std::shared_ptr<sttm> > ()))); }
#line 645 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 6:
#line 92 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = MAKE_SHARED(sttm, print_sttm(std::move(yystack_[1].value.as< std::list<std::shared_ptr<expr>> > ()))); }
#line 651 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 7:
#line 93 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = MAKE_SHARED(sttm, assign_sttm(std::move(yystack_[1].value.as< std::string > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 657 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 8:
#line 94 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = MAKE_SHARED(sttm, scope_sttm(std::move(yystack_[1].value.as< std::list<std::shared_ptr<sttm>> > ()))); }
#line 663 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 9:
#line 95 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = MAKE_SHARED(sttm, while_sttm(std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<sttm> > ()))); }
#line 669 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 10:
#line 99 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = nullptr; }
#line 675 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 11:
#line 100 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<sttm> > () = std::move(yystack_[0].value.as< std::shared_ptr<sttm> > ()); }
#line 681 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 12:
#line 104 "src/prefcalc.yy" // lalr1.cc:907
    {}
#line 687 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 13:
#line 105 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::list<std::shared_ptr<expr>> > () = std::move(yystack_[0].value.as< std::list<std::shared_ptr<expr>> > ()); yylhs.value.as< std::list<std::shared_ptr<expr>> > ().push_front(std::move(yystack_[1].value.as< std::shared_ptr<expr> > ())); }
#line 693 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 14:
#line 109 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, num(std::move(yystack_[0].value.as< std::string > ()))); }
#line 699 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 15:
#line 110 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, var(std::move(yystack_[0].value.as< std::string > ()))); }
#line 705 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 16:
#line 111 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("+", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 711 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 17:
#line 112 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("-", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 717 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 18:
#line 113 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("*", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 723 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 19:
#line 114 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("/", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 729 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 20:
#line 115 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("%", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 735 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 21:
#line 116 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, un_op("!", std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 741 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 22:
#line 117 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("&", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 747 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 23:
#line 118 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("|", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 753 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 24:
#line 119 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("<", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 759 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 25:
#line 120 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op(">", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 765 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 26:
#line 121 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("==", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 771 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 27:
#line 122 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("!=", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 777 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 28:
#line 123 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op(">=", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 783 "src/prefcalc.cc" // lalr1.cc:907
    break;

  case 29:
#line 124 "src/prefcalc.yy" // lalr1.cc:907
    { yylhs.value.as< std::shared_ptr<expr> > () = MAKE_SHARED(expr, bin_op("<=", std::move(yystack_[1].value.as< std::shared_ptr<expr> > ()), std::move(yystack_[0].value.as< std::shared_ptr<expr> > ()))); }
#line 789 "src/prefcalc.cc" // lalr1.cc:907
    break;


#line 793 "src/prefcalc.cc" // lalr1.cc:907
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
      yypush_ ("Shifting", YY_MOVE (error_token));
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const signed char parser::yypact_ninf_ = -26;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      44,     2,    43,    44,    43,    43,     8,   -26,    44,    43,
     -26,   -26,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,   -11,     9,    43,
      44,   -26,   -26,   -26,    43,    43,    43,    43,    43,    43,
      43,    43,    43,   -26,    43,    43,    43,    43,    14,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,    44,    11,   -26,   -26
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     3,    12,     0,     0,     2,     3,     0,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     1,     4,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,    10,     8,
       6,    13,     9,    26,    27,    28,    29,    16,    17,    18,
      19,    20,    22,    23,    25,    24,     0,     0,    11,     5
  };

  const signed char
  parser::yypgoto_[] =
  {
     -26,   -26,     1,   -25,   -26,    -1,    -2
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     6,     7,     8,    67,    28,    29
  };

  const unsigned char
  parser::yytable_[] =
  {
      26,    48,    49,    30,    27,    52,     9,    33,    31,    32,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    50,    66,    69,     0,    51,     0,
       0,     0,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    68,    62,    63,    64,    65,    10,    11,    12,    13,
      14,    15,     0,     1,     2,     0,     3,     0,     4,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       5
  };

  const signed char
  parser::yycheck_[] =
  {
       2,    26,    13,     5,     3,    30,     4,     9,     0,     8,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    15,    11,    15,    -1,    29,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    66,    44,    45,    46,    47,     3,     4,     5,     6,
       7,     8,    -1,     9,    10,    -1,    12,    -1,    14,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      26
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     9,    10,    12,    14,    26,    28,    29,    30,     4,
       3,     4,     5,     6,     7,     8,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    33,    29,    32,    33,
      33,     0,    29,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    30,    13,
      15,    32,    30,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    11,    31,    30,    15
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    27,    28,    29,    29,    30,    30,    30,    30,    30,
      31,    31,    32,    32,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     5,     3,     3,     3,     3,
       0,     2,     0,     2,     1,     1,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"number\"", "\"variable\"",
  "\"==\"", "\"!=\"", "\">=\"", "\"<=\"", "\"=\"", "\"?\"", "\":\"",
  "\"(\"", "\")\"", "\"@\"", "\";\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"%\"", "\"!\"", "\"&\"", "\"|\"", "\">\"", "\"<\"", "\"#\"", "$accept",
  "main", "sttmseq", "sttm", "else", "printargs", "exp", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    82,    82,    86,    87,    91,    92,    93,    94,    95,
      99,   100,   104,   105,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1200 "src/prefcalc.cc" // lalr1.cc:1218
#line 126 "src/prefcalc.yy" // lalr1.cc:1219


void yy::parser::error(const location_type & l, const std::string & m)
{
    std::cerr << l << ": " << m << '\n';
}
