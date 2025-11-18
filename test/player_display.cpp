#include "../src/entity/player.h"
#include "raylib.h"

#include "../src/config.h"
#include "../src/window/window.h"

int main() {
  // 初始化窗口
  Window window(Config::Window::width, Config::Window::height,
                Config::Window::title); // 设置大小和标题
  window.set_fps(Config::Window::fps);  // 设置帧率

  Player player;

  while (!window.shouldClose()) {
    window.beginDrawing();

    window.setBackgroundColor(BLACK);
    player.draw();
    player.updatePosition();

    window.endDrawing();
  }
  window.close();
}