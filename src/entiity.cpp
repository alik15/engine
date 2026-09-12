#include "entity.hpp"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <iostream>

Entity::Entity(float x, float y, float width, float height, float vx, float vy)
    : skeleton{x, y, width, height}, velocity{vx, vy} {
  spdlog::info("Object Created");
  acceleration = {0.0f, 0.0f};
};

int Entity::Draw(Color fillColor, Color outlineColor) {
  DrawRectangleRec(
      skeleton, fillColor); // draws the fill, using skeleton's x/y/width/height
  DrawRectangleLinesEx(skeleton, 2.0f, outlineColor);

  return 0;
};

int Entity::Move(Vector2 gravity, int floor) {
  velocity.x = velocity.x + acceleration.x + gravity.x;
  velocity.y = velocity.y + acceleration.y + gravity.y;
  skeleton.x = skeleton.x + velocity.x;
  skeleton.y = skeleton.y + velocity.y;
  if (skeleton.y + 100.0f > floor) {
    skeleton.y = floor - skeleton.height;
  }

  return 0;
};

int Entity::Stats() {
  spdlog::info("Pos:{}, {} Vel:{}, {}", skeleton.x, skeleton.y, velocity.x,
               velocity.y);
  return 0;
};
Entity::~Entity() { spdlog::warn("Object Destroyed"); };