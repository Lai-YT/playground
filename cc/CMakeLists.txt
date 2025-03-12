cmake_minimum_required(VERSION 3.16)
project(cc)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
find_package(Clang REQUIRED CONFIG)
message(STATUS "Found Clang ${LLVM_VERSION}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_CMAKE_DIR}")

include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
add_executable(cc main.cc)

if (NOT LLVM_ENABLE_RTTI)
  target_compile_options(cc PRIVATE -fno-rtti)
endif()

if (CLANG_LINK_CLANG_DYLIB)
  target_link_libraries(cc PRIVATE clang-cpp)
else()
  target_link_libraries(cc PRIVATE
    clangAST
    clangBasic
    clangCodeGen
    clangDriver
    clangFrontend
    clangLex
    clangParse
    clangSema
  )
endif()

if (LLVM_LINK_LLVM_DYLIB)
  target_link_libraries(cc PRIVATE LLVM)
else()
  target_link_libraries(cc PRIVATE
    LLVMOption
    LLVMSupport
    LLVMTarget
    LLVMX86AsmParser
    LLVMX86CodeGen
    LLVMX86Desc
  LLVMX86Info
  )
endif()


