# subscheme

Lowering a purely functional dialect of scheme to C. More details coming soon...

Why do this in C++ when a lisp can be implemented in itself (in this case, using a subset of scheme)?

- First, the ability to manipulate lisp constructs within itself is very powerful and an implementation in a traditional systems-level flavour can highlight much of what goes on underneath.

- Second, using C++ opens the possibility to explore compilation for lisp and untyped functional languages in the context of LLVM/MLIR.


# Building

```
cmake -G Ninja <path to this repository>/compiler
./run-tests (in the build directory)
```

# License
MIT license