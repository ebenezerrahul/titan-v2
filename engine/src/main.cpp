#include "core/cmd_link.h"
#include "core/cmdsystem.h"
#include <core/logger.h>

static Logger logger;
CONSOLE_COMMAND(sum, "sums n numbers") {
  i32 n = cmdArgs.Argc();
  i32 sum = 0;
  for (i32 i = 1; i < n; i++) {
    sum += cmdArgs.Argv<i32>(i);
  }
  logger.info("%d\n", sum);
}

int main() {
  logger.info("what the hell\n");
  cmdSystem->Init();
  CmdLink::Init();
  cmdSystem->Execute("sum 1 2 3 4");
}
