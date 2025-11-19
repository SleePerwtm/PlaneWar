#pragma once

#include "entity.h"

class Enemy : public Entity {
public:
  Enemy(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp, float scale,
        const char* path, TextureType type);
  ~Enemy() = default;
};