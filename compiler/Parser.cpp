#include "Parser.h"

#include <cassert>

SExpr *Parser::parse() {
  currentToken = lexer.lexToken();
  SExpr *expr = nullptr;

  switch (currentToken.getKind()) {
  case Token::Integer:
    expr = parseInteger();
    break;

  case Token::Lparen:
    expr = parseSExpr();
    break;

  case Token::Rparen:
    expr = context.createEmptySExpr();
    break;
  }

  if (nestingLevel == 0)
    topLevelExprs.push_back(expr);

  return expr;
}

SExpr *Parser::parseInteger() {
  assert(currentToken.getKind() == Token::Integer);
  return context.createIntLiteral(currentToken.getText());
}

SExpr *Parser::parseSExpr() {
  ++nestingLevel;

  SExpr *currentFirst = parse();

  if (currentFirst->isEmpty()) {
    --nestingLevel;
    return currentFirst;
  }

  SExpr *currentRest = parseSExpr();
  --nestingLevel;
  return context.createPair(currentFirst, currentRest);
}
