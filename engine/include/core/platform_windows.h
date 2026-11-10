#pragma once
#include "platform.h"
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

class PlatformWindowsCtx : public PlatformContext {
public:
  PlatformWindowsCtx(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPWSTR lpCmdLine, int nCmdShow)
      : hInstance(hInstance), hPrevInstance(hPrevInstance),
        lpCmdLine(lpCmdLine), nCmdShow(nCmdShow) {}

  HINSTANCE hInstance;
  HINSTANCE hPrevInstance;
  LPWSTR lpCmdLine;
  int nCmdShow;
};
