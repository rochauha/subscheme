#ifndef CAST_H
#define CAST_H

#include <cassert>
#include <cstddef>
#include <fstream>

#include <vector>

namespace C {

// This AST models the subset of valid C code, that the compiler will emit.
// It helps to work at the level of C constructs rather than raw strings.

class AstNode {

public:
  friend class Builder;
  enum Kind { Unkown = 0, TranslationUnit = 1, Function, ReturnStmt };

  AstNode();
  virtual ~AstNode();

  virtual void emit(std::ostream &os) const;

  Kind kind;
};

class ReturnStmt : protected AstNode {
public:
  friend class Builder;
  void emit(std::ostream &os) const override;

private:
  ReturnStmt(int64_t returnValue);
  int64_t returnValue;
};

class Function : protected AstNode {

public:
  friend class Builder;
  ~Function() = default;

  void emit(std::ostream &os) const override;

  void setBody(AstNode *body) { this->body = body; }

  bool hasBody() const { return body; }

private:
  Function(const std::string &name) : AstNode(), name(name), body(nullptr) {
    kind = AstNode::Function;
  }

  void emitHeader(std::ostream &os) const;

  void emitBody(std::ostream &os) const;

  // TODO:
  // add function types, parameters, statement blocks
  std::string name;
  AstNode *body;
};

class TranslationUnit final : protected AstNode {
public:
  friend class Builder;
  TranslationUnit() : AstNode() { kind = AstNode::TranslationUnit; }
  ~TranslationUnit() = default;

  void emit(std::ostream &os) const override;

  void addFunction(class Function *function) { functions.push_back(function); }

private:
  std::vector<class Function *> functions;
};

} // namespace C

#endif
