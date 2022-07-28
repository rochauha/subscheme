#include "Lexer.h"

#include <cassert>
#include <cctype>
#include <iostream>

Token Lexer::lexToken() {
  while (curPtr != bufferEnd) {
    switch (*curPtr) {
    case ' ':
    case '\n':
    case '\t':
      ++curPtr;
      continue;

    case '(':
      ++curPtr;
      return createToken(Token::Lparen, curPtr - 1, 1);

    case ')':
      ++curPtr;
      return createToken(Token::Rparen, curPtr - 1, 1);

    // ignore comments
    case ';':
      while (*curPtr != '\n')
        ++curPtr;
      continue;

    case '+':
      if (&curPtr[1] != bufferEnd &&
          isdigit(curPtr[1])) // ignore '+' if it is used to indicate sign
        ++curPtr;
      continue; // todo, + can also be standalone

    case '-':
      if (&curPtr[1] != bufferEnd && isdigit(curPtr[1])) {
        return lexNumber(curPtr);
      }
      continue; // todo, - can also be standalone

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return lexNumber(curPtr);
    }
  }
}

Token Lexer::lexNumber(const char *tokenStart) {
  assert(curPtr != bufferEnd);
  assert(isdigit(*curPtr) || *curPtr == '-');

  if (*curPtr == '-')
    ++curPtr;

  while (curPtr != bufferEnd && isdigit(*curPtr))
    ++curPtr;

  size_t length = curPtr - tokenStart;
  return createToken(Token::Integer, tokenStart, length);
}
