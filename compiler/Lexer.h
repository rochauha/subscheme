#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string_view>

class Lexer {
public:
  Lexer(std::string_view textBuffer)
      : textBuffer(textBuffer), curPtr(textBuffer.data()) {
    bufferEnd = curPtr + textBuffer.size();
  }

  Lexer(const Lexer &) = delete;
  void operator=(const Lexer &) = delete;

  Token lexToken();

private:
  Token createToken(Token::Kind kind, const char *tokenStart, size_t length) {
    return Token(kind, std::string_view(tokenStart, length));
  }

  Token lexNumber(const char *tokStart);

  Token lexSymbol(const char *tokStart);

  std::string_view textBuffer;
  const char *curPtr;
  const char *bufferEnd;
};

#endif
