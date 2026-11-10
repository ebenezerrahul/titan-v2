#pragma once
class PlatformContext {
public:
  virtual ~PlatformContext() {}
};

class Platform {
public:
  virtual ~Platform() {}
  void virtual Init(PlatformContext *ctx) = 0;
  void virtual CreatePlatformWindow(const int x, const int y,
                                    const char *title) = 0;

  void virtual pump_messages() = 0;
  void virtual Shutdown() = 0;
};

extern Platform *platform;
