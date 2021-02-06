#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct RecursionCount : public FunctionPass 
{
  static char ID;
  RecursionCount() : FunctionPass(ID) {}
  static unsigned int count;
  bool runOnFunction(Function &F) override 
  {
  	if(!F.doesNotRecurse())
  	{
    	errs().write_escaped(F.getName()) << " is recursive \n";
    	++count;
    }
    return false;
  }
  ~RecursionCount()
  {
  	errs() << count << " recursive functions \n";
  }
}; 
}  

unsigned int RecursionCount::count = 0;
char RecursionCount::ID = 0;
static RegisterPass<RecursionCount> X("RecusrionCount", "RecursionCount Pass",
                             false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new RecursionCount()); });