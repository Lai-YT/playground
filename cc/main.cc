#include <clang/Basic/Diagnostic.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/FrontendOptions.h>
#include <llvm/ADT/SmallString.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/VirtualFileSystem.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#ifndef NDEBUG
#include <experimental/iterator>  // make_ostream_joiner
namespace stdx = std::experimental;
#endif  // NDEBUG

constexpr llvm::StringRef kTargetTriple = "x86_64-unknown-linux-gnu";
constexpr llvm::StringRef kClangExecutable = "clang";

namespace {

struct DiagSaver : clang::DiagnosticConsumer {
  void HandleDiagnostic(clang::DiagnosticsEngine::Level diag_level,
                        const clang::Diagnostic& info) override {
    clang::DiagnosticConsumer::HandleDiagnostic(diag_level, info);
    llvm::StringRef level;
    switch (diag_level) {
      case clang::DiagnosticsEngine::Note:
        level = "note";
        break;
      case clang::DiagnosticsEngine::Warning:
        level = "warning";
        break;
      case clang::DiagnosticsEngine::Error:
      case clang::DiagnosticsEngine::Fatal:
        level = "error";
        break;
      default:
        // Ignore other levels.
        return;
    }
    auto msg = llvm::SmallString<256>{};
    info.FormatDiagnostic(msg);
    auto& sm = info.getSourceManager();
    auto loc = info.getLocation();
    auto file_loc = sm.getFileLoc(loc);
    os << sm.getFilename(file_loc) << ":" << sm.getSpellingLineNumber(file_loc)
       << ":" << sm.getSpellingColumnNumber(file_loc) << ": " << level << ": "
       << msg << "\n";
    if (loc.isMacroID()) {
      loc = sm.getSpellingLoc(loc);
      os << sm.getFilename(loc) << ":" << sm.getSpellingLineNumber(loc) << ":"
         << sm.getSpellingColumnNumber(loc) << ": note: expanded from macro\n";
    }
  }

  std::string message;
  llvm::raw_string_ostream os{message};
};

std::pair<bool, std::string> Compile(int argc, const char* argv[]) {
  auto args = std::vector<const char*>(argv, argv + argc);
  args.at(0) = kClangExecutable.str().c_str();
#ifndef NDEBUG
  std::copy(args.begin(), args.end(),
            stdx::make_ostream_joiner(std::clog, " "));
  std::clog << "\n";
#endif  // NDEBUG
  auto fs = llvm::vfs::getRealFileSystem();
  auto dc = DiagSaver{};
  auto diags = clang::CompilerInstance::createDiagnostics(
      new clang::DiagnosticOptions{}, &dc, /*ShouldOwnClient=*/false);
  /*
   * First, we need to create a driver. The driver is responsible for
   * recognizing which compilation mode we are in (e.g. compile, link, etc.),
   * and for creating the compilation object.
   */
  auto driver =
      clang::driver::Driver(/*ClangExecutable=*/args.at(0), kTargetTriple,
                            *diags, /*Title=*/"cc", fs);
  auto Compilation = std::unique_ptr<clang::driver::Compilation>{
      driver.BuildCompilation(args)};
  const auto& jobs = Compilation->getJobs();
  if (jobs.size() != 1) {
    return {false, "Expected exactly one job"};
  }

  /*
   * Then, we create a compiler invocation to hold the jobs, which understands
   * the arguments passed to the compiler, e.g. -I, -D, etc.
   */
  auto invoc = std::make_shared<clang::CompilerInvocation>();
  clang::CompilerInvocation::CreateFromArgs(
      *invoc, jobs.begin()->getArguments(), *diags);

  /* Lastly, we create a compiler instance to execute the compilation. */
  auto ci = std::make_shared<clang::CompilerInstance>();
  ci->setInvocation(std::move(invoc));
  ci->createDiagnostics(&dc, /*ShouldOwnClient=*/false);
  ci->createFileManager(fs);
  ci->createSourceManager(ci->getFileManager());

  /*
   * Initialize the target and the target info. This is necessary to generate
   * code for the target architecture.
   */
  LLVMInitializeX86AsmParser();
  LLVMInitializeX86AsmPrinter();
  LLVMInitializeX86Target();
  LLVMInitializeX86TargetInfo();
  LLVMInitializeX86TargetMC();

  /*
   * Now we can choose the backend action to execute.
   */
  std::unique_ptr<clang::CodeGenAction> action = nullptr;
  switch (ci->getFrontendOpts().ProgramAction) {
    case clang::frontend::ActionKind::EmitObj: {
      action = std::make_unique<clang::EmitObjAction>();
    } break;
    case clang::frontend::ActionKind::EmitAssembly: {
      action = std::make_unique<clang::EmitAssemblyAction>();
    } break;
    default:
      return {false, "Unsupported action"};
  }
  auto ok = ci->ExecuteAction(*action);
  return {ok, std::move(dc.message)};
}

}  // namespace

int main(int argc, const char* argv[]) {
  auto [ok, msg] = Compile(argc, argv);
  if (!ok) {
    std::cerr << msg;
  } else {
    std::cout << msg;
  }
  return !ok;
}
