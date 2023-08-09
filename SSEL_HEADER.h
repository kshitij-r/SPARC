#ifndef SSEL
#define SSEL

#include "map_header.h"
#ifndef __clang__
#include <thread>
#include <iostream>
#include <chrono>
#endif
#include <assert.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <queue>
#include <mutex>
#include <map>
#include "guard.h"
#include <klee/klee.h>
#include "baseIP.cpp"
#include "sys_map.cpp"
#include "memory_model.cpp"
// #include "crc_module.cpp"
#include "slave_config.cpp"
#include "interface.cpp"
#include "map_header.h"
// #include "/usr/include/llvm-6.0/llvm/Bitcode/BitcodeReader.h"
// #include "llvm/IR/Constants.h"
// #include "llvm/IR/IRBuilder.h"
// #include "llvm/IR/InstrTypes.h"
// #include "llvm/IR/Instruction.h"
// #include "llvm/IR/Instructions.h"
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Type.h"
// #include "llvm/Support/CommandLine.h"
// #include "llvm/Support/Errno.h"
// #include "llvm/Support/FileSystem.h"
// #include "llvm/Support/Host.h"
// #include "llvm/Support/ManagedStatic.h"
// #include "llvm/Support/MemoryBuffer.h"
// #include "llvm/Support/Path.h"
// #include "llvm/Support/raw_ostream.h"

// #include "llvm/Support/TargetSelect.h"
// #include "llvm/Support/Signals.h"
// #include "timer.cpp"
using namespace std;
using namespace std::literals::chrono_literals;

template <typename T>
void wait__(T condition){};
#endif