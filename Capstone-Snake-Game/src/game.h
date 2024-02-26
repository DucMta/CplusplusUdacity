#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t numberObstacle);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void SetMaxScore(int score);
  int GetMaxScore(void);

 private:
  Snake snake;
  //snake2
  Snake snake2;
  //snake2
  int count_food{1};//food_v2
  std::vector<SDL_Point> food;//food_v2
  //DucLH12
  std::vector<SDL_Point> obstacle;
  //DucLH12

  std::random_device dev;
  std::mt19937 engine;
  //DucLH12
  std::random_device dev2;
  std::mt19937 engine2;
  //DucLH12
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
 //DucLH12
  void PlaceObstacle();
  int maxScore{0};
  //DucLH12
  void Update();
};

#endif