#include "Parser.h"

#include <cassert>

SExpr *Parser::parse() {
  Token token = lexer.lexToken();
  if (token.getKind() == Token::Integer) {
    SExpr *expr = context.createIntLiteral(token.getText());
    if (nestingLevel == 0)
      topLevelExprs.push_back(expr);

    return expr;
  }

  assert(false && "token not an integer!");
}
