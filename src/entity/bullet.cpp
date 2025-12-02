#include "bullet.h"

#include "entity.h"

#include "raylib.h"

Bullet::Bullet(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp,
               float scale, const char* path, TextureType type)
    : Entity(pos, vel, acc, rad, hp, scale, path, type) {
  deactivate();
}