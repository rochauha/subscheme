#ifndef CODE_BUILDER_H
#define CODE_BUILDER_H

#include "AST.h"

namespace C {

// This class allows us to 'build-up' C code at the AST level and finally emit
// it to a file.

class Builder {
public:
  Builder() : currentFunction(nullptr), transUnit(new TranslationUnit){};
  Builder(Builder &) = delete;
  ~Builder() = default; // TODO: cleanup in the destructor

  ReturnStmt *createReturnStmt(int64_t returnValue);

  Function *createEmptyFunction(std::string name) {
    auto function = new Function(name);
    transUnit->addFunction(function);
    return function;
  }

  Function *getCurrentFunction() const {
    assert(currentFunction && "currentFunction must be non-null");
    return currentFunction;
  }

  void switchToFunction(Function *function) {
    assert(function && "function must be non-null");
    currentFunction = function;
  }

  void emitCodeToStream(std::ostream &os) const;

  void emitCodeToFile(const std::string &filePath) const;

private:
  Function *currentFunction;

  TranslationUnit *transUnit;

  std::vector<AstNode *> allocatedNodes;
};

} // namespace C

#endif
