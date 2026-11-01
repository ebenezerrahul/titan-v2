#pragma once
#include "cmdsystem.h"

// compiletime List of static cmdFunctions that all are registered to CmdSystem
// at runtime automatically
// Along with ConsoleCommands Macro Idea is to implement kind of component Scan
class CmdLink {
public:
  CmdLink(const char *cmdName, CmdFunction function, const char *desc,
          ArgCompletion argCompletion = nullptr);
  static void Init() {
    if (initialized)
      return;
    CmdLink *current = list;
    while (current) {

      cmdSystem->AddCommand(current->m_cmdName, current->m_function,
                            current->m_desc, current->m_argCompletion);
      current = current->m_next;
    }
  }

private:
  const char *m_cmdName;
  CmdFunction m_function;
  const char *m_desc;
  ArgCompletion m_argCompletion = nullptr;
  CmdLink *m_next = nullptr;
  static inline CmdLink *list = nullptr;
  static inline bool initialized = false;
};

#define CONSOLE_COMMAND(name, desc)                                            \
  void cmd_##name_impl(CmdArgs &cmdArgs);                                      \
  static CmdLink cmd_##name_link(#name, cmd_##name_impl, desc);                \
  void cmd_##name_impl(CmdArgs &cmdArgs)
