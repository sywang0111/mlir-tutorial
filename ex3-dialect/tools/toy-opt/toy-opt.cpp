#include "mlir/IR/DialectRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
// 导入 Func Dialect
#include "mlir/Dialect/Func/IR/FuncOps.h"
// 导入 MLIR 自带 Pass
#include "mlir/Transforms/Passes.h"
// 导入我们新建的 Dialect
#include "toy/ToyDialect.h"
using namespace mlir;
using namespace llvm;

#include "mlir/IR/AsmState.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Support/FileUtilities.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "llvm/Support/raw_ostream.h"


#include <iostream>
int main(int argc, char ** argv) {
  if (argc == 3) {
  MLIRContext ctx;
  // 首先，注册需要的 dialect
  ctx.loadDialect<func::FuncDialect, toy::ToyDialect>();
  // 读入dialect
  auto src = parseSourceFile<ModuleOp>(argv[2], &ctx);
  // 输出原始dialect
  std::cout << "original: \n";
  src->print(llvm::outs());
  std::cout << "after optimization: \n";
  }

  DialectRegistry registry;
  // 注册 Dialect
  registry.insert<toy::ToyDialect, func::FuncDialect>();
  // 注册两个 Pass
  registerCanonicalizerPass();
  registerCSEPass();
  return asMainReturnCode(MlirOptMain(argc, argv, "toy-opt-try", registry));
}