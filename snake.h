#pragma once

#include <vector>
#include "config.h"

constexpr unsigned int InitSnakeTailSize = 12;

enum SK_Direction {
  SK_NORTH = 0x1,
  SK_EAST  = 0x2,
  SK_WEST  = 0x4,
  SK_SOUTH = 0x8
};

class Snake {
  std::vector<Tile> body;
  SK_Direction direction = SK_EAST;
  bool is_alive;

  void updateHead(int dx, int dy);
  void updateTail(const Tile &prev_head);
  void checkBorderCollision();
  void checkSelfCollision();
public:
  Snake();
  ~Snake();

  void turn(SK_Direction new_direction);
  void truncate();
  void extend();
  void update();

  [[nodiscard]] bool isAlive() const;
  [[nodiscard]] bool checkCollision(const Tile &obj) const;
  [[nodiscard]] const std::vector<Tile>& getBody() const;
};