#pragma once

#include "raylib.h"

#include <memory>

enum class TextureType { SHARED, UNIQUE }; // 纹理类型

// shared_ptr共享指针纹理，只有最后一个指针指向的变量，才会被销毁。
using TexturePtr = std::shared_ptr<Texture2D>;

// 纹理删除器
void TextureDeleter(Texture2D* texture);

class Entity {
protected:
  Vector2     position_;     // 位置
  Vector2     velocity_;     // 速度
  Vector2     acceleration_; // 加速度
  int         radius_;       // 半径
  int         hp_;           // 血量
  bool        is_active_;    // 是否激活
  TexturePtr  texture_;      // 纹理
  TextureType texture_type_; // 纹理类型
  float       scale_;        // 缩放倍数

  // 加载共享纹理
  static TexturePtr loadSharedTexture(const char* path);
  // 加载独享纹理
  static TexturePtr loadUniqueTexture(const char* path);

public:
  // 不指定纹理的构造函数
  Entity(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp, float scale);
  // 指定纹理的构造函数
  Entity(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp, float scale,
         const char* texture_path, TextureType type);
  // 析构函数
  ~Entity() = default;

  // 更新位置
  virtual void updatePosition();
  // 绘制
  virtual void draw();

  // 加载纹理
  virtual void loadTexture(const char* path, TextureType type);

  // 设置速度
  virtual void set_velocity(Vector2 vel);
  // 设置位置
  virtual void set_position(Vector2 pos);
  // 设置血量
  virtual void set_hp(int hp);

  // 获取速度
  virtual Vector2 get_velocity() const;
  // 获取位置
  virtual Vector2 get_position() const;
  // 获取血量
  virtual int get_hp() const;
  // 获取半径
  virtual int get_radius() const;

  // 激活
  virtual void activate();
  // 停用
  virtual void deactivate();
  // 获取激活状态
  virtual bool is_active() const;

  // 碰撞时受到伤害
  virtual void damage(int damage);
};
