#include "core/platform_windows.h"
#include "Tracy.hpp"
#include "core/platform.h"
#include <cstdio>
#include <minwindef.h>
#include <windows.h>
class PlatformWindows : public Platform {
  void virtual Init(PlatformContext *ctx) override;
  void virtual CreatePlatformWindow(const int x, const int y,
                                    const char *title) override;
  void virtual pump_messages() override;
  void virtual Shutdown() override { delete ctx; }

private:
  PlatformWindowsCtx *ctx;
};

PlatformWindows platformWindows;
Platform *platform = &platformWindows;

void PlatformWindows::Init(PlatformContext *ctx) {
  PlatformWindowsCtx *win_ctx = nullptr;
  if (!(this->ctx = dynamic_cast<PlatformWindowsCtx *>(ctx))) {
    // NOTE:Decide wether or not to log it
    std::exit(1);
  }
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  ZoneScoped;
  switch (uMsg) {
  case WM_QUIT:
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void PlatformWindows::CreatePlatformWindow(const int x, const int y,
                                           const char *title) {
  const wchar_t CLASS_NAME[] = L"TITAN ENGINE";
  WNDCLASS wc = {};
  wc.lpszClassName = CLASS_NAME;
  wc.hInstance = ctx->hInstance;
  wc.lpfnWndProc = WindowProc;
  if (!RegisterClass(&wc)) {
    std::printf("RegisterClass failed: %lu\n", GetLastError());
    std::exit(1);
  }

  const size_t title_len = strlen(title);
  wchar_t w_title[title_len + 1];
  mbstowcs(w_title, title, title_len + 1);

  HWND hwnd =
      CreateWindowEx(0,          // Optional window styles.
                     CLASS_NAME, // Window class
                     w_title,
                     WS_OVERLAPPEDWINDOW, // Window style
                     // Size and position
                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                     NULL,           // Parent window
                     NULL,           // Menu
                     ctx->hInstance, // Instance handle
                     NULL            // Additional application data
      );

  if (!hwnd) {
    std::printf("CreateWindowEx failed: %lu\n", GetLastError());
    std::exit(1);
  }

  ShowWindow(hwnd, ctx->nCmdShow);
}

void PlatformWindows::pump_messages() {
  ZoneScoped;
  MSG msg;
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
