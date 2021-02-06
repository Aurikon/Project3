add_llvm_library(LLVMRecursionCount MODULE RecursionCount.cpp

	PLUGIN_TOOL
	opt
)