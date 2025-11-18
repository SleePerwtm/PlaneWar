#pragma once

#include "entity.h"

class Player : public Entity {
private:
public:
  Player();
  Player(const Player&)            = delete;
  Player& operator=(const Player&) = delete;
  ~Player()=default;

  void updatePosition() override;
  void draw() override;
};