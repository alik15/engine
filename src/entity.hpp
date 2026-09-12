#include "raylib.h"
#include <raylib-cpp.hpp>
#ifndef ENTITY_H

#define ENTITY_H

class Entity {
public:
  Entity(float x, float y, float width, float height, float vx, float vy);
  ~Entity();
  int Draw(Color fillColor, Color outlineColor);
  int Move(Vector2 gravity, int floor);
  int Stats();
  int mass;
  Rectangle skeleton;
  Vector2 velocity;
  Vector2 acceleration;
};

#endif