#ifndef CODEGEN_PASS_H
#define CODEGEN_PASS_H

#include "C/AST.h"
#include "C/Builder.h"
#include "SExpr.h"

class CodeGenPass {
public:
  CodeGenPass(C::Builder &builder) : builder(builder) {
    // create subschemeEntry by default
    C::Function *schemeEntry = builder.createEmptyFunction("schemeEntry");
    builder.switchToFunction(schemeEntry);
  }

  ~CodeGenPass() = default;

  void run(SExpr *expr);

private:
  C::Builder &builder;
};

#endif
