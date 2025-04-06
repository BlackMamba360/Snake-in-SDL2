#include <iostream>
#include <memory> // for unique_ptr
#include <SDL2/SDL.h>

#include "game.h"
#include "snake.h"
#include "config.h"

using std::cout, std::endl;

int main() {
  auto game = GameObject::init();

  if (game == nullptr) {
    cout << "Failed to initialize GameObject: " << SDL_GetError() << endl;
    return 1;
  }

  auto snake = game->getSnake();

  while (game->isRunning()) {
    game->handleInput();

    snake->update();

    game->checkSnakeConsumableCollision();

    game->checkSnakeLiveliness();

    game->prepareScreen();

    game->drawSnake();

    game->drawConsumable();

    game->presentScreen();

    SDL_Delay(DELAY_IN_MILLISECONDS);
  }

  cout << "|------------------- GAME OVER -------------------|" << endl;
  cout << "| Highscore: " << snake->getBody().size() - InitSnakeTailSize << endl;
  cout << "| Final Snake Size: " << snake->getBody().size() << endl;
  cout << "|-------------------------------------------------|" << endl;

  return 0;
}