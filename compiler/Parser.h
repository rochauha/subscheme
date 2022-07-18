#ifndef PARSER_H
#define PARSER_H

#include "Context.h"
#include "Lexer.h"
#include "SExpr.h"

#include <vector>

class Parser {
public:
  Parser(Lexer &lexer, Context &context)
      : lexer(lexer), context(context), nestingLevel(0) {}

  SExpr *parse();

  const std::vector<SExpr *> &getTopLevelExprs() const { return topLevelExprs; }

private:
  Lexer &lexer;

  Context &context;

  std::vector<SExpr *> topLevelExprs;

  int nestingLevel;
};

#endif
