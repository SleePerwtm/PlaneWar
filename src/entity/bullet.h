#pragma once

#include "entity.h"

#include "raylib.h"

class Bullet : public Entity {
private:
public:
  Bullet(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp, float scale,
         const char* path, TextureType type);
  ~Bullet() = default;
};