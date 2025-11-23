

#include "interpreter.h"
#include "command.h"

#include <sstream>

using namespace MathBase;

Interpreter::Interpreter() :
    m_asts(),
    m_scanner(*this),
    m_parser(m_scanner, *this),
    m_location(0)
{
    m_filename = "";
    m_track_filename = false;
    m_track_line = false;
}

int Interpreter::parse() {
    m_location = location(&m_filename);
    return m_parser.parse();
}



void Interpreter::clear() {
    m_location = location(&m_filename);
    m_asts.clear();
    m_allocated_nodes.clear();
}

std::string Interpreter::str() const {
    std::stringstream s;
    s << "Interpreter: " << m_asts.size() << " expressions received from command line." << std::endl;
    for (AST* ast : m_asts) {
        s << ast->str() << std::endl;
    }
    return s.str();
}

std::size_t Interpreter::total_asts() const {
    return m_asts.size();
}
AST* Interpreter::get_ast(std::size_t index) const {
    if (index < 0 || index >= m_asts.size()) {
        return nullptr;
    }
    return m_asts[index];
}

void Interpreter::switchInputStream(std::istream *is) {
    m_scanner.switch_streams(is, NULL);
    m_asts.clear();    
}

void Interpreter::configLocation(std::string filename, bool track_filename, bool track_line) {
    m_filename = filename;
    m_track_filename = track_filename;
    m_track_line = track_line;
}

void Interpreter::addAST(AST* ast)
{
    m_asts.push_back(ast);
}

void Interpreter::increaseLocation(std::string loc) {
    for (char& ch : loc) {
        if (ch == '\n') {
            if (m_track_line) {
                m_location.lines();
            } else {
                m_location.columns();
            }
        } else {
            m_location.columns();
        }
    }
    m_location.step();
}

location Interpreter::getLocation() const {
    return m_location;
}

merr::LocationStruct Interpreter::transformLocation(location loc) const {
    std::string filename = "";
    if (m_track_filename) {
        filename = m_filename;
    }
    bool absolute = !m_track_line;
    int column = static_cast<int>(loc.end.column);
    int line = static_cast<int>(loc.end.line);
    return merr::LocationStruct(filename, line, column, absolute);
}

merr::LocationStruct Interpreter::locationStruct() const {
    return transformLocation(m_location);
}


std::vector<AST*> Interpreter::get_asts() {
    return m_asts;
}
void Interpreter::allocate(ASTNode* node) {
    m_allocated_nodes.push_back(node);
}
std::vector<ASTNode*> Interpreter::get_allocated_nodes() {
    return m_allocated_nodes;
}

merr::MathError Interpreter::getError() {
    return this->m_errorFlag.get();
}
bool Interpreter::hasError() {
    return this->m_errorFlag.hasError();
}
void Interpreter::setError(std::string type, std::string error) {
    merr::MathErrorType mathErrorType = merr::toErrorType(type);
    merr::LocationStruct loc = locationStruct();
    merr::MathError mathError = merr::MathError(mathErrorType, error, &loc);
    m_errorFlag.set(mathError);
}
void Interpreter::clrError() {
    this->m_errorFlag.clr();
}