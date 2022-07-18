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
  SExpr *createIntLiteral(std::string_view integerStr);

  Context(const char *filePath);

  ~Context();

  const std::vector<SExpr *> getTopLevelExprs() const { return topLevelExprs; }

private:
  TextBuffer getTextBuffer(const char *filePath);

  std::vector<SExpr *> topLevelExprs;

  TextBuffer txtBuf;
  std::vector<SExpr *> allocatedExprs;
};

#endif
