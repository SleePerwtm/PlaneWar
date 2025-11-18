#include "raylib.h"

#include "config.h"
#include "window/window.h"

int main() {
  // 初始化窗口
  Window window(Config::Window::WIDTH, Config::Window::HEIGHT,
                Config::Window::TITLE); // 设置大小和标题
  window.set_fps(Config::Window::FPS);  // 设置帧率

  while (!window.shouldClose()) {
    window.beginDrawing();

    window.setBackgroundColor(BLACK);

    window.endDrawing();
  }
  window.close();
}