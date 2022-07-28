#include "Context.h"
#include "Lexer.h"
#include "Parser.h"

#include <charconv>
#include <fstream>
#include <string_view>

Context::Context(const char *filePath) {
  txtBuf = getTextBuffer(filePath);
  Lexer lexer(std::string_view(txtBuf.bytes, txtBuf.length));
  Parser parser(lexer, *this);

  parser.parse();
  this->topLevelExprs = parser.getTopLevelExprs();
}

TextBuffer Context::getTextBuffer(const char *filePath) {
  std::ifstream file(filePath, std::ios::in);

  if (!file.is_open()) {
    std::cout << "could not open " << filePath << '\n';
    exit(1);
  }

  file.seekg(0, file.end);
  size_t length = file.tellg();
  file.seekg(0, file.beg);

  char *bytes = new char[length];
  file.read(bytes, length);

  file.close();
  return TextBuffer{bytes, length};
}

SExpr *Context::createIntLiteral(std::string_view integerStr) {
  int64_t integer;
  const std::from_chars_result result = std::from_chars(
      integerStr.data(), integerStr.data() + integerStr.size(), integer);

  if (result.ec == std::errc::invalid_argument ||
      result.ec == std::errc::result_out_of_range) {
    std::cout << "error in creating integer literal... exiting...\n";
    exit(1);
  }

  SExpr *intLiteral = new SExpr(SExpr::Integer, integer);
  allocatedExprs.push_back(intLiteral);
  return intLiteral;
}

SExpr *Context::createSymbolAtom(std::string_view symbolName) {
  SExpr *expr = new SExpr(SExpr::Symbol, symbolName);
  allocatedExprs.push_back(expr);
  return expr;
}

SExpr *Context::createPair(SExpr *first, SExpr *rest) {
  SExpr *pair = new SExpr(SExpr::Pair, first, rest);
  allocatedExprs.push_back(pair);
  return pair;
}

SExpr *Context::createEmptySExpr() {
  SExpr *empty = new SExpr(SExpr::Empty);
  allocatedExprs.push_back(empty);
  return empty;
}

Context::~Context() {
  for (SExpr *expr : allocatedExprs) {
    delete expr;
  }
}
