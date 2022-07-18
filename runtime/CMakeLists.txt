add_library(subscheme-rt STATIC
  runtime.c
)

set_property(TARGET subscheme-rt PROPERTY C_STANDARD 11)
set_property(TARGET subscheme-rt PROPERTY C_STANDARD_REQUIRED ON)


