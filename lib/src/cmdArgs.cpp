#include <cstdlib>
#include <cstring>
#include <lib/cmdArgs.h>
#include <string>

bool is_seprator(char c) { return ' ' == c; };

CmdArgs::CmdArgs(const char *cmdText) {
  i32 len = strlen(cmdText);
  if (len < 0) {
    std::exit(1);
  } else if (len == 0) {
    m_pool = nullptr;
    m_argc = 0;
  }
  m_pool = new char[len + 1];
  memcpy(m_pool, cmdText, len + 1);
  m_argc = 0;
  m_argv[m_argc] = m_pool;
  bool inToken = false;
  for (i32 i = 0; i <= len; i++) {
    if (is_seprator(cmdText[i])) {
      m_pool[i] = '\0';
      inToken = false;
    } else if (!inToken) {
      inToken = true;
      if (m_argc < MAX_ARGS) {
        m_argv[m_argc] = m_pool + i;
        m_argc++;
      }
    }
  }
}

i32 CmdArgs::Argc() { return m_argc; }

const char *CmdArgs::Argv(i32 idx) {
  if (idx >= 0 && idx < m_argc) {
    return m_argv[idx];
  }
  return "";
}

template <> i32 CmdArgs::Argv<i32>(i32 idx) {
  return std::atoi(this->Argv(idx));
}

template <> f32 CmdArgs::Argv<f32>(i32 idx) {
  return std::stof(this->Argv(idx));
}

CmdArgs::~CmdArgs() { delete[] m_pool; }
