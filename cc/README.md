# Compiling C++ with the Clang API

> [!IMPORTANT]
> Merely copies the code from the post [MaskRay, Compiling C++ with the Clang API, 2025](https://maskray.me/blog/2025-03-09-compiling-c++-with-clang-api), with Google-Style conventions.

## How to Build?

```console
mkdir build
cmake -G Ninja \
  -B build \
  -DCMAKE_PREFIX_PATH=$(llvm-config --cmakedir) \
  -DLLVM_DIR=$(llvm-config --cmakedir) \
  -DClang_DIR=$(llvm-config --libdir)/cmake/clang \
  .
cmake --build build
```

> [!NOTE]
> Is only tested with LLVM 19.

## How to Run?

```console
build/cc [-S|-c] file.cc
```
