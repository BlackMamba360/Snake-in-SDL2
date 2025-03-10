#include <iostream>
#include <algorithm> // for all_of
#include "game.h"

std::random_device GameObject::rd;
std::default_random_engine GameObject::gen(rd());
std::uniform_int_distribution<> GameObject::wdis(0, GRID_WIDTH - 1);
std::uniform_int_distribution<> GameObject::hdis(0, GRID_HEIGHT - 1);

GameObject::GameObject(): consumable({}), is_running(true) {
  /* initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    exit(1);
  }

  /* create game window */
  window = SDL_CreateWindow(
    "Snake Game",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(1);
  }

  /* create renderer */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
  }

  snake = std::make_unique<Snake>();

  generateConsumable();

  std::cout << "Successfully initialized GameObject\n";
}

GameObject::~GameObject() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  snake.reset();

  std::cout << "Successfully destroyed GameObject\n";
}

void GameObject::generateConsumable() {
  bool b;

  do {
    consumable.x = wdis(gen);
    consumable.y = hdis(gen);

    b = std::all_of(
      snake->getBody().begin(),
      snake->getBody().end(),
      [this](const Tile &tile) {
        return !checkCollisionBetweenTiles(tile, consumable);
    });
  } while (!b);
}


void GameObject::handleInput() {
  static SDL_Event event;

  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) { is_running = false; }
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_w:
        case SDLK_UP:
          snake->turn(SK_NORTH);
        break;
        case SDLK_s:
        case SDLK_DOWN:
          snake->turn(SK_SOUTH);
        break;
        case SDLK_a:
        case SDLK_LEFT:
          snake->turn(SK_WEST);
        break;
        case SDLK_d:
        case SDLK_RIGHT:
          snake->turn(SK_EAST);
        break;
        case SDLK_ESCAPE:
          is_running = false;
        break;
        default: {
          // Do Nothing
        }
      }

      SDL_FlushEvent(event.type);
    }
  }
}

void GameObject::drawSnake() const {
  auto iter = snake->getBody().begin();

  // draw head (light blue)
  SDL_SetRenderDrawColor(renderer, LIGHT_BLUE.r, LIGHT_BLUE.g, LIGHT_BLUE.b, LIGHT_BLUE.a);
  drawTile(iter->x, iter->y);

  // draw tail (white)
  SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
  while (++iter != snake->getBody().end()) {
    drawTile(iter->x, iter->y);
  }
}

void GameObject::drawConsumable() const {
  SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
  drawTile(consumable.x, consumable.y);
}

void GameObject::prepareScreen() const {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void GameObject::presentScreen() const {
  SDL_RenderPresent(renderer);
}

void GameObject::drawTile(int x, int y) const {
  static SDL_Rect rect = {0, 0, TILE_SIZE, TILE_SIZE};

  rect.x = x * TILE_SIZE;
  rect.y = y * TILE_SIZE;

  SDL_RenderFillRect(renderer, &rect);
}

void GameObject::checkSnakeConsumableCollision() {
  if (checkCollisionBetweenTiles(snake->getBody().front(), consumable)) {
    // snake ate consumable -> increase length by 1
    snake->extend();
    // generate new consumable
    generateConsumable();
  }
}

void GameObject::checkSnakeLiveliness() {
  if (!snake->isAlive()) {
    is_running = false;
  }
}