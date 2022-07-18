#ifndef TOKEN_H
#define TOKEN_H

#include <string_view>

class Token {
public:
  enum Kind { Integer };

  Token(Kind k, std::string_view text) : kind(k), text(text) {}

  Kind getKind() const { return kind; }

  std::string_view getText() const { return text; }

private:
  Kind kind;
  std::string_view text;
};

#endif
