
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>

#include "scanner.h"
#include "location.hh"
#include "../merr/errloc.h"

#include "parser.hpp"

namespace MathBase {


/**
 * This class is the interface for our scanner/lexer. The end user
 * is expected to use this. It drives scanner/lexer, keeps
 * parsed AST and generally is a good place to store additional
 * context data. Both parser and lexer have access to it via internal 
 * references.
 * 
 * I know that the AST is a bit too strong word for a simple
 * vector with nodes, but this is only an example. Get off me.
 */
class Interpreter
{
public:
    Interpreter();
    
    /**
     * Run parser. Results are stored inside.
     * \returns 0 on success, 1 on failure
     */
    int parse();
    
    /**
     * Clear AST
     */
    void clear();
    
    /**
     * Print AST
     */
    std::string str() const;

    std::vector<AST*> get_asts();
    std::vector<ASTNode*> get_allocated_nodes();

    void allocate(ASTNode* node);
    void setError(std::string type, std::string error);
    bool hasError();
    /**
     * Switch scanner input stream. Default is standard input (std::cin).
     * It will also reset AST.
     */
    void switchInputStream(std::istream *is);
    void configLocation(std::string filename, bool track_filename=true, bool track_line=true);
    
    /**
     * This is needed so that Scanner and Parser can call some
     * methods that we want to keep hidden from the end user.
     */
    friend class Parser;
    friend class Scanner;
    
private:
    // Used internally by Parser to insert AST nodes.
    void addAST(AST *ast);
    
    // Used internally by Scanner YY_USER_ACTION to update location indicator
    void increaseLocation(std::string loc);
    
    // Used to get last Scanner location. Used in error messages.
    location getLocation() const;
    merr::LocationStruct locationStruct() const;
    merr::LocationStruct transformLocation(location loc) const;
    
private:
    Scanner m_scanner;
    Parser m_parser;
    std::vector<AST*> m_asts;
    location m_location;          // Used by scanner
    std::string m_filename;
    bool m_track_filename;
    bool m_track_line;
    std::vector<ASTNode*> m_allocated_nodes;
};

}

#endif // INTERPRETER_H
