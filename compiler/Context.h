#ifndef CONTEXT_H
#define CONTEXT_H

#include "C/Builder.h"
#include "SExpr.h"

#include <string_view>
#include <vector>

struct TextBuffer {
  char *bytes;
  size_t length;
};

class Context {
public:
  Context(const char *filePath);

  ~Context();

  const std::vector<SExpr *> getTopLevelExprs() const { return topLevelExprs; }

  SExpr *createEmptySExpr();

  SExpr *createIntLiteral(std::string_view integerStr);

  SExpr *createPair(SExpr *first, SExpr *rest);

private:
  TextBuffer getTextBuffer(const char *filePath);

  std::vector<SExpr *> topLevelExprs;

  TextBuffer txtBuf;
  std::vector<SExpr *> allocatedExprs;
};

#endif
