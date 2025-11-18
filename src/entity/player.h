#pragma once

#include "entity.h"
#include "raylib.h"

class Player : public Entity {
private:
public:
  Player();
  Player(const Player&)            = delete;
  Player& operator=(const Player&) = delete;

  void draw() override;
};