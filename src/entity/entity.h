#pragma once

#include "raylib.h"

#include <memory>

enum class TextureType { SHARED, UNIQUE }; // 纹理类型 感觉是个不错的抽象
using TexturePtr = std::shared_ptr<Texture2D>;

// 纹理删除器
void TextureDeleter(Texture2D* texture);

class Entity {
protected:
  Vector2 position_;     // 位置
  Vector2 velocity_;     // 速度
  Vector2 acceleration_; // 加速度
  int     radius_;       // 半径
  int     hp_;           // 血量
  bool    is_alive_;     // 是否存活
  // shared_ptr共享指针纹理，只有最后一个指针指向的变量，才会被销毁。
  TexturePtr  texture_;      // 纹理
  TextureType texture_type_; // 纹理类型

  // 加载共享纹理
  static TexturePtr loadSharedTexture(const char* path);
  // 加载独享纹理
  static TexturePtr loadUniqueTexture(const char* path);

public:
  // 不指定纹理的构造函数
  Entity(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp);
  // 指定纹理的构造函数
  Entity(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp,
         const char* texture_path, TextureType type);

  // 绘制
  virtual void draw() = 0;
  // 更新位置
  virtual void updatePosition();

  // 加载纹理
  virtual void loadTexture(const char* path, TextureType type);

  // 设置位置
  virtual void set_position(Vector2 pos);
  // 设置速度
  virtual void set_velocity(Vector2 vel);
  // 设置加速度
  virtual void set_acceleration(Vector2 acc);

  // 获取位置
  virtual Vector2 get_position() const;
  // 获取速度
  virtual Vector2 get_velocity() const;
  // 获取加速度
  virtual Vector2 get_acceleration() const;

  // 析构函数
  ~Entity() = default;
};
