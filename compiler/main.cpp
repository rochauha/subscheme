#include "CodeGenPass.h"
#include "Context.h"
#include "SExpr.h"

#include <cassert>
#include <iostream>

int main(int argc, char **argv) {
  assert(argc == 2 && "pass only one argument - the path to the source file");

  const char *filePath = argv[1];

  Context ctx(filePath);
  C::Builder builder;
  CodeGenPass CGP(builder);

  auto exprs = ctx.getTopLevelExprs();
  CGP.run(exprs[0]);
  builder.emitCodeToStream(std::cout);
}
