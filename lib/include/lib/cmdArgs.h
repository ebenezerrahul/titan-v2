#pragma once
#include "defines.h"

class CmdArgs {
public:
  // cmdText needs to be null Terminated
  CmdArgs(const char *cmdText);
  ~CmdArgs();
  i32 Argc();
  const char *Argv(i32 idx);
  CmdArgs(const CmdArgs &) = delete;
  CmdArgs &operator=(const CmdArgs &) = delete;
  template <typename T> T Argv(i32 idx);

private:
  i32 m_argc;
  char *m_pool;
  static const i32 MAX_ARGS = 64;
  char *m_argv[MAX_ARGS] = {0};
};
