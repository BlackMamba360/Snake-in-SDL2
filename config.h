#pragma once

#include <cstdint> // for uint8_t

constexpr std::uint32_t DELAY_IN_MILLISECONDS = 90;

struct RGBA_Color {
  std::uint8_t r, g, b, a;
};

constexpr RGBA_Color RED = { 255, 0, 0, 255 };
constexpr RGBA_Color WHITE = { 255, 255, 255, 255 };
constexpr RGBA_Color LIGHT_BLUE = { 0, 255, 255, 255 };

struct Tile {
  int x, y;
};

bool checkCollisionBetweenTiles(const Tile& tile1, const Tile& tile2);

constexpr int TILE_SIZE = 20;
constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = GRID_WIDTH;
constexpr int SCREEN_WIDTH = GRID_WIDTH * TILE_SIZE;
constexpr int SCREEN_HEIGHT = GRID_HEIGHT * TILE_SIZE;