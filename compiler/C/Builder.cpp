#include "Builder.h"

#include <fstream>
#include <iostream>

namespace C {

ReturnStmt *Builder::createReturnStmt(int64_t returnValue) {
  ReturnStmt *newStmt = new ReturnStmt(returnValue);
  allocatedNodes.push_back(newStmt);
  return newStmt;
}

void Builder::emitCodeToStream(std::ostream &os) const {
  transUnit->emit(os);
  std::flush(os);
}

void Builder::emitCodeToFile(const std::string &filePath) const {
  std::ofstream file(filePath, std::ios::out);

  if (!file.is_open()) {
    std::cout << "could not open " << filePath << '\n';
    exit(1);
  }

  transUnit->emit(file);
  file.close();
}

} // namespace C
