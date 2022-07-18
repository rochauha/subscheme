#include "AST.h"

#include <cassert>

namespace C {

//-------------------------------- AstNode -------------------------------------
//
AstNode::AstNode() {}

AstNode::~AstNode() {}

void AstNode::emit(std::ostream &os) const { os << '\n'; }

//------------------------------- ReturnStmt -----------------------------------
//
ReturnStmt::ReturnStmt(int64_t returnValue) {
  kind = AstNode::ReturnStmt;
  this->returnValue = returnValue;
}

void ReturnStmt::emit(std::ostream &os) const {
  os << "return";
  os << ' ';
  os << returnValue;
  os << ';';
}

//-------------------------------- Function ------------------------------------
//
void Function::emitHeader(std::ostream &os) const {
  os << "int " << name << "()";
}

void Function::emitBody(std::ostream &os) const {
  assert(hasBody());

  os << '{' << '\n';
  body->emit(os);
  os << '}' << '\n';
}

void Function::emit(std::ostream &os) const {
  emitHeader(os);
  if (hasBody())
    emitBody(os);
}

//---------------------------- TranslationUnit ---------------------------------
//
void TranslationUnit::emit(std::ostream &os) const {
  for (auto function : functions) {
    function->emit(os);
    os << '\n';
  }
}

} // namespace C
