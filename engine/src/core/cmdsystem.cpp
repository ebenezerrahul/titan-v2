#include <core/cmdsystem.h>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>

class CmdDefination {
public:
  const char *cmdName;
  CmdFunction function;
  const char *desc;
  ArgCompletion argCompletion;

  CmdDefination() {}

  CmdDefination(const char *cmdName, CmdFunction function, const char *desc,
                ArgCompletion argCompletion)
      : cmdName(cmdName), function(function), desc(desc),
        argCompletion(argCompletion) {}
};

class CmdSystemImpl : public CmdSystem {
public:
  virtual ~CmdSystemImpl() {}
  virtual void AddCommand(const char *cmdName, CmdFunction function,
                          const char *desc,
                          ArgCompletion argCompletion = nullptr);
  virtual void Init();
  virtual void Execute(const char *cmd);

private:
  CmdDefination *FindExactCommandDefination(const char *cmdName);
  std::shared_mutex m_mutex;
  std::unordered_map<std::string, CmdDefination *> m_cmdMap;
};

CmdSystemImpl cmdSystemImpl;
CmdSystem *cmdSystem = &cmdSystemImpl;

void CmdSystemImpl::Init() {};

void CmdSystemImpl::AddCommand(const char *cmdName, CmdFunction function,
                               const char *desc, ArgCompletion argCompletion) {

  if (!cmdName || !desc || !function) {
    printf("should not be like this");
    return;
  }

  std::unique_lock<std::shared_mutex> writeLock(m_mutex);
  auto it = m_cmdMap.find(cmdName);
  if (it != m_cmdMap.end()) {
    // NOTE: remove the printf
    printf("error command already exists %s", cmdName);
    return;
  }
  // NOTE: Think about allocation here
  m_cmdMap[cmdName] = new CmdDefination(cmdName, function, desc, argCompletion);
};

CmdDefination *CmdSystemImpl::FindExactCommandDefination(const char *cmdName) {
  std::shared_lock<std::shared_mutex> readLock(m_mutex);
  auto it = m_cmdMap.find(cmdName);
  if (it == m_cmdMap.end()) {
    return nullptr;
  }
  return it->second;
}

void CmdSystemImpl::Execute(const char *cmd) {
  CmdArgs cmdArgs(cmd);
  int n = cmdArgs.Argc();
  if (n <= 0) {
    printf("No cmd to execute");
    return;
  }
  CmdDefination *def = FindExactCommandDefination(cmdArgs.Argv(0));
  if (!def) {
    printf("cmd not found\n");
    return;
  }
  def->function(cmdArgs);
};
