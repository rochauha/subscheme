#include "CodeGenPass.h"

void CodeGenPass::run(SExpr *expr) {
  switch (expr->getKind()) {
  case SExpr::Integer: {
    C::ReturnStmt *returnStmt = builder.createReturnStmt(expr->getAsInteger());
    auto F = builder.getCurrentFunction();
    F->setBody(reinterpret_cast<C::AstNode *>(returnStmt));
    break;
  }

  default:
    break;
  }
};
