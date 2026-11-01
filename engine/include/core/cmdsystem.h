#pragma once
#include <lib/cmdArgs.h>

using CmdFunction = void (*)(CmdArgs &);
using ArgCompletionCallback = bool (*)(const char *);
using ArgCompletion = void (*)(CmdArgs &, ArgCompletionCallback callback);

class CmdSystem {
public:
  virtual ~CmdSystem() {}
  virtual void AddCommand(const char *cmdName, CmdFunction function,
                          const char *desc,
                          ArgCompletion argCompletion = nullptr) = 0;
  virtual void Init() = 0;
  virtual void Execute(const char *cmd) = 0;
};

extern CmdSystem *cmdSystem;
