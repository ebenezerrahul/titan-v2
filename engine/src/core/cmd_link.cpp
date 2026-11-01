#include <core/cmd_link.h>

CmdLink::CmdLink(const char *cmdName, CmdFunction function, const char *desc,
                 ArgCompletion argCompletion)
    : m_cmdName(cmdName), m_function(function), m_desc(desc),
      m_argCompletion(argCompletion) {
  m_next = CmdLink::list;
  list = this;
};
