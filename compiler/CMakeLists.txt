add_executable(ssc
  main.cpp
  SExpr.cpp
  Lexer.cpp
  Parser.cpp
  Context.cpp
  CodeGenPass.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/C/AST.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/C/Builder.cpp
)

set_property(TARGET ssc PROPERTY CXX_STANDARD 17)
set_property(TARGET ssc PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(ssc PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(ssc PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)
