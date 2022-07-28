#ifndef SEXPR_H
#define SEXPR_H

#include <cstddef>
#include <iostream>

class SExpr {
  friend class Context;

public:
  enum Kind { Empty = 1, Integer, Symbol, Pair };

  Kind getKind() const { return kind; }

  bool isEmpty() const;

  bool isPair() const { return kind == Pair; }

  bool isAtom() const { return !isEmpty() && !isPair(); }

  bool isInteger() const { return kind == Integer; }

  bool isList() const;

  SExpr *getCar() const { return car; }

  SExpr *getCdr() const { return cdr; }

  int64_t getAsInteger() const;

  const char *getAsSymbol() const;

  void dump(std::ostream &os) const;

private:
  SExpr(Kind k);

  SExpr(Kind k, int64_t intLiteral);

  SExpr(Kind k, char *symbolName);

  SExpr(Kind k, SExpr *car, SExpr *cdr);

  Kind kind;

  int64_t integerLiteral;

  char *symbolName;

  SExpr *car;

  SExpr *cdr;
};

#endif
