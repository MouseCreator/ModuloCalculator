
%{
	#include <iostream>
    #include <sstream>
	#include <cstdlib>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() MathBase::Parser::make_END(MathBase::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocation(yytext);
	
%}

%option nodefault
%option noyywrap
%option c++
%option never-interactive
%option nounistd
%option yyclass="Scanner"
%option prefix="MathBase_"


alpha       [a-zA-Z]
number      [0]|[1-9][0-9]*
identifier  {alpha}+

%%


{identifier}     { 
                return MathBase::Parser::make_IDENTIFIER(yytext, m_driver.getLocation()); 
                }
[\t ]       {
                /* Ignore whitespaces */
            }
\n+         {
                return MathBase::Parser::make_NEW_LINE(m_driver.getLocation());
            }

{number}    {
                return MathBase::Parser::make_NUMBER(yytext, m_driver.getLocation());
            }
            
\(          {
                return MathBase::Parser::make_LEFT_BRACKET(m_driver.getLocation());
            }
            
\)          { 
                return MathBase::Parser::make_RIGHT_BRACKET(m_driver.getLocation());
            } 
                 
,           {
                return MathBase::Parser::make_COMMA(m_driver.getLocation());
            }
\*\*|\^     {
                return MathBase::Parser::make_POWER(m_driver.getLocation());
            }
"+"         {
                return MathBase::Parser::make_PLUS(m_driver.getLocation());
            }
"-"         {
                return MathBase::Parser::make_MINUS(m_driver.getLocation());
            }
"*"         {
                return MathBase::Parser::make_MULTIPLY(m_driver.getLocation());
            }
"/"         {
                return MathBase::Parser::make_DIVIDE(m_driver.getLocation());
            }
"%"         {
                return MathBase::Parser::make_MODULO(m_driver.getLocation());
            }
"="         {
                return MathBase::Parser::make_EQUALS(m_driver.getLocation());
            }
"<"         {
                return MathBase::Parser::make_LT(m_driver.getLocation());
            }
">"         {
                return MathBase::Parser::make_GT(m_driver.getLocation());
            }
"<="         {
                return MathBase::Parser::make_LE(m_driver.getLocation());
            }
">="        {
                return MathBase::Parser::make_GE(m_driver.getLocation());
            }

.           {
                 std::stringstream ss;
                 ss << "Error: Unknown characters: " << yytext << ".";
                 m_driver.setError("scan", ss.str());
            }
            
<<EOF>>     { return yyterminate(); }


%%
