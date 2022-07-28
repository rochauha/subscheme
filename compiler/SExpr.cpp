#include "SExpr.h"

#include <cassert>

SExpr::SExpr(Kind k) {
  assert(k == Empty && "this constructor only creates empty SExprs");
  kind = k;
  symbolName = nullptr;
  first = nullptr;
  rest = nullptr;
}

SExpr::SExpr(Kind k, int64_t intLiteral) {
  assert(k == Integer && "this constructor only creates integers");
  kind = k;
  integerLiteral = intLiteral;
  symbolName = nullptr;
  first = nullptr;
  rest = nullptr;
}

SExpr::SExpr(Kind k, char *symbolName) {
  assert(k == Symbol && "this constructor only creates symbolic values");
  kind = k;
  this->symbolName = symbolName;
  first = nullptr;
  rest = nullptr;
}

SExpr::SExpr(Kind k, SExpr *first, SExpr *rest) {
  assert(k == Pair && "this constructor only creates compound s-expressions");
  assert(first && "first must be non-null");
  assert(rest && "rest must be non-null");
  kind = k;
  this->first = first;
  this->rest = rest;
}

int64_t SExpr::getAsInteger() const {
  assert(kind == Integer);
  return integerLiteral;
}

bool SExpr::isEmpty() const { return kind == Empty; }

void SExpr::dump(std::ostream &os) const {
  switch (kind) {
  case Empty:
    os << "()";
    break;

  case Integer:
    os << integerLiteral;
    break;

  case Symbol:
    os << symbolName;
    break;

  case Pair:
    os << '(';
    first->dump(os);
    os << " . ";
    rest->dump(os);
    os << ')';
  }
}

bool SExpr::isList() const {
  if (!isPair())
    return false;

  const SExpr *currentPair = this;
  while (currentPair->getRest()) {
    currentPair = currentPair->getRest();
  }

  if (currentPair->isEmpty())
    return true;

  return false;
}
