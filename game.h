#pragma once

#include <random>
#include <memory> // for unique_ptr, shared_ptr
#include <SDL2/SDL.h>
#include "snake.h"
#include "config.h"

/* ------------ GAME OBJECT IMPLEMENTATION ------------ */

class GameObject {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  std::shared_ptr<Snake> snake;
  Tile consumable;
  bool is_running;

  struct Deleter {
    void operator()(GameObject *game) const;
  };

public:
  static std::unique_ptr<GameObject, Deleter> init();

  void handleInput();
  void generateConsumable();

  void drawSnake() const;
  void drawConsumable() const;

  void checkSnakeConsumableCollision();
  void checkSnakeLiveliness();

  [[nodiscard]] bool isRunning() const;
  [[nodiscard]] std::shared_ptr<Snake> getSnake() const;

  void prepareScreen() const;
  void presentScreen() const;

private:
  GameObject(SDL_Window *win, SDL_Renderer *ren);
  ~GameObject();

  void drawTile(int x, int y) const;

  static std::random_device rd;
  static std::default_random_engine gen;
  static std::uniform_int_distribution<> wdis;
  static std::uniform_int_distribution<> hdis;
};