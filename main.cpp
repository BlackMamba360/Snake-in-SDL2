#include <iostream>
#include <memory> // for unique_ptr
#include <SDL2/SDL.h>

#include "game.h"
#include "snake.h"
#include "config.h"

using std::cout, std::endl;

int main() {
  auto game = std::make_unique<GameObject>();

  while (game->is_running) {
    game->handleInput();

    game->snake->update();

    game->checkSnakeConsumableCollision();

    game->checkSnakeLiveliness();

    game->prepareScreen();

    game->drawSnake();

    game->drawConsumable();

    game->presentScreen();

    SDL_Delay(DELAY_IN_MILLISECONDS);
  }

  cout << "|------------------- GAME OVER -------------------|" << endl;
  cout << "| Highscore: " << game->snake->getBody().size() - InitSnakeTailSize << endl;
  cout << "| Final Snake Size: " << game->snake->getBody().size() << endl;
  cout << "|-------------------------------------------------|" << endl;

  return 0;
}