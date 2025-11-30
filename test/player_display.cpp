#include "../src/entity/player.h"
#include "raylib.h"

#include "../src/config.h"
#include "../src/window/window.h"

int main() {
  // 初始化窗口
  Window window(Config::Window::WIDTH, Config::Window::HEIGHT,
                Config::Window::TITLE); // 设置大小和标题
  window.set_fps(Config::Window::FPS);  // 设置帧率

  Player player(Config::Player::POSITION, Config::Player::VELOCITY,
                Config::Player::ACCELERATION, Config::Player::RADIUS,
                Config::Player::HP, Config::Player::SCALE,
                Config::Player::IMG_PATH, TextureType::UNIQUE);

  while (!window.shouldClose()) {
    window.beginDrawing();

    window.setBackgroundColor(BLACK);
    player.draw();
    player.updatePosition();

    window.endDrawing();
  }
  window.close();
}