#pragma once

#include <random>
#include <memory> // for unique_ptr
#include <SDL2/SDL.h>
#include "snake.h"
#include "config.h"

/* ------------ GAME OBJECT IMPLEMENTATION ------------ */

struct GameObject {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  std::unique_ptr<Snake> snake;
  Tile consumable;
  bool is_running;

  GameObject();
  ~GameObject();

  void handleInput();
  void generateConsumable();

  void drawSnake() const;
  void drawConsumable() const;

  void checkSnakeConsumableCollision();
  void checkSnakeLiveliness();

  void prepareScreen() const;
  void presentScreen() const;

private:
  void drawTile(int x, int y) const;

  static std::random_device rd;
  static std::default_random_engine gen;
  static std::uniform_int_distribution<> wdis;
  static std::uniform_int_distribution<> hdis;
};