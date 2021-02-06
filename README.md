# LLVM Recursive Functions Count Pass

This is a LLVM Pass for counting recursive functions. 

# Installation and running

1. You should build LLVM: https://github.com/llvm/llvm-project

2. Move the folder RecursionCount to next path:

`` llvm-project/llvm/lib/Transform ``

3. Copy next line into llvm-project/llvm/lib/Transforms/CMakeLists.txt

`` add_subdirectory(RecusrsionCount) ``

4. Again build your llvm

5. Run pass with next command: 

``opt -load lib/LLVMRecursionCount.so -RecursionCount < /path/to/.bc > /dev/null ``
