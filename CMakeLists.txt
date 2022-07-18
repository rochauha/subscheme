cmake_minimum_required(VERSION 3.20)

project(subscheme)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(compiler)
add_subdirectory(runtime)

# Creating the run-tests script
file(READ
  ${CMAKE_SOURCE_DIR}/test/script-contents
  scriptContents
)

file(WRITE
  ${CMAKE_BINARY_DIR}/run-tests
  "#!/bin/bash\n\nsourcePath=\"${CMAKE_SOURCE_DIR}\"\nbuildPath=\"${CMAKE_BINARY_DIR}\"\n"
)

file(APPEND
  ${CMAKE_BINARY_DIR}/run-tests
  "${scriptContents}"
)

file(CHMOD
  ${CMAKE_BINARY_DIR}/run-tests
  FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
)
