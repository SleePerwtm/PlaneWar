#include "entity.h"

#include "raylib.h"

#include <memory>
#include <string>
#include <unordered_map>

static std::unordered_map<std::string, std::weak_ptr<Texture2D>> texture_cache_;

void TextureDeleter(Texture2D* texture) {
  if (texture) {
    UnloadTexture(*texture);
    delete texture;
  }
}

Entity::Entity(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp)
    : position_(pos), velocity_(vel), acceleration_(acc), radius_(rad),
      hp_(hp) {}

Entity::Entity(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp,
               const char* path, TextureType type)
    : Entity(pos, vel, acc, rad, hp) {
  texture_type_ = type;
  switch (type) {
  case TextureType::SHARED:
    texture_ = Entity::loadSharedTexture(path);
    break;

  case TextureType::UNIQUE:
    texture_ = Entity::loadUniqueTexture(path);
    break;
  }
}

TexturePtr Entity::loadSharedTexture(const char* path) {
  std::string path_str = path;
  // 查找缓存中是否有该纹理
  auto it = texture_cache_.find(path_str);
  if (it != texture_cache_.end()) {
    // 检查缓存中纹理是否有效
    if (auto exist_texture = it->second.lock()) {
      return exist_texture; // 纹理有效，直接返回
    } else {
      // 纹理已被释放，清理无用缓存项
      texture_cache_.erase(it);
    }
  }

  // 缓存中没有该纹理
  Texture2D* new_texture = new Texture2D(LoadTexture(path));
  TexturePtr new_texture_ptr(new_texture, TextureDeleter);
  texture_cache_[path_str] = new_texture_ptr;
  return new_texture_ptr;
}

TexturePtr Entity::loadUniqueTexture(const char* path) {
  Texture2D* texture = new Texture2D(LoadTexture(path));
  return TexturePtr(texture, TextureDeleter);
}

void Entity::updatePosition() {
  /* 利用 raylib 中的 GetFrameTime() 函数，获取帧间间隔时间 */
  position_.x += velocity_.x * GetFrameTime();
  position_.y += velocity_.y * GetFrameTime();

  velocity_.x += acceleration_.x * GetFrameTime();
  velocity_.y += acceleration_.y * GetFrameTime();
}

void Entity::loadTexture(const char* path, TextureType type) {
  switch (type) {
  case TextureType::SHARED:
    texture_ = Entity::loadSharedTexture(path);
    break;

  case TextureType::UNIQUE:
    texture_ = Entity::loadUniqueTexture(path);
    break;
  }
}

void Entity::set_position(Vector2 pos) { position_ = pos; }

void Entity::set_velocity(Vector2 vel) { velocity_ = vel; }

void Entity::set_acceleration(Vector2 acc) { acceleration_ = acc; }

Vector2 Entity::get_position() const { return position_; }

Vector2 Entity::get_velocity() const { return velocity_; }

Vector2 Entity::get_acceleration() const { return acceleration_; }