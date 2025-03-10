#include <iostream>
#include "snake.h"

bool checkCollisionBetweenTiles(const Tile &tile1, const Tile &tile2) {
  return tile1.x == tile2.x && tile1.y == tile2.y;
}

Snake::Snake(): is_alive(true) {
  /* create head node */
  body.push_back({GRID_WIDTH / 2, GRID_HEIGHT / 2});

  // create body
  unsigned int i = InitSnakeTailSize;

  do {
    extend();
  } while (--i > 0);

  std::cout << "Snake created\n";
}

Snake::~Snake() { std::cout << "Snake destroyed\n"; }

const std::vector<Tile> &Snake::getBody() const { return body; }

bool Snake::isAlive () const { return is_alive; }

void Snake::truncate() {
  if (body.size() > 1) {
    body.pop_back();
  }
}

void Snake::extend() {
  body.push_back(body.back());

  switch (direction) {
    case SK_NORTH:
      body.back().y += 1;
    break;
    case SK_SOUTH:
      body.back().y -= 1;
    break;
    case SK_WEST:
      body.back().x += 1;
    break;
    case SK_EAST:
      body.back().x -= 1;
  }
}

void Snake::turn(SK_Direction new_direction) {
  if (
    (direction == SK_SOUTH && new_direction == SK_NORTH) ||
    (direction == SK_NORTH && new_direction == SK_SOUTH) ||
    (direction == SK_EAST  && new_direction == SK_WEST) ||
    (direction == SK_WEST  && new_direction == SK_EAST)) {
    return;
    }
  direction = new_direction;
}

void Snake::update() {
  Tile prev_head = body.front();

  switch (direction) {
    case SK_NORTH:
      updateHead(0, -1);
    break;
    case SK_SOUTH:
      updateHead(0, 1);
    break;
    case SK_WEST:
      updateHead(-1, 0);
    break;
    case SK_EAST:
      updateHead(1, 0);
  }

  updateTail(prev_head);
  checkBorderCollision();
  checkSelfCollision();
}

void Snake::updateHead(int dx, int dy) {
  if (dx) body.front().x += dx;
  if (dy) body.front().y += dy;
}

void Snake::updateTail(const Tile &prev_head) {
  std::size_t i = body.size() - 1;

  while (i > 1) {
    body[i] = body[i - 1];
    --i;
  }

  body[i] = prev_head;
}

void Snake::checkBorderCollision() {
  Tile *head = &body.front();

  if (head->x < 0) head->x = GRID_WIDTH - 1;
  else if (head->x >= GRID_WIDTH) head->x = 0;

  if (head->y < 0) head->y = GRID_HEIGHT - 1;
  else if (head->y >= GRID_HEIGHT) head->y = 0;
}

bool Snake::checkCollision(const Tile &obj) const {
  return checkCollisionBetweenTiles(body.front(), obj);
}

void Snake::checkSelfCollision() {
  auto iter = body.begin();

  while (++iter != body.end()) {
    if (checkCollision(*iter)) {
      is_alive = false;
      break;
    }
  }
}