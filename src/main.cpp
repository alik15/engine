#include "entity.hpp"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include "util.hpp"
#include <cstdlib>
#include <random>
#include <raylib-cpp.hpp>
#include <vector>

int main() {

  // Declaration and Setup
  int screenWidth = 800;
  int screenHeight = 450;
  Vector2 GRAVITY = {0, 9.81};
  const float e = 1.0f;
  const std::size_t totalEntities = 1;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(1.0f, 10.0f);

  raylib::Color textColor(LIGHTGRAY);
  raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

  // Initialize Entities
  std::vector<Entity> entities;
  entities.reserve(totalEntities);

  for (std::size_t i = 0; i < totalEntities; i++) {
    entities.emplace_back(20, GetScreenHeight() / 2.0f - 50, 100, 100,
                          dist(gen),
                          dist(gen)); // modern (C++11)
  }

  SetTargetFPS(60);
  //    collision = CheckCollisionRecs(boxA,boxB);

  // Main game loop
  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    // Update
    // TODO: Update your variables here
    for (int i = 0; i < totalEntities; i++) {
      for (int j = 0; j < totalEntities; j++) {
        if (i == j) {
          break;
        };
        if (CheckCollisionRecs(entities[i].skeleton, entities[j].skeleton)) {
          spdlog::info("Collision detected");
          // New X Velocities
          entities[i].velocity.x =
              ResolveVelocity2D(entities[i].velocity.x, entities[j].velocity.y,
                                entities[i].mass, entities[j].mass, e);
          entities[j].velocity.x =
              ResolveVelocity2D(entities[j].velocity.x, entities[i].velocity.y,
                                entities[j].mass, entities[i].mass, e);

          // entities[j].skeleton.x = ResolveVelocity2D(
          //    float v1, float v2, float m1, float m2, float e);
          // New X Velocities
        }
      };
      entities[i].Move(GRAVITY, screenHeight);
      entities[i].Stats();

      // Check if the Entities are out of bounds
      if (entities[i].skeleton.x + 100.0f >= screenWidth ||
          entities[i].skeleton.x <= 0) {
        entities[i].velocity.x = -entities[i].velocity.x;
      } else if (entities[i].skeleton.y + 100.0f >= screenHeight ||
                 entities[i].skeleton.y <= 0) {
        entities[i].velocity.y = -entities[i].velocity.y;
      };
    };
    // Draw
    BeginDrawing();
    ClearBackground(GRAY);

    for (int i = 0; i < totalEntities; i++) {

      entities[i].Draw(MAROON, BLACK);
    }
    DrawFPS(10, 10);
    EndDrawing();
  }

  return 0;
}