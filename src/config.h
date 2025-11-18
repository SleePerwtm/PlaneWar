#pragma once

#include "raylib.h"

// 在C++中，非整型的静态成员变量不能在类内初始化，除非使用 constexpr
namespace Config {

namespace Window {
constexpr int         width  = 900;         // 窗口宽度
constexpr int         height = 1280;        // 窗口高度
constexpr const char* title  = "Plane War"; // 窗口标题
constexpr int         fps    = 60;          // 帧率
}; // namespace Window

namespace Player {
constexpr Vector2     position     = {450 - 16, 640 - 16}; // 初始位置
constexpr Vector2     velocity     = {0, -100};               // 初始速度
constexpr Vector2     acceleration = {0, 0};               // 初始加速度
constexpr int         radius       = 16;                   // 半径
constexpr int         hp           = 3;                    // 初始血量
constexpr Color       color        = YELLOW;               // 圆形颜色
constexpr const char* img_path     = "../assets/player.jpg";         // 玩家贴图资源
}; // namespace Player

}; // namespace Config