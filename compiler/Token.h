#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>
#include <string_view>

class Token {
public:
  enum Kind { Integer, Lparen, Rparen };

  Token() = default;

  Token(Kind k, std::string_view text) : kind(k), text(text) {}

  Token(const Token &other) : kind(other.getKind()), text(other.getText()) {}

  Kind getKind() const { return kind; }

  std::string_view getText() const { return text; }

  void dump(std::ostream &os) const {
    os << '[';
    switch (kind) {
    case Integer:
      os << "Integer";
      break;
    case Lparen:
      os << "Lparen";
      break;
    case Rparen:
      os << "Rparen";
      break;
    }
    os << ' ' << text << ']' << '\n';
  }

private:
  Kind kind;
  std::string_view text;
};

#endif
