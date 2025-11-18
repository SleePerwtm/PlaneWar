#pragma once

#include "raylib.h"

// 在C++中，非整型的静态成员变量不能在类内初始化，除非使用 constexpr
namespace Config {

namespace Window {
constexpr int         WIDTH  = 900;         // 窗口宽度
constexpr int         HEIGHT = 1280;        // 窗口高度
constexpr const char* TITLE  = "Plane War"; // 窗口标题
constexpr int         FPS    = 60;          // 帧率
}; // namespace Window

namespace Player {
constexpr Vector2     POSITION     = {450 - 16, 640 - 16};   // 初始位置
constexpr Vector2     VELOCITY     = {0, -100};              // 初始速度
constexpr Vector2     ACCELERATION = {0, 0};                 // 初始加速度
constexpr int         RADIUS       = 16;                     // 半径
constexpr int         HP           = 3;                      // 初始血量
constexpr Color       COLOR        = YELLOW;                 // 圆形颜色
constexpr const char* IMG_PATH     = "../assets/player.jpg"; // 玩家贴图资源
}; // namespace Player

}; // namespace Config