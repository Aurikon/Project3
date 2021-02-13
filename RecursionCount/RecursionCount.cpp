#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct RecursionCount : public ModulePass 
{
  static char ID;
  RecursionCount() : ModulePass(ID) {}
  static unsigned int count;
  bool runOnModule(Module &M) override 
  {
		for(auto &function : M)
		{
  			bool isFound = false;
  			for(auto &basicBlock : function)
  			{
  				if(isFound)
  				{
  					isFound = false;
  					break;
  				}
  				for(auto &instruction : basicBlock)
  				{
  					if(CallInst* callInst = dyn_cast<CallInst>(&instruction))
  					{
  						if(Function* calledFunction = callInst->getCalledFunction())
  						{
  							if(calledFunction->getName() == function.getName())
  							{
  								errs() << function.getName() << " is recursive\n";
  								++count;
  								isFound = true;
  								break;
  							}
  						}
  					}
  				}
  			}
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
static RegisterPass<RecursionCount> X("RecursionCount", "RecursionCount Pass",
                             false, false);