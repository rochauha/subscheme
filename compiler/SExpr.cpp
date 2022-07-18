#include "SExpr.h"

#include <cassert>

SExpr::SExpr(Kind k) {
  assert(k == Empty && "this constructor only creates empty SExprs");
  kind = k;
  symbolName = nullptr;
  car = nullptr;
  cdr = nullptr;
}

SExpr::SExpr(Kind k, int64_t intLiteral) {
  assert(k == Integer && "this constructor only creates integers");
  kind = k;
  integerLiteral = intLiteral;
  symbolName = nullptr;
  car = nullptr;
  cdr = nullptr;
}

SExpr::SExpr(Kind k, char *symbolName) {
  assert(k == Symbol && "this constructor only creates symbolic values");
  kind = k;
  this->symbolName = symbolName;
  car = nullptr;
  cdr = nullptr;
}

SExpr::SExpr(Kind k, SExpr *car, SExpr *cdr) {
  assert(k == Pair && "this constructor only creates compound s-expressions");
  assert(car && cdr && "car and cdr musb be non-null");
  kind = k;
  this->car = car;
  this->cdr = cdr;
}

int64_t SExpr::getAsInteger() const {
  assert(kind == Integer);
  return integerLiteral;
}

bool SExpr::isEmpty() const {
  assert(car == nullptr && cdr == nullptr &&
         "Empty SExpr must not have a car and cdr");
  return kind == Empty;
}

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

  default:
    os << '(';

    assert(car && cdr);
    car->dump(os);
    os << " . ";
    cdr->dump(os);

    os << ')';
  }
}
