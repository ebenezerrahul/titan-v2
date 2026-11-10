#include "core/cmd_link.h"
#include "core/cmdsystem.h"
#include <core/logger.h>
#include <core/platform.h>

#include "core/platform_windows.h"

CONSOLE_COMMAND(sum, "sums n numbers") {
  i32 n = cmdArgs.Argc();
  i32 sum = 0;
  for (i32 i = 1; i < n; i++) {
    sum += cmdArgs.Argv<i32>(i);
  }
  logger.info("%d\n", sum);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, int nCmdShow) {

  logger.info("what the hell\n");
  PlatformContext *ctx =
      new PlatformWindowsCtx(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
  platform->Init(ctx);
  cmdSystem->Init();
  CmdLink::Init();
  cmdSystem->Execute("sum 1 2 3 4");
  platform->CreatePlatformWindow(0, 0, "TITAN GAME");
  while (true) {
    platform->pump_messages();
  }

  platform->Shutdown();
  return 0;
}
