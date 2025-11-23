

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { MathBase }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "command.h"

    namespace MathBase {
        class Scanner;
        class Interpreter;
    }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the scanner. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
    #include <iostream>
    #include <sstream>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    // yylex() arguments are defined in parser.y
    static MathBase::Parser::symbol_type yylex(MathBase::Scanner &scanner, MathBase::Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()
    
    using namespace MathBase;
}

%lex-param { MathBase::Scanner &scanner }
%lex-param { MathBase::Interpreter &driver }
%parse-param { MathBase::Scanner &scanner }
%parse-param { MathBase::Interpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"
%token <std::string> NUMBER "number";
%token <std::string> IDENTIFIER "identifier";
%token POWER "^"
%token PLUS "+"
%token MINUS "-"
%token MULTIPLY "*"
%token DIVIDE "/"
%token MODULO "%"
%token COMMA ","
%token EQUALS "="
%token LT "<"
%token GT ">"
%token LE "<="
%token GE ">="
%token LEFT_BRACKET "("
%token RIGHT_BRACKET ")"
%token NEW_LINE "ln"
%token ERRPAIR "errpair"

%left EQUALS LT GT LE GE
%left COMMA
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right POWER

%nonassoc UMINUS UPLUS
%type<std::vector<MathBase::AST*>> S;
%type<std::vector<MathBase::AST*>> R;
%type<MathBase::ASTNode*> E;
%type<MathBase::ASTNode*> D;
%type<MathBase::ASTNode*> V;
%type<MathBase::ASTNode*> C;
%type<MathBase::ValueNode*> P;
%type<MathBase::FunctionNode*> L;
%type<std::vector<MathBase::ASTNode*>> A;
%type<std::vector<MathBase::ASTNode*>> B;

%start S

%%
S :
{
    $$ = {}; driver.clear();
}
| R  
{ 
  $$ = $1; 
  for (AST* ast : $1) { driver.addAST(ast); } 
}
;

R : 
D  {
   $$ = std::vector<AST*>();
   AST* ast = new AST($1);
   $$.emplace_back(ast); 
}
| R "ln" D    { $$ = $1; AST* ast = new AST($3);  $$.emplace_back(ast); }
D : E { $$ = $1; }
  ;
E : 
    E "+" E        { $$ = new OperationNode($1, "+", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E "-" E       { $$ = new OperationNode($1, "-", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E "*" E    { $$ = new OperationNode($1, "*", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E "/" E         {
                        $$ = new OperationNode($1, "-", $3, driver.transformLocation(@2)); driver.allocate($$);
                    }
  | E "%" E         {
                        $$ = new OperationNode($1, "%", $3, driver.transformLocation(@2)); driver.allocate($$);
                    }
  | E "^" E       {  
                        $$ = new OperationNode($1, "^", $3, driver.transformLocation(@2)); driver.allocate($$);
                    }
  | E "=" E { $$ = new ComparisonNode($1, "=", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E "<" E { $$ = new ComparisonNode($1, "<", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E ">" E { $$ = new ComparisonNode($1, ">", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E "<=" E { $$ = new ComparisonNode($1, "<=", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | E ">=" E { $$ = new ComparisonNode($1, ">=", $3, driver.transformLocation(@2)); driver.allocate($$); }
  | V { $$ = $1; }
  ;

V : MINUS C        %prec UMINUS   { $$ = new UnaryNode("-", $2, driver.transformLocation(@1)); }
  | PLUS C         %prec UPLUS    { $$ = $2; }
  | C { $$ = $1; }
  ; 
C : P { $$ = $1; }
  | L { $$ = $1; }
  | LEFT_BRACKET E RIGHT_BRACKET  { $$ = $2; }
;


A : B                              {  $$ = $1; }
  | /* empty */                    {  $$ = std::vector<ASTNode*>(); }
  ;

B : E                              { $$ = std::vector<ASTNode*>(); $$.emplace_back($1); }
  | B COMMA E                      { $$ = $1; $$.emplace_back($3); }
  ;

P : NUMBER                         { 
    $$ = new NumberNode($1, driver.locationStruct()); driver.allocate($$);
                                   }
  ;

L : IDENTIFIER LEFT_BRACKET A RIGHT_BRACKET {
    $$ = new FunctionNode($1, $3, driver.transformLocation(@1)); driver.allocate($$);
}
;
%%

void MathBase::Parser::error(const location &loc , const std::string &message) {
    std::stringstream ss;
    for (MathBase::ASTNode* node : driver.get_allocated_nodes()) {
        delete node;
    }
    driver.clear();
    if (!driver.hasError()) {
      driver.setError("parse", message);
    }
}
